/**
 * Lua filter support.
 \file luaplug.cpp 
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
#include "defaults.h"

#include "plugin.h"
#include "luaplug.h"
#include "builtins.h"
#include "filter.h"

lua_State* L = NULL;

// Built-in Functions
typedef struct FuncTable {
  char *name;
  int (*ptr)(lua_State *);
} FuncTable;

FuncTable funcs[] = {
  { "beep", beep }, 
  { "message", message }, 
  { "choice", choice }, 
  { "camfilter_off", camfilter_off }, 
  { "getpixel", getpixel }, 
  { "putpixel", putpixel } ,
  { "create_images", createimages }, 
  { "destroy_images", destroyimages }, 
  { "negative", negative }, 
  { "xmirror", xmirror }, 
  { "copy_images", copy_images }, 
  { "integral_image", integral_image }, 
  { "mult_images", mult_images }, 
  { "add_images", add_images }, 
  { "absdiff_images", absdiff_images }, 
};
int n_funcs = 15;

// Lua Support Functions

void initlua(void)
{
  if (L!=NULL) 
    return;
  L=luaL_newstate();
  luaL_openlibs(L);
  for (int i=0; i < n_funcs; i++) 
    lua_register(L, funcs[i].name, funcs[i].ptr);
}

int load_plugin(const char *filename)
{
  if (L==NULL) 
    initlua();
  if (test_file(filename,  "r") == FALSE)
    return plugin_error("Lua Load error:", "filename");
  if (luaL_dofile(L,filename)==0)
    return 1;
  else
    return plugin_error("Lua Parse:", lua_tostring(L,-1));
}

int docall(const char* name, int n)
{
  lua_getglobal(L,name);
  if (lua_isnil(L,-1)) 
    return 0;
  lua_insert(L,-n-1);
  if (lua_pcall(L,n,1,1) != 0) {
    return plugin_error("Lua Runtime:",lua_tostring(L,-1));
  }
  return lua_tonumber(L,-1);
}


