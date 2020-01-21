/**
 * Filter support.
 \file filter.cpp
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
#include "lua.hpp"

#include "luaplug.h"
#include "builtins.h"
#include "filter.h"

extern lua_State* L;

// CAMERA FILTER

int camfilter_init(Frame *f, int n)
{
  setimage(f->GetImage(), 0);
  lua_pushinteger(L, n);
  lua_pushinteger(L, f->GetWidth());
  lua_pushinteger(L, f->GetHeight());
  return docall("camfilter_init", 3);
}

int camfilter_exec(Frame *f)
{
  setimage(f->GetImage(), 0);
  lua_pushinteger(L, f->GetWidth());
  lua_pushinteger(L, f->GetHeight());
  return docall("camfilter_exec", 2);
}

int camfilter_close(void)
{
  return docall("camfilter_close",0);
}


// PROCESS FILTER

int procfilter_init(Frame *f, int n)
{
  setimage(f->GetImage(), 0);
  lua_pushinteger(L, n);
  lua_pushinteger(L, f->GetWidth());
  lua_pushinteger(L, f->GetHeight());
  return docall("procfilter_init", 3);
}

int procfilter_exec(Frame *f, int i)
{
  setimage(f->GetImage(), 0);
  lua_pushinteger(L, f->GetWidth());
  lua_pushinteger(L, f->GetHeight());
  lua_pushinteger(L, i);
  return docall("procfilter_exec", 3);
}

int procfilter_close(void)
{
  return docall("procfilter_close",0);
}


