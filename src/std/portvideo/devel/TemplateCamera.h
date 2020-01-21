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

#ifndef TEMPLATECamera_H
#define TEMPLATECamera_H

#include <unistd.h>
#include "CameraEngine.h"
#include "template.h"
	
class TemplateCamera : public CameraEngine
{
public:
	TemplateCamera(const char* cfg);
	~TemplateCamera();
	
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
		
	// void drawGUI(SDL_Surface *display);

private:
	template_t *d;
};

#endif
