/*
* Copyright (C) 2001-2007 Dan Dennedy <dan@dennedy.org>
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software Foundation,
* Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

#ifndef PREFERENCES_H
#define PREFERENCES_H 1

enum { AVI, PLAYLIST, RAW_DV, QT, UNKNOWN_FORMAT };
enum { PAL_FORMAT, NTSC_FORMAT, AVI_DV1_FORMAT, AVI_DV2_FORMAT, QT_FORMAT, RAW_FORMAT, TEST_FORMAT, UNDEFINED };
enum { DISPLAY_XX, DISPLAY_GDKRGB, DISPLAY_GDKRGB32, DISPLAY_XV, DISPLAY_SDL };

enum { NORM_UNSPECIFIED = 0, NORM_PAL = 1, NORM_NTSC = 2 };
enum { AUDIO_32KHZ = 0, AUDIO_44KHZ = 1, AUDIO_48KHZ = 2 };
enum { ASPECT_43 = 0, ASPECT_169 = 1 };

/* For jogShuttle selections, some include an a couple of classes */
#include <string>
#include <map>
#include <utility>
#include <vector>
using std::string;
using std::map;
using std::pair;
using std::make_pair;
using std::vector;

//mcv aqui: #include <glib.h>

#endif
