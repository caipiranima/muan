/**
 * This file represents the video interface with dv.
  \file DV1394Camera.h
 */

/*
 * Copyright (C) 2010  Lab. Visgraf/IMPA and AnimaMundi
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

#ifndef _VIDEO_DV_H
#define _VIDEO_DV_H


#define  BUFFERED_FRAMES        25
#define  dvW     720
#define  dvH     480

#include <iostream>

#include <math.h>
#include <limits.h>
#include "../include/CameraEngine.h"
#include "dv1394/ieee1394io.h"
#include "dv1394/error.h"
#include "dv1394/dvframe.h"
#include "dv1394/dv1394.h"
#include "config.h"

extern "C"
{
#include "image.h"
}


class DV1394Camera : public CameraEngine {
public:
	DV1394Camera(const char* cfg);
	~DV1394Camera(void);

	bool findCamera();
	bool initCamera();
	bool startCamera();
	unsigned char* getFrame();
	bool stopCamera();
	bool stillRunning();
	bool resetCamera();
	bool closeCamera();
	
    int getCameraSettingStep(int mode);
    bool setCameraSettingAuto(int mode, bool flag);
    bool setCameraSetting(int mode, int value);
    int getCameraSetting(int mode);
    int getMaxCameraSetting(int mode);
    int getMinCameraSetting(int mode);

protected:
	/*DV*/
        bool dv_video_open(void);

        IEEE1394Reader *reader;
        unsigned char *pixels;
        bool hdv;
};


#endif
