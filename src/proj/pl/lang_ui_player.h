/**
 * This file contains the labels, hints and messages specifics for Muan Player user interface in diferent languages.
 \file lang_ui_player.h
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

#ifndef LANG_UI_PLAYER_H
#define LANG_UI_PLAYER_H

#include "defaults.h"


//==============================================================================
#ifdef LANG_EN
//==============================================================================

  #define LBL_WIN_PRINCIPAL_PLAYER "IMPA-VISGRAF/ Anima Mundi      MUAN-PLAYER v8.2      Technological Partnership IBM"
  #define HNT_WIN_PRINCIPAL_PLAYER ""

  #define MANUAL_FILE_PLAYER "/usr/local/share/muan/manual/muan_player_en.html"

  #define LBL_EDT_FILE_NAME_PLAYER "File:"
  #define HNT_EDT_FILE_NAME_PLAYER ""

  #define MSG_FILE_NOT_EXISTS "File not found. Try another."

  
#else

//==============================================================================
#ifdef LANG_SP
//==============================================================================

  #define LBL_WIN_PRINCIPAL_PLAYER "IMPA-VISGRAF/ Anima Mundi        MUAN-PLAYER v8.2        Sociedad Tecnol\363gica IBM"
  #define HNT_WIN_PRINCIPAL_PLAYER ""

  #define MANUAL_FILE_PLAYER "/usr/local/share/muan/manual/muan_player_sp.html"

  #define LBL_EDT_FILE_NAME_PLAYER "Archivo:"
  #define HNT_EDT_FILE_NAME_PLAYER ""

  #define MSG_FILE_NOT_EXISTS "Archivo no encontrado. Intente otro."


//==============================================================================
#else   //LANG_PT
//==============================================================================
  #define LBL_WIN_PRINCIPAL_PLAYER "IMPA-VISGRAF/ Anima Mundi         MUAN-PLAYER v8.2        Parceria Tecnol\363gica IBM"
  #define HNT_WIN_PRINCIPAL_PLAYER ""

  #define MANUAL_FILE_PLAYER "/usr/local/share/muan/manual/muan_player_pt.html"

  #define LBL_EDT_FILE_NAME_PLAYER "Arquivo:"
  #define HNT_EDT_FILE_NAME_PLAYER ""

  #define MSG_FILE_NOT_EXISTS "Arquivo n\343o encontrado. Tente outro."

  
#endif

#endif
#endif
