/**
 * This file represents a video encoder interface. The video manipulation operations are defined here.  
  \file video_encoder.h 
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
#ifndef VIDEO_ENCODER_H
#define VIDEO_ENCODER_H

#include <stdio.h>
#include <stdlib.h>

#include "imglist.h"
extern "C"{
#include "ffmpeg_rw.h"
#include "image.h"
#include "jpeg.h"
}

#define FRAME_DURATION 1
#define MAX_FRAMES 10000
#define MAX_FILE_SIZE 10000
#define JPEG_QUALITY 90

#define AVI_DV2_FORMAT 0 // temporary !!!

class VideoEncoder{
public:
   bool avi_write( char *fname, ImgList *imgl, int file_format, int max_frames,
                   off_t max_file_size, bool time_stamp, bool isOpenDML, int w=0, int h=0);                
   bool avi_read( ImgList *imgl, const char *fname, int load_mode); // lv: integrate

   bool mpg_write( ImgList *imgl, const char *fname, int w=0, int h=0);
   bool mpg_read( ImgList *imgl, const char *fname); // lv: integrate

   bool avffmpeg_write( ImgList *imgl, const char *fname, int w=0, int h=0);
   bool avffmpeg_read( ImgList *imgl, const char *fname);

   bool jpg_write( ImgList *imgl, const char *fname, int quality);
   bool jpg_read( ImgList *imgl, const char *dirname, int load_mode );

   bool verify_frame_duplication(unsigned char *i1, unsigned char *i2, int load_mode,  int w, int h, int key);
   bool verify_image_duplication(unsigned char *i1, unsigned char *i2, int w, int h);
};


#endif
