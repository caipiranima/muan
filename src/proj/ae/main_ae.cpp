/**
 * This file represents Muan Anima Escola Main file.
 \file main_ae.cpp
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
#ifdef WIN32
#include <basetsd.h>
#endif

#include <stdio.h>
#include <FL/fl_ask.H>
#include "defaults.h"
#include "lang_ui.h"
#include "imglist.h"
#include "ui_ae.h"
#include "imgviewer.h"
#include "sndfile-play.h"

#include <string.h>
#include "video.h"
#include "plugin.h"

static Fl_Window *w;
static MuanUI *p;
static char crt_frame[10];
static char crt_frame_duration[10];
static char crt_frame_pos[10];
static clock_t clk_start;

#define MUAN_AE
#include "../inc/settings.h"


void show_splash (void)
{
  p->make_splash_window();
  p->win_splash->end();
  p->win_splash->show();

  while ((p->btn_iniciar->value()==0) && (p->win_splash->shown()))
    Fl::wait(); 

  p->win_splash->cursor(FL_CURSOR_WAIT);
  Fl::check();

  if (!p->win_splash->shown()) {
    free(p->win_splash);
    free(w);
    free(p);
    exit(1);
  }
}


int main( int argc, char **argv) 
{
  p = new MuanUI();	
  w = p->make_window();
  p->imgv->imgvmode = _MUAN_FULL;
	
  readPreferences();
  plugin_setup(MUAN_ROOT_DIR);

  if(p->show_splash)
      show_splash();

  video_open(config_filename(), p->camera_connection);
  if (! isize_override) {
    p->imgl_w = iframe_w = video_w();
    p->imgl_h = iframe_h = video_h();
  }
  p->imgv->initialize(iframe_w, iframe_h);	

  if(p->show_splash) {
      p->win_splash->hide();
      p->win_splash->cursor(FL_CURSOR_DEFAULT);
      Fl::check();
      free(p->win_splash);
  }
  
  w->show( argc, argv );

  Fl::add_idle( redraw_panel );
  if (p->auto_save)
    Fl::add_timeout(p->auto_save_time, &autoSave);
  return  Fl::run();
}
