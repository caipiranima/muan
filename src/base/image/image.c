/**
 * This file implements the methods about an Image.
 \file image.c
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

#ifndef WIN32
#include <unistd.h>
#endif
#include "image.h"

#define PIXRED(I,U,V) I->c[(U + (((I->h - 1) - (V)) * I->w))*3]
#define PIXGRN(I,U,V) I->c[(U + (((I->h - 1) - (V)) * I->w))*3+1]
#define PIXBLU(I,U,V) I->c[(U + (((I->h - 1) - (V)) * I->w))*3+2]


/**
 * Creates a new image.
 * @param type The Image type: IMG_TRUECOL, IMG_MAPPCOL, IMG_MONOCOL.
 * @param w The Image width.
 * @param h The Image height.
 * @return The Image.
 */
Image *img_create(int w, int h)
{
  Image *i = NEWSTRUCT(Image);
  i->w = w; i->h = h;
  i->c = NEWTARRAY(w*h*3, Byte);
  return i;
}

/**
 * Frees an image
 */
void img_free(Image *i)
{
  efree(i->c); efree(i);
}

/**
 * Clears an image with a color.
 * @param i The image to clear
 * @param c The color to fill.
 */
void img_clear(Image *i, Bcolor c)
{
  int u, v;
  for (v = 0; v < i->h; v++)
    for (u = 0; u < i->w; u++)
      img_putc(i,u,v,c);
}

/**
 * Sets a pixel on the image using color
 */
void img_putc(Image *i, int u, int v, Bcolor c)
{
  if (u >= 0 && u < i->w && v >= 0 && v < i->h) {
    PIXRED(i,u,v) = RED(c); 
    PIXGRN(i,u,v) = GRN(c); 
    PIXBLU(i,u,v) = BLU(c);
  }
}

/**
 * Gets the color of a pixel on the image
 */
Bcolor img_getc(Image *i, int u, int v)
{
  int k;
  if (u >= 0 && u < i->w && v >= 0 && v < i->h)
    return c_make(PIXRED(i,u,v),PIXGRN(i,u,v),PIXBLU(i,u,v));
  else
    return c_make(0,0,0);
}

Bcolor c_make(Byte x, Byte y, Byte z)
{
  Bcolor v;
  v.r = x; v.g = y; v.b = z;
  return v;
}
