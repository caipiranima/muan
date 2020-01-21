/**
 * This file implements a video encoder interface, reading and writing avi, mpg and jpg files.
 \file video_encoder.cpp
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
#include "video_encoder.h"
#include "defaults.h"
#include <FL/filename.H>
#include <assert.h>
#include <math.h>

#define V_NO_AUDIO 1
#define V_F_DUPL 1

static int sws_flags = SWS_FAST_BILINEAR;
static int _muan_load_mode = 0;

/**
 * Writes a file in the AVI format.
 *@param fname the file name.
 *@param imgl the ImageList.
 *@param file_format the file format to be writed.
 *@param max_frames the maximum frame supported number.
 *@param max_file_size the maximum file size suported.
 *@param time_stamp the file time_stamp
 *@param isOpenDML 
 *@return true if the file was successfully writed, false otherwise.
 */
/*============================================================================*/
bool VideoEncoder::avi_write(char *fname, ImgList *imgl, int file_format, int max_frames,
                                  off_t max_file_size, bool time_stamp, bool isOpenDML, int w, int h) 
/*============================================================================*/
{
  return avffmpeg_write(imgl, fname, w, h);
}

/**
 *Reads a specified file.
 *@param imgl the ImageList where the file will be stored.
 *@param fname the file name.
 *@param load_mode -- 0 if compare muan number; 1 if compare entire frame; 2 if not verifiy duplication.
 *@return true if the file was successfully read, false otherwise.
 */
/*============================================================================*/
bool VideoEncoder::avi_read( ImgList *imgl, const char *fname, int load_mode)
/*============================================================================*/
{
  _muan_load_mode = load_mode;
  return avffmpeg_read(imgl, fname);
}

/*============================================================================*/
bool VideoEncoder::mpg_write( ImgList *imgl, const char *fname, int w, int h)
/*============================================================================*/
{
  return avffmpeg_write(imgl, fname, w, h);
}

/*============================================================================*/
bool VideoEncoder::mpg_read( ImgList *imgl, const char *fname)
/*============================================================================*/
{
  return avffmpeg_read(imgl, fname);
}

/**
 *Compare 2 frames.
 *@param load_mode how to compare: 0 if compare entire frame; 1 if not verifiy duplication.
 *@return true if they coincide, false otherwise.
 */
/*============================================================================*/
bool VideoEncoder::verify_frame_duplication(unsigned char *i1, unsigned char *i2, int load_mode, int w, int h, int key) 
/*============================================================================*/
{
    int i, init;
    bool value = false;

    if (i1 == NULL)
      return false; 
    switch (load_mode) {
    case 2: return verify_image_duplication(i1, i2, w,  h);
      break;
    case 1: return FALSE;
      break;
    case 0:
      return (key == 0);
      break;
    default: fprintf(stderr, "Invalid LOAD_MODE. Check preferences file. %d\n", load_mode);
      return FALSE;
      break;
    }
    return value;
}

/*============================================================================*/
bool VideoEncoder::verify_image_duplication(unsigned char *i1, unsigned char *i2, int w,  int h) 
/*============================================================================*/
{
  int k, d;
  double diff = 0;
  for (k = 1; k < (w*h*3); k+=3) {
	d = (int)(i1[k]) - (int)(i2[k]);
	diff += (d > 0)? d : -d;
  }
  return (diff < 0.5*w*h);
}

/*============================================================================*/
bool VideoEncoder::jpg_write( ImgList *imgl, const char *fname, int quality)
/*============================================================================*/
{
  int frame_num=0; 
  char sname[255];
  
  Image* auximg = img_create(imgl->img_w, imgl->img_h); 
  
  for ( ImgNode *imgnode = imgl->head; imgnode != NULL; imgnode = imgnode->next )  {
    sprintf(sname, "%s_%05d.jpg", fname, ++frame_num);
    imgnode->frame->ExtractRGB(auximg->c);
    write_JPEG_file ((unsigned char*)auximg->c, imgl->img_w, imgl->img_h, sname, quality);
  }
  img_free(auximg);
  return true;
}


/*============================================================================*/
bool VideoEncoder::jpg_read( ImgList *imgl, const char *dirname, int load_mode)
/*============================================================================*/
{     
  int numlist, i;
  struct dirent **namelist;
  char fname[255];
  uint8_t *image;
  Frame* frameAnt = NULL;
  
  if (fl_filename_isdir(dirname) <= 0) {
    printf("Error: jpg_read not reading a directory.\n");
    return FALSE;
  }
  numlist = fl_filename_list(dirname, &namelist, fl_casenumericsort);
  //importing jpg files
  for (i=0;i<numlist;i++) {
    if ((strcmp(fl_filename_ext(namelist[i]->d_name), ".JPG")==0) || (strcmp(fl_filename_ext(namelist[i]->d_name), ".jpg")==0)){
      strcpy(fname, dirname);
      if (fname[strlen(fname)-1] != '/'  )
        strcat(fname, "/");
      Frame *frame = new Frame(imgl->img_w, imgl->img_h);
      image = read_JPEG_file(strcat(fname, namelist[i]->d_name), imgl->img_w, imgl->img_h);
      if (image != NULL) {
        frame->StoreRGB(image);
        imglist_addimg(imgl, imgnode_alloc( frame , 3, 1));
        free(image);
      }
    }
  }
  //liberando memoria
  for (i=numlist; i > 0;) {
    free((void*)(namelist[--i]));
  }
  free((void*)namelist);
  return true; 
}


/*================================================================================*/
bool VideoEncoder::avffmpeg_write( ImgList *imgl, const char *fname, int w, int h)
/*================================================================================*/
{
    const char *filename;
    AVOutputFormat *fmt;
    AVFormatContext *oc;
    AVStream *audio_st, *video_st;
    double audio_pts, video_pts;
    int i, fno = 0;

    if (test_file(fname, "a+") == FALSE) {
      ui_message("AV_WRITE: could not write to file");
      return false;
    }
    /* initialize libavcodec, and register all codecs and formats */
    av_register_all();
    filename = fname;

    /* auto detect the output format from the name. default is mpeg. */
    fmt = guess_format(NULL, filename, NULL);
    if (!fmt) {
        printf("Could not deduce output format from file extension: using MPEG.\n");
        fmt = guess_format("mpeg", NULL, NULL);
    }
    if (!fmt) {
        fprintf(stderr, "Could not find suitable output format\n");
        exit(1);
    }    
    /* allocate the output media context */
    oc = av_alloc_format_context();
    if (!oc) {
        fprintf(stderr, "video write: Memory error\n");
        exit(1);
    }
    oc->oformat = fmt;
#ifndef WIN32
    snprintf(oc->filename, sizeof(oc->filename), "%s", filename);
#else
    _snprintf(oc->filename, sizeof(oc->filename), "%s", filename);
#endif
    /* add the audio and video streams using the default codecs and initialize */
    video_st = NULL;
    audio_st = NULL;
    if (fmt->video_codec != CODEC_ID_NONE) {
	  if( w > 0 && h > 0 )
		  video_st = add_video_stream(oc, fmt->video_codec, w, h);
	  else
		  video_st = add_video_stream(oc, fmt->video_codec, imgl->img_w, imgl->img_h);
    }
#ifndef V_NO_AUDIO
    if (fmt->audio_codec != CODEC_ID_NONE) {
        audio_st = add_audio_stream(oc, fmt->audio_codec);
    }
#endif
    /* set the output parameters (must be done even if no parameters). */
    if (av_set_parameters(oc, NULL) < 0) {
        fprintf(stderr, "Invalid output format parameters\n");
        exit(1);
    }
    dump_format(oc, 0, filename, 1);

    /* now that all the parameters are set, we can open the audio and
       video codecs and allocate the necessary encode buffers */
    if (video_st)
        open_video(oc, video_st);
    if (audio_st)
        open_audio(oc, audio_st);

    /* open the output file, if needed */
    if (!(fmt->flags & AVFMT_NOFILE)) {
        if (url_fopen(&oc->pb, filename, URL_WRONLY) < 0) {
            fprintf(stderr, "Could not open '%s'\n", filename);
            exit(1);
        }
    }    
    /* write the stream header, if any */
    av_write_header(oc);
    
    int frame_count=0;  //mcv
    for ( ImgNode *imgnode = imgl->head; imgnode != NULL; imgnode = imgnode->next)  {      
      fno++;
      for ( int k  = 1; k <= imgnode->frame_duration; k++ ) {  
		int kf = (k == 1)? TRUE : FALSE;
        frame_count++;
        /* compute current audio and video time */
        if (audio_st)
            audio_pts = (double)audio_st->pts.val * audio_st->time_base.num / audio_st->time_base.den;
        else
            audio_pts = 0.0;
        if (video_st)
            video_pts = (double)video_st->pts.val * video_st->time_base.num / video_st->time_base.den;
        else
            video_pts = 0.0;
        /* write interleaved audio and video frames */
        if (!video_st || (video_st && audio_st && audio_pts < video_pts)) {
		  write_audio_frame(oc, audio_st); // lcv: BUG - change this later
        } else {
		  write_video_frame(oc, video_st, frame_count, imgnode->frame->GetData(), kf, imgl->img_w, imgl->img_h);
		}
      } //for do frame_duration
    } //for do imgl
    /* close each codec */
    if (video_st)
        close_video(oc, video_st);
    if (audio_st)
        close_audio(oc, audio_st);

    /* write the trailer, if any */
    av_write_trailer(oc);
    
    /* free the streams */
    for(i = 0; i < oc->nb_streams; i++) {
        av_freep(&oc->streams[i]->codec);        
        av_freep(&oc->streams[i]);
    }
    if (!(fmt->flags & AVFMT_NOFILE)) {
        /* close the output file */
        url_fclose(oc->pb);
    }
    /* free the stream */
    av_free(oc);

    return true;
}


/*============================================================================*/
bool VideoEncoder::avffmpeg_read( ImgList *imgl, const char *fname)
/*============================================================================*/
{
    AVFormatContext *pFormatCtx;
    int             i, videoStream;
    AVCodecContext  *pCodecCtx;
    AVCodec         *pCodec;
    AVFrame         *pFrame; 
    AVFrame         *pFrameRGB;
    AVPacket        packet;
    int             frameFinished;
    int             numBytes;
    uint8_t         *buffer;

    int nCopies;
    bool first = true;
    Frame *frame = NULL;

    register uint8_t * imageptr;
    register uint8_t * readptr;
    unsigned char   *pFrameRGBAnt = NULL;

    static struct SwsContext *img_convert_ctx;   //mcv: 21/12/2007

    fprintf(stderr, "MUAN Load Mode %d\n", _muan_load_mode);
    // Register all formats and codecs
    av_register_all();

    // Open video file
    if(av_open_input_file(&pFormatCtx, fname, NULL, 0, NULL)!=0)
        return -1; // Couldn't open file

    // Retrieve stream information
    if(av_find_stream_info(pFormatCtx)<0)
        return -1; // Couldn't find stream information

    // Dump information about file onto standard error
    dump_format(pFormatCtx, 0, fname, false);

    // Find the first video stream
    videoStream=-1;
    for(i=0; i<pFormatCtx->nb_streams; i++)
        if(pFormatCtx->streams[i]->codec->codec_type==CODEC_TYPE_VIDEO)  {
	  videoStream=i;
	  break;
	}
    if(videoStream==-1)
        return -1; // Didn't find a video stream

    // Get a pointer to the codec context for the video stream
    pCodecCtx=pFormatCtx->streams[videoStream]->codec;

    // Find the decoder for the video stream
    pCodec=avcodec_find_decoder(pCodecCtx->codec_id);
    if(pCodec==NULL)
        return -1; // Codec not found

    // Open codec
    if(avcodec_open(pCodecCtx, pCodec)<0)
        return -1; // Could not open codec

    if ( (pCodecCtx->width != imgl->img_w) || (pCodecCtx->height != imgl->img_h) )  {
      fprintf(stderr, "Input resolution differs from MUAN defaults -");
      fprintf(stderr, "(%d, %d) - scaling video\n", pCodecCtx->width, pCodecCtx->height);
    }
/*mcv: 21/12/2007    
    // Hack to correct wrong frame rates that seem to be generated by some codecs
    if(pCodecCtx->frame_rate>1000 && pCodecCtx->frame_rate_base==1)
        pCodecCtx->frame_rate_base=1000;
*/
    // Allocate video frame
    pFrame=avcodec_alloc_frame();

    // Allocate an AVFrame structure
    pFrameRGB=avcodec_alloc_frame();
    if(pFrameRGB==NULL)
        return -1;

    // Determine required buffer size and allocate buffer
    numBytes=avpicture_get_size(PIX_FMT_RGB24, imgl->img_w, imgl->img_h);
    buffer=new uint8_t[numBytes];

    // Assign appropriate parts of buffer to image planes in pFrameRGB
    avpicture_fill((AVPicture *)pFrameRGB, buffer, PIX_FMT_RGB24, imgl->img_w, imgl->img_h);

    uint8_t *prev_image = NULL;
    uint8_t *image = new unsigned char[imgl->img_w * imgl->img_h *3];
    memset(image, '0', imgl->img_w * imgl->img_h *3);
    // Read frames, convert them to Frame structure and insert into imgList
    nCopies = 1;
    while(av_read_frame(pFormatCtx, &packet)>=0)  {
        // Is this a packet from the video stream?
        if(packet.stream_index==videoStream)  {
            // Decode video frame
            avcodec_decode_video(pCodecCtx, pFrame, &frameFinished, packet.data, packet.size);

            // Did we get a video frame?
            if(frameFinished) {
	      // Convert the image from its native format to RGB
	        //mcv: 21/12/2007 ini
                img_convert_ctx = sws_getContext(pCodecCtx->width,   
                                   pCodecCtx->height,
                                   pCodecCtx->pix_fmt,
                                   imgl->img_w,   
                                   imgl->img_h,
                                   PIX_FMT_RGB24,
                                   sws_flags, NULL, NULL, NULL);
		sws_scale(img_convert_ctx, 
			    pFrame->data,
			    pFrame->linesize,
			    0, pCodecCtx->height, 
			    pFrameRGB->data, 
			    pFrameRGB->linesize);
		//mcv: 21/12/2007 fim
                imageptr = image;
                readptr = pFrameRGB->data[0];
                for (int h=1; h<=imgl->img_h; h++) {
                  memcpy(imageptr, readptr, pFrameRGB->linesize[0]);
		  imageptr = image + (h*imgl->img_w)*3;
                  readptr = pFrameRGB->data[0]+h*pFrameRGB->linesize[0];
                }              
		// VERIFY_FRAME_DUPLICATION
#if V_F_DUPL
		prev_image = (frame == NULL)? NULL : frame->GetData();
		if (verify_frame_duplication (prev_image, image, _muan_load_mode, imgl->img_w, imgl->img_h, packet.flags)) {
		  nCopies++;
		} else {
		  if (prev_image != NULL)
		    imglist_addimg (imgl, imgnode_alloc (frame, 3, nCopies));
		  frame = new Frame(imgl->img_w, imgl->img_h);
		  frame->StoreRGB(image);
		  nCopies = 1;
		}
#else
                frame = new Frame(imgl->img_w, imgl->img_h);
		frame->StoreRGB(image);
                imglist_addimg( imgl, imgnode_alloc(frame, 3, 1) );
#endif
            }
        }
        // Free the packet that was allocated by av_read_frame
        av_free_packet(&packet);
    }
#if V_F_DUPL
    imglist_addimg(imgl, imgnode_alloc (frame, 3, nCopies));
#endif
    free(image);
    
    // Free the RGB image
    delete [] buffer;
    av_free(pFrameRGB);
    av_free(pFrameRGBAnt);

    // Free the YUV frame
    av_free(pFrame);

    // Close the codec
    avcodec_close(pCodecCtx);

    // Close the video file
    av_close_input_file(pFormatCtx);

    return true;
}
