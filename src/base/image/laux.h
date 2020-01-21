/**
 * Auxiliary definitions to be used by Image.
 \file laux.h
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
#ifndef AUX_H
#define AUX_H 1

#include <stdio.h>

#ifdef _DEBUG_
#define DEBUG1(S) fprintf(stderr, S);
#else
#define DEBUG1(S)
#endif

/****************************/
/* memory allocation macros */
/****************************/

/* create a new instance of an array of size n  */
#define NEWARRAY(n, x)	(struct x *)(emalloc((unsigned)((n)*sizeof(struct x))))

/* create a new instance of a structure */
#define NEWSTRUCT(x)	(struct x *)(emalloc((unsigned)sizeof(struct x)))

/* create a new instance of a type */
#define NEWTYPE(x)	(x *)(emalloc((unsigned)sizeof(x)))

/* create a new instance of an array */
#define NEWTARRAY(n, x)	(x *)(emalloc((unsigned)((n)*sizeof(x))))


/************/
/* booleans  */
/************/

#define TRUE		1
#define FALSE		0

typedef int Bool;
typedef unsigned char Byte;

void *emalloc(int siz);
void efree(void *buf);

void error(char *msg);

#endif
