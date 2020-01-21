/**
 * This file represents an ImageNode and ImageList interface.
 \file imglist.h
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
#ifndef IMGLIST_H
#define IMGLIST_H

extern "C"{
#include "image.h"
#include "jpeg.h"
#include <string.h>
#include <stdint.h>
}
#include "frame.h"
#include "video.h"

void setMessage(const char* m);

/**
 * The ImageNode structure.
 */
typedef struct ImgNode{
  struct ImgNode *next, *prev;
  int delay;
  int time_stamp;
  int frame_number; 	// posicao (na lista) do frame capturado 
  int frame_pos;	// posicao (na animacao) considerando duracao
  int frame_duration;
  Frame *frame;
} ImgNode;

/**
 * The ImageList structure.
 */
typedef struct ImgList{
  ImgNode *head, *current;
  int totFrames;       // total de capturas (frames sem considerar duracao) 
  int totRealFrames;   // total de frames da lista considerando duracao
  int img_w, img_h;
} ImgList;

// The ImageNode methods signature.
ImgNode *imgnode_alloc( Frame *f, int delay, int frame_duration );
void imgnode_dispose( ImgNode *i );
ImgNode *imgnode_copy( ImgNode *i );

//The ImageList methods signature.
ImgList *imglist_alloc( int w, int h );
void imglist_clear( ImgList *q );
void imglist_dispose( ImgList *q );
int  imglist_isempty( ImgList *q );
Frame* imglist_peek_current_frame( ImgList *q );
void imglist_insert( ImgList *q, ImgNode *i );
void imglist_insert( ImgList *q, ImgList *c, bool invert);
void imglist_removeInRange( ImgList *q, int begin, int end );
void imglist_step( ImgList *q, int step);
void imglist_step_foward( ImgList *q );
void imglist_step_backward( ImgList *q );
void imglist_rew( ImgList *q );
void imglist_go_to_end( ImgList *q );
void imglist_update_frames( ImgList *q );
void imglist_go_to_frame( ImgList *q, int frameNumber );
int imglist_getTotalFrames(ImgList *q);
int imglist_getTotalRealFrames(ImgList *q);
void imglist_setFrameDuration(ImgList *q, int begin, int end, int duration);
int imglist_getCurrentFnum(ImgList *q);

void insert_frame_from_imagefile(ImgList *imgl, char *fname);
void insert_frame_from_jpgfile(ImgList *imgl, char *fname);

#define imglist_addimg imglist_insert
#define imglist_addlist imglist_insert

#endif
