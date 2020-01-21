/**
 * This file has the control methods of the image exhibition area.
 \file imgviewer.cpp
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

#include "imgviewer.h"
#include "sndfile-play.h"


/** ImageViewer
 * Creates a new ImageViewer from an OpenGL Window.
 * @param x the x coordinate of window position.
 * @param y the y coordinate of window position.
 * @param w the image width.
 * @param h the image height.
 * @return The ImageViewer created.
 */
ImageViewer::ImageViewer(int x, int y, int w, int h) : Fl_Gl_Window( x, y, w, h, NULL )
{
  mode(FL_RGB | FL_DOUBLE);
  imgl = NULL;
  clipboard = NULL;
  frm = NULL;
  c_scale = 1;
  is_saving = FALSE;
  filter_on = FALSE;
  transp_on = FALSE;
  transp_fac = 0.75;
  flick_on = FALSE;
  flick_delay = 0.5;
  is_playing = FALSE;
  is_looping = FALSE;
  video_on = FALSE;	//always initalize in memory mode
}


	
/** Initializes ImageViewer depending on imgvmode (_MUAN_PLAYER / _MUAN_FULL)
 * _MUAN_PLAYER: Alloc image
 * _MUAN_FULL  : Alloc image and start camera connection
 * @return true for success or false if can't initialize communication with device.
 */	
bool ImageViewer::initialize(int w, int h) 
{
  bool result;
  imgl = imglist_alloc(w, h);
  clipboard = imglist_alloc(w, h);
  frm = new Frame(w, h);
  switch (imgvmode) {
    case _MUAN_PLAYER:
      result = TRUE;
      break;
    case _MUAN_FULL:
      result = video_getframe(frm);
      if ( (!result) ) {
	video_stopReceive();
      }	else {
	video_on = TRUE;
      }
      break;
    default:
      printf("MUAN Error: ImageViewer Mode undefined.\n");
      //FIXME: Tornar isso uma mensagem gráfica.
      exit(0);
      break;
  }	
  calcule_c_scale();
  return result;
}

/** 
 *Sets the camera connection mode
 * @param mode the type of connection 
 */
void ImageViewer::changeConnectMode (int mode) 
{
  int stat, last_video_on = video_on;
#if 0  // LV - look for alternative solution
  video_close();
  if ((stat = video_open(config_filename(), type)))
    video_on = ((last_video_on) && (stat));
  invalidate();
#endif
}

	
/** 
 * Does the flip operation if the user turns it on, that is, alternates the last captured image and the "live" image. 
 */
void ImageViewer::flick( void ) 
{
  static int state;
  static clock_t clk_before = 0;

  if( flick_on ){
    if( clock() - clk_before > .5 * CLOCKS_PER_SEC * ( 1 - flick_delay )){
      video_on = !video_on;
      clk_before = clock();
    }
  }
}

/** 
 *Sets up Viewport and Projection of the GLWindow
 */
void ImageViewer::init_GL() 
{
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glMatrixMode(GL_MODELVIEW); 
  glLoadIdentity();	
  glViewport( 0, 0, w(), h());	
  glMatrixMode(GL_PROJECTION);    
  glLoadIdentity();
  glOrtho( 0 , w(), 0 , h(), -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
}


/** 
 *Draws an image from the ImageList (captured image) or from the camera.
 */
void ImageViewer::draw() 
{
  Frame *c_frame;
  int x0, y0, ret;

  if (!valid()) {
    init_GL();
  }
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
    
  if (video_on || flick_on)  {
      if ((ret = video_getframe(frm)) == false) { 
	  setMessage(MSG_CAMERA_OFF);
	  video_on = FALSE;
	  return;
      } else {
	  setMessage("");
      }
      if (filter_on) {
	int capture_dur = camfilter_exec(frm);
	if (capture_dur > 0) {
	  Frame *f = new Frame(imgl->img_w, imgl->img_h);
	  f->StoreRGB(frm->GetData());
	  imglist_addimg( imgl, imgnode_alloc(f, 3, capture_dur) );
	} else if (capture_dur == -1) {
	  ui_setfilter(FALSE);
	}
      }
      flick();
  }
  x0 = (w() - (frm->GetWidth()*c_scale)) / 2;
  y0 = (h() - (frm->GetHeight()*c_scale)) / 2;
  glRasterPos2i(x0, (int)h()-y0-1);
  glPixelZoom((GLdouble)c_scale, (GLdouble)-c_scale);

  c_frame = imglist_peek_current_frame(imgl);

  if (video_on) {
    if (transp_on && flick_on == FALSE) {
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glPixelTransferf(GL_ALPHA_SCALE, transp_fac );
    }
    if (frm != NULL) 	{
      glDrawPixels(frm->GetWidth(), frm->GetHeight(), GL_RGB, GL_UNSIGNED_BYTE, frm->GetData()); 
    }
    if (transp_on && flick_on == FALSE) {
      glPixelTransferf(GL_ALPHA_SCALE, 1 - transp_fac);
      glDrawPixels(c_frame->GetWidth(), c_frame->GetHeight(), GL_RGB, GL_UNSIGNED_BYTE, c_frame->GetData() );
      glDisable(GL_BLEND);
    }
    gl_color(FL_RED);
    gl_font(FL_TIMES, 20);
    gl_draw(LBL_CAMERA, 35, h()-30);
  } else  {
    glDrawPixels(c_frame->GetWidth(), c_frame->GetHeight(), GL_RGB, GL_UNSIGNED_BYTE, c_frame->GetData() );
  }
  if (is_saving) {
      gl_color(FL_DARK_RED);
      gl_rectf((w()-500)/2, (h()-60)/2, 500, 60);
      gl_color(FL_YELLOW);
      gl_font(FL_TIMES, 50);
      if (is_saving == 2)
	gl_draw("..Processing..", (w()-500)/2, (h()-60)/2, 500, 60, FL_ALIGN_CENTER);
      else
	gl_draw(LBL_SAVING, (w()-500)/2, (h()-60)/2, 500, 60, FL_ALIGN_CENTER);
  }
}

/** 
 *Calculates c_scale of the GLWindow
 */
void ImageViewer::calcule_c_scale(){
  if ((double)frm->GetWidth()/(double)frm->GetHeight() > (double)w()/(double)h()) 
    c_scale = (double)w()/(double)frm->GetWidth();
  else
    c_scale = (double)h()/(double)frm->GetHeight();
}

/** 
 *Resizes the GLwindow
 *@param X the x coordinate of window position
 *@param Y the y coordinate of window position
 *@param W the window width.
 *@param H the window height.
 */
void ImageViewer::resize(int X, int Y, int W, int H)
{
  Fl_Gl_Window::resize(X, Y, W, H);
  calcule_c_scale();	
  invalidate();
  redraw();
}

/**
 *Plays a video.
 */
void ImageViewer::play() 
{
  //always play from the first frame.
  clock_t clk_start;
  
  is_playing = TRUE;
  if( imgl->current != NULL )
    clk_start = clock();
  while( is_playing == TRUE && imgl->current != NULL){
    while(clock() - clk_start >= .01*CLOCKS_PER_SEC*imgl->current->time_stamp ) {      
      if( imgl->current->next == NULL) {
        if(is_looping) {	
          imglist_rew(imgl);
          if( imgl->current != NULL ) {
            clk_start = clock();
          }
	} else {
	  is_playing = FALSE;
	}
        break;     
      }
      imglist_step_foward( imgl );     
    }    
    redraw();
    Fl::wait(0);
  }
  is_playing = FALSE;
}


/**
 *Plays specified range from a video.
 *@param begin the begin of the range.
 *@param end the end of the range.
 */
void ImageViewer::playInRange(int begin, int end) 
{
  clock_t clk_start;
  
  is_playing = TRUE;
  imglist_go_to_frame(imgl, begin);
  
  if (imgl->current != NULL) {
      if ( imgl->current->prev != NULL )
	clk_start = clock() - (clock_t)(.01*CLOCKS_PER_SEC*imgl->current->prev->time_stamp);
      else
	clk_start = clock();
  }
  while( is_playing == TRUE && imgl->current != NULL){
    while( clock() - clk_start >= .01*CLOCKS_PER_SEC*imgl->current->time_stamp ) { 
      if( imgl->current->next == NULL || imgl->current->frame_number == end) {
        if(is_looping) {	
          imglist_go_to_frame(imgl, begin);
          if( imgl->current != NULL ) {
            if ( imgl->current->prev != NULL )
	      clk_start = clock() - (clock_t)(.01*CLOCKS_PER_SEC*imgl->current->prev->time_stamp);
	    else
	      clk_start = clock();
          }
	} else {
	  is_playing = FALSE;
	}
        break;     
      }
      imglist_step_foward( imgl );     
    }    
    redraw();
    Fl::wait(0);
  }
  is_playing = FALSE;
}

/**
 *Stops the video.
 */
void ImageViewer::stop() 
{
  is_playing = FALSE;
}

/**
 *Inserts a new frame.
 *@param delay the frame delay.
 *@param frame_duration the frame duration.
 */
void ImageViewer::insert_frame( int delay, int frame_duration ) 
{
  // this function is called by the Capture Button in UI
  Frame *f = new Frame(imgl->img_w, imgl->img_h);
  if (video_getframe(f)) {
    if (filter_on)
      camfilter_exec(f);
    imglist_addimg( imgl, imgnode_alloc(f, delay, frame_duration) );
  }  else {
    delete f;
  }
}

void ImageViewer::copy_frame(int begin, int end)
{
    imglist_clear(clipboard);

    if( imgl != NULL && imgl->current != NULL ) {
        if(begin != -1 && end != -1) {
            ImgNode *current = imgl->current;

            for(int i=begin; i <= end; ++i) {
                imglist_go_to_frame(imgl, i);
                ImgNode *cp = imgnode_copy(imgl->current);
                imglist_addimg(clipboard, cp);
            }
            imgl->current = current;

        } else {
            ImgNode *cp = imgnode_copy(imgl->current);
            imglist_addimg(clipboard, cp);
        }
    }
}

void ImageViewer::paste_frame(bool invert)
{
    if(clipboard != NULL && clipboard->head != NULL) {
        imglist_addlist(imgl, clipboard, invert);
    }
}

/**
 *Goes to specified frame.
 *@param frameNumber the frame number in animation.
 */
void ImageViewer::goToFrame( int frameNumber )
{ 
  if(imgl != NULL && imgl->current != NULL) {  
    imglist_go_to_frame(imgl, frameNumber);  
    redraw();
    return;
  }
  redraw();
}

/**
 *Sets the visualization mode (CAMERA or MEMORY)
 *Starts or stops the connection with the camera depending on the mode.
 *In fail case of changing to camera mode (start camera connection), can display a message.
 *Sets the label of the switch mode button.
 *@param _camera_on true to CAMERA mode or false to MEMORY mode.
 *@param _mem_alert defines if display an alert or not.
 *@param setLabel the function that sets the label of UI.
 */
void ImageViewer::setModeViewer(int _camera_on, int _mem_alert, setLabelModeViewerFunc setLabel)
{
  video_on = _camera_on;
  //in memory mode, deactivate FLICK
  if (!video_on)
    flick_on = FALSE;
  if (setLabel != NULL)
    setLabel(video_on, _mem_alert);
  invalidate();
  redraw();
}
