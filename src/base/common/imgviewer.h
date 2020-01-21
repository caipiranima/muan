/**
 * This file represents the image exhibition area.
 \file imgviewer.h
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
#ifndef IMGVIEWER_H
#define IMGVIEWER_H

#include <stdio.h>
#include <time.h>

#include "FL/Fl.H"
#include "FL/Fl_Widget.H"
#include "FL/Fl_Output.H"
#include "FL/fl_draw.H"
#include "FL/Fl_Button.H"
#include "FL/Fl_Gl_Window.H"
#include "FL/Fl_Double_Window.H"
#include <FL/gl.h>

#include "defaults.h"
#include "lang_ui.h"

#include "frame.h"
#include "imglist.h"
#include "video.h"

#include "filter.h"

typedef void (*setLabelModeViewerFunc)(bool, bool);

enum PlayMode{_MUAN_FULL, _MUAN_PLAYER};

class ImageViewer : public Fl_Gl_Window {
   int video_on;
   double c_scale;
   void init_GL();
   void draw();
   void resize(int X, int Y, int W, int H);
   void calcule_c_scale();

  public:
   PlayMode imgvmode;
   int filter_on, transp_on, flick_on, is_playing, is_looping, is_saving;
   double flick_delay, transp_fac;
   ImgList *imgl;
   ImgList *clipboard;
   Frame *frm;
   
   ImageViewer (int x, int y, int w, int h);
   bool initialize (int w, int h);
   void changeConnectMode (int mode);

   void play ();
   void stop ();
   void flick ( void );
   void insert_frame ( int delay, int frame_duration );
   void copy_frame(int begin=-1, int end=-1);
   void paste_frame(bool invert=false);
   void goToFrame ( int frameNumber );
   void playInRange (int begin, int end);   
   void setModeViewer (int _camera_on, int _mem_alert, 
                       setLabelModeViewerFunc setLabel = NULL);
   int get_video_on (void) { return video_on;}
};


#endif
