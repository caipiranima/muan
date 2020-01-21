/**
 * MUAN plugin support
 \file plugin.cpp 
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
#include "plugin.h"
#include "luaplug.h"
#include "filter.h"

#if _MSC_VER
#define snprintf _snprintf
#endif

static char *root_dir = "";
static char module_path[1024];
static char *module_dir[] = { "camera", "memory", "none" };
static int module_isloaded[] = { FALSE, FALSE, FALSE };

int plugin_checktype(int type)
{
  if (type != PLUGIN_CAM && type != PLUGIN_MEM)
    return plugin_error("Select", "wrong module type");
  return 0;
}

char * plugin_path(int type)
{
  plugin_checktype(type);
  snprintf(module_path, 1024, "%s/plugins/%s", root_dir, module_dir[type]);
  return module_path;
}

int plugin_setup(char *root)
{
  root_dir = root;
  initlua();
  return 1;
}

int plugin_select(int type, char *filename)
{
  plugin_checktype(type);
  module_isloaded[type] = load_plugin(filename);
  return 1;
}

int plugin_loaded(int type)
{
  plugin_checktype(type);
  return module_isloaded[type];
}

int plugin_error(const char *msg_1, const char *msg_2)
{
  extern void ui_message(const char *s);
  char msg[1024];
  snprintf(msg, 1024, "Plugin: %s %s",  msg_1, msg_2);
  ui_message(msg);
  return -1;
}


