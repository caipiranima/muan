/**
 * This file represents the interface with libjpeg library and was based on libjpeg example program.
 \file jpeg.h
 */
/*
 * Copyright (C) 1991-1998, Thomas G. Lane.
 * This file is part of the Independent JPEG Group's software.
 * For conditions of distribution and use, see the accompanying README file.
*/

#ifndef JPEG_H
#define JPEG_H

#include <stdio.h>
#include <jpeglib.h>

#if BITS_IN_JSAMPLE == 8
#define PUTPPMSAMPLE(ptr,v)  *ptr++ = (char) (v)
#define BYTESPERSAMPLE 1
#define PPM_MAXVAL 255
#else
#ifdef PPM_NORAWWORD
#define PUTPPMSAMPLE(ptr,v)  *ptr++ = (char) ((v) >> (BITS_IN_JSAMPLE-8))
#define BYTESPERSAMPLE 1
#define PPM_MAXVAL 255
#else
/* The word-per-sample format always puts the LSB first. */
#define PUTPPMSAMPLE(ptr,v)			\
	{ register int val_ = v;		\
	  *ptr++ = (char) (val_ & 0xFF);	\
	  *ptr++ = (char) ((val_ >> 8) & 0xFF);	\
	}
#define BYTESPERSAMPLE 2
#define PPM_MAXVAL ((1<<BITS_IN_JSAMPLE)-1)
#endif
#endif

void write_JPEG_file (unsigned char* image, int image_width, int image_height, char* filename, int quality);
unsigned char* read_JPEG_file (const char * filename, int image_width, int image_height);

#endif
