/**
 * This file implements the video.h interface.
 \file video.cpp
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
#include "video.h"

#define IF_DEBUG(S) {if(0) S;}

#include "CameraTool.h"
#include "RingBuffer.h"

#define MILLI_CONV(X) ((X)/1000)
	
static bool running_;
static bool error_;
static bool using_thread_;
static int width_ = -1;
static int height_ = -1;
static int fps_ = 0;
static int sourceDepth_, destDepth_;
static int bytesPerSourcePixel_, bytesPerDestPixel_;
static int sleeptime_;
static int framenumber_;
static int bufsize_;

const char* camera_config_ = "none";

static CameraEngine *camera_ = 0;

static unsigned char *cameraBuffer_ = NULL;
static unsigned char *cameraWriteBuffer = NULL; 
static unsigned char *cameraBufferToRead = NULL; 
static unsigned char *cameraBufferToWrite = NULL; 

static RingBuffer *ringBuffer;
static Image *image_buffer = NULL;

#ifndef WIN32
static pthread_t capturethread;
#endif

/** Sleep
 */
void sleep_for_video(int stime)
{
#ifndef WIN32
      usleep(stime);
#else
      Sleep(MILLI_CONV(stime));
#endif
}

/** Function executed by the capture thread to get a new frame
 */
void *getFrameFromCameraF(void *p) 
{ 
  while (camera_->stillRunning()) { 
    cameraBuffer_ = camera_->getFrame();
    if (cameraBuffer_!=NULL) {
      cameraBufferToWrite = ringBuffer->getNextBufferToWrite();
      if (cameraBufferToWrite!=NULL) {
	memcpy(cameraBufferToWrite,cameraBuffer_,ringBuffer->size());
	framenumber_++;
	ringBuffer->writeFinished();
      }
      sleep_for_video(10*sleeptime_);
    } else {
      if (!camera_->stillRunning()) {
	running_=false;
	error_=true;
      } else {
	sleep_for_video(10*sleeptime_);
      }
    }
  }
  return(0);
}

/** Allocate internal buffers
 */
void allocateBuffers()
{
  bytesPerSourcePixel_ = sourceDepth_/8;	
  bytesPerDestPixel_ = destDepth_/8;
  cameraWriteBuffer = new unsigned char[width_*height_*bytesPerDestPixel_];
  cameraBuffer_ = NULL;
  ringBuffer = new RingBuffer(width_*height_*bytesPerSourcePixel_);
  bufsize_ = width_*height_*bytesPerDestPixel_;
}

/** Read config file and set the camera
 * @return success or failure.
 */
bool setupCamera(const char *config_file, int cam_type) 
{
  camera_ = CameraTool::setCamera(config_file, cam_type);	
  if (camera_ == NULL)
    return false;
  bool success = camera_->initCamera();
  if(success) {
    width_ = camera_->getWidth();
    height_ = camera_->getHeight();
    fps_ = camera_->getFps();
    if (camera_->getColour()) {
      sourceDepth_ = 24;
      destDepth_ = 24;
    } else {
      sourceDepth_ = 8;
      destDepth_ = 8;
      return false;  // only RGB
    }
    return true;
  } else {
    camera_->closeCamera();
    delete camera_;
    return false;
  }
}

/** Gets a new Frame
 * @return the frame captured.
 */
void *get_newframe(unsigned char *buffer) 
{
  unsigned char *frameWriteBuffer;
  if (buffer != NULL)
    frameWriteBuffer = buffer;
  else
    frameWriteBuffer = cameraWriteBuffer;
  if (using_thread_) {
    cameraBufferToRead = NULL;
    while (cameraBufferToRead == NULL) { 
      cameraBufferToRead = ringBuffer->getNextBufferToRead();
      if (cameraBufferToRead != NULL)
	break;
      sleep_for_video(sleeptime_);
      if(!running_) { 
	return NULL;
      }
    }
    memcpy(frameWriteBuffer,cameraBufferToRead,bufsize_);
    ringBuffer->readFinished();
  } else {
    while ((cameraBufferToRead = camera_->getFrame()) == NULL && camera_->stillRunning()) {
      sleep_for_video(sleeptime_);
    }
    if (cameraBufferToRead == NULL || !camera_->stillRunning()) {
      running_ = false;
      return NULL;
    }
    memcpy(frameWriteBuffer,cameraBufferToRead,bufsize_);
  }
  return frameWriteBuffer;
}

void init_vars()
{
#ifndef WIN32
  using_thread_ = true;
#else
  using_thread_ = false;
#endif
  sleeptime_ = 1000;
  framenumber_=0;
  bufsize_ = 0;
}


int copy_image( Image *i, void *buffer)
{
  int u_i0, v_i0, u_c0, v_c0, w, h;
  int u_i, v_i, u_c, v_c, u, v;
  unsigned char *p = cameraWriteBuffer;

  if (i->w < width_) {
    u_c0 = (width_ - i->w) / 2;
    u_i0 = 0;
    w = i->w;
  } else {
    u_c0 = 0;
    u_i0 = (i->w - width_) / 2;;
    w = width_;
  }
  if (i->h < height_) {
    v_c0 = (height_ - i->h) / 2;
    v_i0 = 0;
    h = i->h;
  } else {
    v_c0 = 0;
    v_i0 = (i->h - height_) / 2;;
    h = height_;
  }
  for (v_i = 0; v_i < i->h; v_i++) 
    for (u_i = 0; u_i < i->w; u_i++) 
      img_putc(i, u_i, v_i, c_make(50.,50.,50.));
  for (v = 0, v_i = v_i0, v_c = v_c0; v < h; v++, v_i++, v_c++) {
    for (u = 0, u_i = u_i0, u_c = u_c0; u < w; u++, u_i++, u_c++) {
      int r, g, b;
      r = p[(u_c + ((v_c)*width_))*3];
      g = p[(u_c + ((v_c)*width_))*3 + 1];
      b = p[(u_c + ((v_c)*width_))*3 + 2];
      img_putc(i, u_i, i->h - 1 - v_i ,c_make(r,g,b));
    }
  }
  return TRUE;
}

////////////////////////// Video API ///////////////////////////


/** Return image horizontal dimension.
 */
int video_w( void )
{
  if ( width_ < 0 ) { 
    fprintf(stderr, "Video not initialized %d\n", width_); 
    width_ = IMG_DV_W; 
    height_= IMG_DV_H;
  }
  return width_;
}

/** Return image vertical dimension.
 */
int video_h( void )
{
  return height_;
}

/** Open communication with video device.
 * @return the Image created.
 */
int video_open(const char *config_fname, int cam_type) 
{
  int ret;

  init_vars();
  ret = setupCamera(config_fname, cam_type);
  if (ret == false) {
    camera_ = NULL;
    fprintf(stderr, "NO CAMERA FOUND\n");
    return FALSE;
  }
  allocateBuffers();
  camera_->startCamera();
  running_ = true;
  if (using_thread_) {
    ringBuffer = new RingBuffer(width_*height_*bytesPerSourcePixel_);
    video_startThread();
  }   
  return TRUE;
}

/** Close communication with video device.
 */
void video_close( void ) 
{
  if (camera_ == NULL) 
    return;
  video_stopReceive();
  camera_->closeCamera();
  delete camera_;
}


/** Gets the frame
 * @param f the frame.
 * @return TRUE if success, else returns FALSE
 */
int video_getframe( Frame *f ) 
{ 
  void *buffer;
  if (camera_ == NULL)
    return false;
  if (f->GetWidth() ==  width_ && f->GetHeight() == height_) {
    return (get_newframe(f->GetData()) != NULL);
  } else { 
    if ((buffer = get_newframe(NULL)) == NULL) 
      return false;
    if (image_buffer == NULL)
      image_buffer = img_create(f->GetWidth(), f->GetHeight());
    copy_image(image_buffer, buffer);
    f->StoreRGB(image_buffer->c);
    return true;
  }
}
	

/**Start receiving images from device.
 */
void video_startReceive() 
{ 
  int ret;
  if (camera_ == NULL)
    return;
  if (!camera_->stillRunning())
    ret = camera_->startCamera();
  if (ret)
    running_ = true;
}


/**Stop receiving images from device.
 */
void video_stopReceive() 
{
  if (camera_ == NULL)
    return;
  if (camera_->stillRunning())
    camera_->stopCamera();
  running_ = false;
}


/**Stop the thread for receiving images from device.
 */
void video_stopThread() 
{
  if (using_thread_) {
    running_ = false;
#ifndef WIN32
    pthread_exit(&capturethread);
    pthread_join(capturethread, NULL);
#endif
  }
}

	
/**Start the thread for receiving images from device.
 */
void video_startThread() 
{
  if (using_thread_) {
    running_ = true;
#ifndef WIN32
    pthread_create( &capturethread, NULL, getFrameFromCameraF, NULL );
#endif
  }
}

  
