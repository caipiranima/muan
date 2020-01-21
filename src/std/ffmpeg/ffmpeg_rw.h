/**
 * Interface with ffmpeg. It was based on ffmpeg example program.
 \file ffmpeg_rw.h
 */
/*
 * Libavformat API example: Output a media file in any supported
 * libavformat format. The default codecs are used.
 * 
 * Copyright (c) 2003 Fabrice Bellard
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.  
 */
#ifndef FFMPEG_OUTPUT_H
#define FFMPEG_OUTPUT_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.1415926535897931
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifdef WIN32
#define inline _inline
#endif
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#ifdef __cplusplus
}
#endif

#undef exit

#define STREAM_PIX_FMT PIX_FMT_YUV420P /*default - mpeg*/
#define STREAM_FRAME_RATE 30    //mcv
#define STREAM_NB_FRAMES  1000000 //mcv | lcv - check this


/**************************************************************/
/* video output */
/**************************************************************/
AVStream *add_video_stream(AVFormatContext *oc, int codec_id, int width, int height);
void open_video(AVFormatContext *oc, AVStream *st);
void write_video_frame(AVFormatContext *oc, AVStream *st, int frame_count, unsigned char* imgFrame, int key, int src_width, int src_height);
void close_video(AVFormatContext *oc, AVStream *st);


/**************************************************************/
/* audio output */
/**************************************************************/
AVStream *add_audio_stream(AVFormatContext *oc, int codec_id);
void open_audio(AVFormatContext *oc, AVStream *st);
void get_audio_frame(int16_t *samples, int frame_size, int nb_channels);
void write_audio_frame(AVFormatContext *oc, AVStream *st);
void close_audio(AVFormatContext *oc, AVStream *st);

#endif
