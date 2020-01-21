/**
 * This file represents Muan Player Main file.
 \file main_player.cpp
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
#include <string.h>
#include "defaults.h"
#include "imglist.h"
#include "ui_player.h"
#include "imgviewer.h"

static Fl_Window *w;
static MuanPlayerUI *p;

#define MUAN_PL
#include "../inc/settings.h"


void redraw_panel( void* ){
  p->imgv->redraw();  //vai executar o draw definido na classe imgviewer	
  if (p->imgv->imgl!=NULL && p->imgv->imgl->current!=NULL)
  	p->sl_play->value(p->imgv->imgl->current->frame_number);
  else
    p->sl_play->value(0);
}


int main( int argc, char **argv) 
{
  p = new MuanPlayerUI();
  w = p->make_window();

  p->imgv->imgvmode = _MUAN_PLAYER;
  p->set_language_ui();
  readPreferences();

  p->imgv->initialize(iframe_w, iframe_h);
#ifndef __APPLE__
  p->load_file(argv[1]);
#endif
  w->show( 1, argv );
  Fl::add_idle( redraw_panel );
  
  return  Fl::run();
}
