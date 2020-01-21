/**
 * This file represents a video interface.
 \file video.h
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
#ifndef VIDEO_H
#define VIDEO_H

#include "frame.h"

extern "C" {
#include "image.h"
}

// Methods.

int          video_open( const char *config_fname, int cam_type);
void         video_close( void );
int          video_getframe( Frame *f );

int          video_w();
int          video_h();
		
void         video_stopReceive();
void         video_startReceive();

void         video_stopThread();
void         video_startThread();

#endif
