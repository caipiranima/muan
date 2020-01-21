/**
 * Utilities for processing digital video frames.
 \file frame.cpp 
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

// C++ includes

#include <string>
#include <iostream>
#include <string.h>

// local includes
#include "frame.h"

/** constructor
*/
Frame::Frame(int width, int height)
{
  int i, clear = false;
  this->img = img_create(width, height);
  if (clear)
    img_clear(this->img, c_make(0,0,0));
}
/** copy constructor
*/
Frame::Frame(const Frame &that)
{
    this->img = img_create(that.img->w, that.img->h);
    this->StoreRGB( that.img->c );
}


/** operator =
*/
Frame *Frame::operator =(const Frame &that)
{
    if(this != &that) {
        this->img = img_create(that.img->w, that.img->h);
        this->StoreRGB( that.img->c );
    }
    return this;
}

/** destructor
 */
Frame::~Frame()
{
  img_free(this->img);
}

int Frame::ExtractRGB( void * rgb )
{
  unsigned char *p = (unsigned char *) rgb;
  unsigned char *d = (unsigned char *) (img->c);
  memcpy(p, d, img->w * img->h * 3);
  return 1;
}

int Frame::StoreRGB( void * rgb )
{
  unsigned char *p = (unsigned char *) rgb;
  unsigned char *d = (unsigned char *) (img->c);
  memcpy(d, p, img->w * img->h * 3);
  return 1;
}

/** Get the frame image width.
    \return the width in pixels.
*/
int Frame::GetWidth()
{
  return this->img->w;
}

/** Get the frame image height.
    \return the height in pixels.
*/
int Frame::GetHeight()
{
  return this->img->h;
}

/** Get the frame image data
    \return the pixel buffer.
*/
unsigned char * Frame::GetData()
{
  return (unsigned char *)(this->img->c);
}

/** Get the frame image 
    \return img struct.
*/
Image * Frame::GetImage()
{
  return (this->img);
}
