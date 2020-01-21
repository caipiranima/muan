/**
 * Lua builtin functions for MUAN
 \file builtins.cpp 
 */
/*
 * Copyright (C) 2006  Lab. Visgraf/IMPA and AnimaMundi
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 * 
*/
#include <math.h>
#include "luaplug.h"
#include "builtins.h"
#include "defaults.h"

/* linear interpolation from l (when a=0) to h (when a=1)*/
/* (equal to (a*h)+((1-a)*l) */
#define LERP(a,l,h)	((l)+(((h)-(l))*(a)))

/* clamp the input to the specified range */
#define CLAMP(v,l,h)	((v)<(l) ? (l) : (v) > (h) ? (h) : v)


// Images
#define MAX_IMAGES 64
static Image* image[MAX_IMAGES];
static int n_images = 1;


// Lua Export Functions

extern "C" {

// Internal 

int freeimages(void)
{
  int i;
  for (i = 1; i < n_images; i++)
    img_free(image[i]);
  n_images = 1;
  return 0;
}

int setimage(Image *img, int k)
{
  if (k < n_images)
    image[k] = img;

  return 0;
}

// Auxiliary UI funcs

int beep(lua_State *L)
{
  ui_beep();
  return 0;
}

int camfilter_off(lua_State *L)
{
  ui_setfilter(FALSE);
  return 0;
}

int message(lua_State *L)
{
  const char *msg = luaL_checklstring(L,1,NULL);
  ui_message(msg);
  return 0;
}

int choice(lua_State *L)
{
  const char *msg = luaL_checklstring(L,1,NULL);
  int ret = ui_choice(msg, "cancel", "yes", "no");
  lua_pushnumber(L,ret);
  return 1;
}

// Basic Image Functions

int getpixel(lua_State *L)
{
  Bcolor p;
  int u = luaL_checknumber(L,1);
  int v = luaL_checknumber(L,2);
  int n = luaL_optnumber(L,3,0);
  if (n < n_images)
    p = img_getc(image[n], u, v);
  else
    p = c_make(0,0,0);
  lua_pushnumber(L,p.r);
  lua_pushnumber(L,p.g);
  lua_pushnumber(L,p.b);
  return 3;
}

int putpixel(lua_State *L)
{
  int u = luaL_checknumber(L,1);
  int v = luaL_checknumber(L,2);
  int r = luaL_checknumber(L,3);
  int g = luaL_checknumber(L,4);
  int b = luaL_checknumber(L,5);
  int n = luaL_optnumber(L,6,0);
  if (n < n_images)
    img_putc(image[n], u, v, c_make(r,g,b));
  return 0;
}

int createimages(lua_State *L)
{
  int i, n = luaL_checknumber(L,1) + 1;
  int ni = n_images;
  int w = image[0]->w;
  int h = image[0]->h;
  if (n > MAX_IMAGES)
    n_images = MAX_IMAGES;
  else if (n > n_images)
    n_images = n;
  for (i=ni; i<n_images; i++) {
    image[i] = img_create(w,h);
  }
  return 0;
}

int destroyimages(lua_State *L)
{
  freeimages();
  return 0;
}

// Add-ons

int negative(lua_State *L)
{
  int k = luaL_optnumber(L,1,0);
  int w = image[0]->w;
  int h = image[0]->h;
  int u, v;
  if (k >= n_images) 
    return 0;
  for (u=0; u < w; u++) {
    for (v=0; v < h; v++) {
      Bcolor p = img_getc(image[k], u, v);
      img_putc(image[k], u, v, c_make(255-p.r, 255-p.g, 255-p.b));
    }
  }
  return 0;
}

int xmirror(lua_State *L)
{
  int k = luaL_optnumber(L,1,0);
  int w = image[0]->w;
  int h = image[0]->h;
  int u, v;
  if (k >= n_images) 
    return 0;
  for (u=0; u < w; u++) {
    for (v=0; v < h; v++) {
      Bcolor p = img_getc(image[k], u, v);
      img_putc(image[k], w-u-1, v, c_make(p.r, p.g, p.b));
    }
  }
  return 0;
}

int copy_images(lua_State *L)
{
  int src = luaL_checknumber(L,1);
  int dst = luaL_checknumber(L,2);
  int w = image[0]->w;
  int h = image[0]->h;
  int u, v;
  if (src >= n_images || dst >= n_images) 
    return 0;
  for (u=0; u < w; u++) {
    for (v=0; v < h; v++) {
      Bcolor p = img_getc(image[src], u, v);
      img_putc(image[dst], u, v, c_make(p.r, p.g, p.b));
    }
  }
  return 0;
}

int absdiff_images(lua_State *L)
{
  int src1 = luaL_checknumber(L,1);
  int src2 = luaL_checknumber(L,2);
  int dst = luaL_optnumber(L,3,src2);
  int w = image[0]->w;
  int h = image[0]->h;
  int u, v;
  if (src1 >= n_images || src2 >= n_images ||dst >= n_images) 
    return 0;
  for (u=0; u < w; u++) {
    for (v=0; v < h; v++) {
      Bcolor p0 = img_getc(image[src1], u, v);
      Bcolor p1 = img_getc(image[src2], u, v);
      float r = fabs((float)(p0.r) - (float)(p1.r));
      float g = fabs((float)(p0.g) - (float)(p1.g));
      float b = fabs((float)(p0.b) - (float)(p1.b));
      img_putc(image[dst], u, v, c_make(r, g, b));
    }
  }
  return 0;
}

int integral_image(lua_State *L)
{
  int src = luaL_checknumber(L,1);
  int w = image[0]->w;
  int h = image[0]->h;
  int u, v;
  double ad = 0;
  if (src >= n_images) 
    return 0;
  for (u=0; u < w; u++) {
    for (v=0; v < h; v++) {
      Bcolor p = img_getc(image[src], u, v);
      float d = p.r + p.g + p.b;
      ad += d;
    }
  }
  lua_pushnumber(L,ad);
  return 1;
}

int mult_images(lua_State *L)
{
  float t = luaL_checknumber(L,1);
  int src = luaL_checknumber(L,2);
  int dst = luaL_optnumber(L,3,src);
  int w = image[0]->w;
  int h = image[0]->h;
  int u, v;
  if (src >= n_images || dst >= n_images) 
    return 0;
  for (u=0; u < w; u++) {
    for (v=0; v < h; v++) {
      Bcolor p = img_getc(image[src], u, v);
      float r = CLAMP((float)(p.r) * t, 0, 255);
      float g = CLAMP((float)(p.g) * t, 0, 255);
      float b = CLAMP((float)(p.b) * t, 0, 255);
      img_putc(image[dst], u, v, c_make(r, g, b));
    }
  }
  return 0;
}

int add_images(lua_State *L)
{
  int src1 = luaL_checknumber(L,1);
  int src2 = luaL_checknumber(L,2);
  int dst = luaL_optnumber(L,3,src2);
  int w = image[0]->w;
  int h = image[0]->h;
  int u, v;
  if (src1 >= n_images || src2 >= n_images || dst >= n_images) 
    return 0;
  for (u=0; u < w; u++) {
    for (v=0; v < h; v++) {
      Bcolor p1 = img_getc(image[src1], u, v);
      Bcolor p2 = img_getc(image[src2], u, v);
      float r = CLAMP((float)(p1.r) + (float)(p2.r), 0, 255);
      float g = CLAMP((float)(p1.g) + (float)(p2.g), 0, 255);
      float b = CLAMP((float)(p1.b) + (float)(p2.b), 0, 255);
      img_putc(image[dst], u, v, c_make(r, g, b));
    }
  }
  return 0;
}

}


