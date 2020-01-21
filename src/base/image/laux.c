/**
 * This file implements the auxiliary routines about vector, color, memory and io.
 \file laux.c
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
#include <stdlib.h>
#include <signal.h>

#include "laux.h"

void *emalloc(int siz)
{
  void *buf, *malloc();

  if ((buf = malloc(siz)) == (char *)0)
    error("(emalloc) can't alloc space");
  return buf;
}

void efree(void *buf)
{
  if (buf) free(buf);
}

void error(char *msg)
{
  fprintf(stderr, "MUAN: fatal error: %s\n(exiting)\n", msg);
  exit(1); // fix this..
}

