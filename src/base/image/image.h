/**
 * This file represents an Image.
 \file image.h
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
#ifndef IMAGE_H
#define IMAGE_H

#include "laux.h"

#define IMG_DV_W 720
#define IMG_DV_H 480

#define RED(c) (c.r)
#define GRN(c) (c.g)
#define BLU(c) (c.b)


typedef struct Bcolor {
  Byte r, g, b;
} Bcolor;

typedef struct Image {
  int w, h;
  Byte *c;
} Image;

Image *img_create(int w, int h);
void img_free(Image *i);

void  img_clear(Image *i, Bcolor c);

void  img_putc(Image *i, int u, int v, Bcolor c);
Bcolor img_getc(Image *i, int u, int v);

Bcolor c_make(Byte x, Byte y, Byte z);

#endif
