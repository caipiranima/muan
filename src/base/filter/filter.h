/**
 * Filter support.
 \file filter.h
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
#ifndef FILTER_H
#define FILTER_H

#include "frame.h"

extern "C" {
#include "image.h"
}

// Camera Filter

int camfilter_init(Frame *f, int duration);
int camfilter_exec(Frame *f);
int camfilter_close(void);

// Process Filter

int procfilter_init(Frame *f, int n);
int procfilter_exec(Frame *f, int i);
int procfilter_close(void);

#endif
