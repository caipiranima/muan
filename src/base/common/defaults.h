/**
 * Default values for MUAN parameters.
 \file defaults.h
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
#ifndef DEFAULTS_H
#define DEFAULTS_H

//available languages: PT (Portuguese), EN (English), SP (Spanish) - uncomment the desired one
#ifndef LANG_PT
#  ifndef LANG_EN
#    ifndef LANG_SP
#       define LANG_PT
#    endif
#  endif
#endif

#define DEF_LOAD_MODE 0
#define DEF_DURATION_DEFAULT 1
#define DEF_AUTO_SAVE 0
#define DEF_AUTO_SAVE_TIME 300
#define DEF_SAVE_PATH ""

#ifdef WIN32
    #define DEF_AUTO_SAVE_FILE "MUAN_auto_save.avi"
#else
    #define DEF_AUTO_SAVE_FILE "/tmp/MUAN_auto_save.avi"
#endif

#define DEF_PLAY_SOUND 1
#define DEF_CAMERA_CONNECTION 0
#define DEF_SHOW_SPLASH 1

#define CAM_DEFAULT 0
#define CAM_V4L     1
#define CAM_DV1394  2
#define CAM_DC1394  3
#define CAM_FILE    4
#define CAM_GST     5

#define LD_MODE_ALL_FRMS 0
#define LD_MODE_COMP_FRM 1
#define LD_MODE_MUAN_COD 2

#if defined(WIN32)
// MUAN_ROOT_DIR is defined in the CMake
#elif defined(__APPLE__)
#define MUAN_ROOT_DIR "/Applications/muan/"
#else // Linux
//#define MUAN_ROOT_DIR "/usr/local/share/muan/"
#define MUAN_ROOT_DIR "/usr/share/muan/"
#endif

const char* config_filename();
int test_file(const char *fname, const char *mode);
void writePreferences (void);
int ui_choice(const char *s, const char *cancel, const char *yes, const char *no);
void ui_message(const char *s);
void ui_setfilter(int stat);
void ui_beep(void);

#endif
