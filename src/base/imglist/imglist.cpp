/**
 * This file represents an image list and has the control methods of the captured images.
 \file imglist.cpp
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

#include <iostream>
#include <assert.h>
#include "imglist.h"
#include "stdlib.h"

#ifdef WIN32
typedef unsigned char uint8_t;
#endif

static Frame *auxframe = NULL;

/**
 * Creates a new ImageList.
 * @return The ImageList.
 */
ImgList *imglist_alloc( int w, int h )
{
  ImgList *q = NEWSTRUCT(ImgList);
  q->head = q->current = NULL;
  q->totFrames = 0;
  q->totRealFrames = 0;
  q->img_w = w; q->img_h = h;

  return q;
}

/**
 *Inserts a frame from image file (RAS or JPG).
 * @param imgl imageList where the frame will be inserted.
 * @param fname image file name.
 */
void insert_frame_from_imagefile(ImgList *imgl, char *fname)
{
  char* ext = (char *)"";
  if (fname != NULL) {
      if (strlen(fname)>0)
        ext = strrchr(fname, '.');
      if (strcmp(ext, ".jpg")==0 || strcmp(ext, ".JPG")==0) {
        insert_frame_from_jpgfile(imgl, fname);
      } else {
        setMessage("Invalid frame file format.");
      }
  }
}


/**
 *Inserts a frame from JPG image file.
 * @param imgl imageList where the frame will be inserted.
 * @param fname image file name.
 */
void insert_frame_from_jpgfile(ImgList *imgl, char *fname)
{
  Frame *frame = new Frame(imgl->img_w, imgl->img_h);
  uint8_t *imagebuf = read_JPEG_file(fname, imgl->img_w, imgl->img_h);
  if (imagebuf != NULL) {
    frame->StoreRGB(imagebuf);
    free(imagebuf);
    imglist_insert(imgl, imgnode_alloc( frame , 3, 1));
  }
}

/**
 * Gets the current image in the ImageList.
 * @param q the ImageList.
 * @return The current image.
 */
Frame *imglist_peek_current_frame( ImgList *q )
{
  Frame *frame;
  if( auxframe == NULL )
    auxframe = new Frame(q->img_w, q->img_h);
  if (q->current != NULL)
    frame = q->current->frame;
  else
    frame = auxframe;
  return frame;
}


/**
 * Returns true if the ImageList is empty, false otherwise.
 * @param q the ImageList.
 * @return true if the ImageList is empty, false otherwise.
 */
int imglist_isempty( ImgList *q )
{
  return (q->head == NULL);
}

/**
 * Inserts an ImageNode in the ImageList.
 * @param q the ImageList.
 * @param i the ImageNode to be inserted.
 */
void imglist_insert( ImgList *q, ImgNode *i )
{
  ImgNode *aux = NULL;

  if(q->head == NULL) {
    q->head = q->current = i;
  } else if(q->current != NULL) {
    aux = q->current->next;
    q->current->next = i;
    i->prev = q->current;
    q->current = i;
  }
  i->next = aux;
  if( aux != NULL ) {
    aux->prev = i;
  }
  q->totFrames += 1;
  q->totRealFrames += i->frame_duration;

  imglist_update_frames( q );
}


/**
 * Merges two ImageList.
 * @param q the main ImageList.
 * @param c the ImageList to be merged.
 */
void imglist_insert( ImgList *q, ImgList *c, bool invert )
{
    ImgNode *aux = NULL;
    ImgNode *i = NULL;
    ImgNode *end = NULL;
    bool pasteAfterLastFrame = false;

    end = c->current;

    if(q->current != NULL && q->current->next == NULL) 
        pasteAfterLastFrame = true;
    if (invert)
        c->current = c->head;

    while(c->current != NULL) {
        i = imgnode_copy(c->current);
        if(q->head == NULL) {
            q->head = q->current = i;
        } else if(q->current != NULL) {
            if(pasteAfterLastFrame) {
                aux = q->current;
                pasteAfterLastFrame = false;
            } else {
                aux = q->current->prev;
                q->current->prev = i;
                i->next = q->current;
            }
            if(q->current == q->head) {
                q->head = i;
            }
            q->current = i;
        }
        i->prev = aux;
        if( aux != NULL ) {
            aux->next = i;
        }
        q->totFrames += 1;
        q->totRealFrames += i->frame_duration;

        c->current = (invert)? c->current->next : c->current->prev;
    }
    c->current = end;
    imglist_update_frames( q );
}

/**
 * Removes the current ImageNode in the ImageList.
 * @param q the ImageList.
 */
void imglist_removeInRange( ImgList *q, int begin, int end )
{
  ImgNode *i, *aux;
  int fnumber = 1, fpos = 1, fts= 0, cont = 0, total;

  if ( q != NULL && q->head != NULL) {
    assert(begin <= end);
    assert(end <= q->totFrames);
    total = q->totFrames;

    i = q->head;

    while (cont++ < total) {
      ImgNode *aux = i;
      i = i->next;

      if (cont < begin) {
        fnumber++;
        fpos += aux->frame_duration;
        fts += (aux->delay*aux->frame_duration);
      }
      if ((cont >= begin) && (cont <= end)) {

        if (aux == q->head)
          q->head = aux->next;
        else
          aux->prev->next = aux->next;

        if (aux->next == NULL)
          q->current = q->head;
        else
          aux->next->prev = aux->prev;

        q->totFrames -= 1;
        q->totRealFrames -= aux->frame_duration;

        if (q->current == aux)
          q->current = NULL;

        imgnode_dispose(aux);
      }
      if (cont > end) {
        if (q->current == NULL)
          q->current = aux;
        aux->frame_number = fnumber++;
        aux->frame_pos = fpos;
        fpos += aux->frame_duration;
        fts += (aux->delay*aux->frame_duration);
        aux->time_stamp = fts;
      }
    }
  }
}


/**
 * Clears an ImageList.
 * @param q the ImageList.
 */
void imglist_clear( ImgList *q )
{
  if (q != NULL) {
    ImgNode *i = q->head;

    q->current=NULL;
    q->head=NULL;

    while (i != NULL) {
      ImgNode *t = i;
      i = i->next;
      imgnode_dispose(t);
    }
    q->head = q->current = NULL;
    q->totFrames = 0;
    q->totRealFrames = 0;
  }
}


/**
 * Disposes an ImageList.
 * @param q the ImageList.
 */
void imglist_dispose( ImgList *q )
{
  imglist_clear(q);
  efree(q);
}

/**
 * Forwards/Backwards the current ImageNode in the ImageList using step.
 * @param q the ImageList.
 * @param step the number to increment/decrement current ImageNode position.
 */
void imglist_step( ImgList *q, int step)
{
  if ((q->current != NULL) && (step != 0))
    {
      if (step < 0)
        while (( step++ < 0 ) && (q->current->prev != NULL))
          q->current = q->current->prev;
      else  //step > 0
        while (( step-- > 0 ) && (q->current->next != NULL))
          q->current = q->current->next;
    }
}


/**
 * Forwards the current ImageNode in the ImageList.
 * @param q the ImageList.
 */
void imglist_step_foward( ImgList *q )
{
  if( (q->current != NULL) && (q->current->next != NULL) ) {
    q->current = q->current->next;
  }
}


/**
 * Backwards the current ImageNode in the ImageList.
 * @param q the ImageList.
 */
void imglist_step_backward( ImgList *q )
{
  if(q->current != NULL && (q->current->prev != NULL)) {
    q->current = q->current->prev;
  }
}


/**
 * Rewinds an ImageList.
 * @param q the ImageList.
 */
void imglist_rew( ImgList *q )
{
  q->current = q->head;
}


/**
 * Goes to the end of the ImageList.
 * @param q the ImageList.
 */
void imglist_go_to_end( ImgList *q )
{
  while( (q->current != NULL) && (q->current->next != NULL) )
    q->current = q->current->next;
}


/**
 * Updates all the ImageNodes frame number, frame_pos and time_stamp in the ImageList.
 * @param q the ImageList.
 */
void imglist_update_frames( ImgList *q )
{
  int fnumber = 1, fpos = 1, aux = 0;
  ImgNode *i;
  if ( q == NULL) return;
  for( i = q->head; i!= NULL; i = i->next )  {
      i->frame_number = fnumber++;
      i->frame_pos = fpos;
      fpos = fpos + i->frame_duration;
      aux += (i->delay*i->frame_duration);
      i->time_stamp = aux;
    }
}


/**
 *Shows a desired frame.
 *@param q the image list.
 *@param frameNumber the desired frame number.
 */
void imglist_go_to_frame( ImgList *q, int frameNumber )
{
  ImgNode *i;
  if ( q == NULL) return;
  for(i = q->head; i!= NULL; i = i->next) {
    if(i->frame_number == frameNumber) {
      q->current = i;
      break;
    }
  }
}


/**
 *Gets the total of frames in an ImageList
 *@param q the ImageList
 *@return The number of frames in an ImageList.
 */
int imglist_getTotalFrames(ImgList *q)
{
  if ( q != NULL )
    return q->totFrames;
  else
    return 0;
}


/**
 *Calculate the total of real frames (frame*duration) in an ImageList
 *@param q the ImageList
 *@return The number of frames in an ImageList.
 */
int imglist_getTotalRealFrames(ImgList *q)
{
  if ( q != NULL )
    return q->totRealFrames;
  else
    return 0;
}


/**
 * Sets the current frame duration.
 *@param begin the begin of the range where to set the new duration.
 *@param end the end of the range where to set the new duration.
 *@param duration the new duration.
 *@param q the ImageList
 **/
void imglist_setFrameDuration(ImgList *q, int begin, int end, int duration)
{
  int fpos = 1, aux = 0;
  ImgNode *i;

  if ( q != NULL ) {
    for (i = q->head; i!= NULL; i = i->next) {
      if ((i->frame_number >= begin) && (i->frame_number <= end)) {
        q->totRealFrames -= i->frame_duration;
        i->frame_duration = duration;
        q->totRealFrames += i->frame_duration;
      }
      i->frame_pos = fpos;
      fpos = fpos + i->frame_duration;
      aux += (i->delay*i->frame_duration);
      i->time_stamp = aux;
    } //fim do for
  } //fim do if
}

/**
 * Get the current frame number.
 **/
int imglist_getCurrentFnum(ImgList *q)
{
  if (q != NULL && q->current != NULL)
    return q->current->frame_number;
  else
    return 0;
}
