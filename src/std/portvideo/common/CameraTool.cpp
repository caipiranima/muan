/*  portVideo, a cross platform camera framework
	Copyright (C) 2005-2009 Martin Kaltenbrunner <modin@yuri.at>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include "CameraTool.h"

void CameraTool::listDevices(const char* config_file) 
{
  CameraEngine* camera = NULL;
  camera = findCamera(config_file);
  if (camera != NULL) {
    camera->initCamera();
    fprintf(stderr, "CAMERA - name = %s, w = %d, h = %d\n"
	    , camera->getName(), camera->getWidth(), camera->getHeight());
    camera->closeCamera();
    delete camera;
  }
}
	
CameraEngine* CameraTool::setCamera(const char* config_file, int type) 
{
  CameraEngine* camera = NULL;

  switch (type) {

#ifdef LINUX
  case CAM_DV1394:
    camera = new DV1394Camera(config_file);
    if(!camera->findCamera() )  delete camera;
    else return camera;
    ui_message("DV1394 Camera Not Found, using default");
    break;
  case CAM_DC1394:
    camera = new DC1394Camera(config_file);
    if( !camera->findCamera() ) delete camera;
    else return camera;
    ui_message("DC1394 Camera Not Found, using default");
    break;
  case CAM_GST:
      camera = new GStreamerCamera(config_file);
      if( !camera->findCamera()) delete camera;
      else return camera;
      ui_message("GStreamer Camera Not Found, using default");
      break;
  default:
  case CAM_DEFAULT:
  case CAM_V4L:
    camera = new V4Linux2Camera(config_file);
    if( !camera->findCamera()) delete camera;
    else return camera;
    ui_message("V4Linux Camera Not Found, using default");
    break;
#endif

#ifdef WIN32
  default:
  case CAM_DEFAULT:
    camera = new DSlibCamera(config_file);
    if( !camera->findCamera() ) delete camera;
    else return camera;
    ui_message("DirectShow Camera Not Found, using default");
    break;
#endif

#if defined (__APPLE__) && !defined (__x86_64__) && !defined (__ppc64__)
  default:
  case CAM_DEFAULT:
    camera = new MacVdigCamera(config_file);
    if( !camera->findCamera()) delete camera;
    else return camera;
    ui_message("MacVid Camera Not Found, using default");
    break;
#endif	
  case CAM_FILE:
    break;
  }
  camera = new FileCamera(config_file);
  if( !camera->findCamera() ) delete camera;
  else return camera;

  return NULL;
}

CameraEngine* CameraTool::findCamera(const char* config_file) 
{
	CameraEngine* camera = NULL;
	
	#ifdef WIN32
	camera = new DSlibCamera(config_file);
	if( !camera->findCamera() ) delete camera;
	else return camera;
	#endif

	#ifdef __APPLE__
	#if !defined (__x86_64__) && !defined (__ppc64__)
	camera = new MacVdigCamera(config_file);
	if( !camera->findCamera()) delete camera;
	else return camera;
	#endif
	#endif		
		
	#ifdef LINUX
	camera = new DC1394Camera(config_file);
	if( !camera->findCamera() ) delete camera;
	else return camera;
	
	camera = new V4Linux2Camera(config_file);
	if( !camera->findCamera()) delete camera;
	else return camera;

	camera = new DV1394Camera(config_file);
	if(!camera->findCamera() )  delete camera;
	else return camera;
	#endif

	camera = new FileCamera(config_file);
	if( !camera->findCamera() ) delete camera;
	else return camera;

	return NULL;
}

