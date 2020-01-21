/**
 * This file represents the Image attributes.
 \file imgnode.cpp
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
#include "imglist.h"


/**
 * Creates a new ImageNode.
 * @param f an ImageNode Frame attribute.
 * @param delay an ImageNode delay attribute.
 * @return The ImageNode.
 */
ImgNode *imgnode_alloc( Frame *f, int delay, int frame_duration ) 
{
 ImgNode *i = NEWSTRUCT(ImgNode);
 i->next = i->prev = NULL;
 i->frame_number = 0;
 i->frame_pos = 0;
 i->delay = delay;
 i->time_stamp = 0;
 i->frame_duration = frame_duration;

 i->frame = f;

 return i;
}


/**
 * Disposes an ImageNode.
 * @param i the ImageNode to be deleted..
 */
void imgnode_dispose( ImgNode *i ) 
{
 if( i->frame != NULL )
   delete i->frame;

 efree(i);
}

/**
  * Copies an ImageNode.
  * @param i the ImageNode to be copied.
  */
ImgNode *imgnode_copy(ImgNode *i)
{
    Frame *f = new Frame( *(i->frame) );
    return imgnode_alloc(f, i->delay, i->frame_duration);
}
