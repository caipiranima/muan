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

#include "TemplateCamera.h"

TemplateCamera::TemplateCamera(const char* cfg) : CameraEngine(cfg)
{	
	running=false;
	lost_frames=0;
}

TemplateCamera::~TemplateCamera()
{
}

bool TemplateCamera::findCamera() 
{
	return true;
}

bool TemplateCamera::initCamera() 
{
	return true;
}

unsigned char* TemplateCamera::getFrame()
{
	templatevideo_frame_t *frame = NULL;
	return NULL; 
}

bool TemplateCamera::startCamera()
{
	running = true;
	return true;
}

bool TemplateCamera::stopCamera()
{
	if(!running) return false;

	running=false;
	return true;
}

bool TemplateCamera::stillRunning() 
{
	return running;
}

bool TemplateCamera::resetCamera()
{
  return (stopCamera() && startCamera());
}

bool TemplateCamera::closeCamera()
{
  return true;
}

bool TemplateCamera::setCameraSettingAuto(int mode, bool flag) {

	templatefeature_t feature = (templatefeature_t)-1;
	switch (mode) {
		case BRIGHTNESS: feature = Template_FEATURE_BRIGHTNESS; break;
		case GAIN: feature = Template_FEATURE_GAIN; break;
		case SHUTTER: feature = Template_FEATURE_SHUTTER; break;
		case EXPOSURE: feature = Template_FEATURE_EXPOSURE; break;
		case SHARPNESS: feature = Template_FEATURE_SHARPNESS; break;
		case FOCUS: feature = Template_FEATURE_FOCUS; break;
		case GAMMA: feature = Template_FEATURE_GAMMA; break;
	} if (feature<0) return 0;
		
	if (flag==true) template_feature_set_power(camera, feature, Template_ON);
	else template_feature_set_power(camera, feature, Template_OFF);

	if ( template_feature_set_mode(camera, feature, Template_FEATURE_MODE_AUTO) != Template_SUCCESS) return false;
	return true;
}


bool TemplateCamera::setCameraSetting(int mode, int setting) 
{

	int current_setting = getCameraSetting(mode);
	if (setting==current_setting) return true;
	setCameraSettingAuto(mode,false);

	templatefeature_t feature = (templatefeature_t)-1;
	switch (mode) {
		case BRIGHTNESS: feature = Template_FEATURE_BRIGHTNESS; config.brightness = setting; break;
		case GAIN: feature = Template_FEATURE_GAIN; config.gain = setting; break;
		case SHUTTER: feature = Template_FEATURE_SHUTTER; config.shutter = setting; break;
		case EXPOSURE: feature = Template_FEATURE_EXPOSURE; config.exposure = setting; break;
		case SHARPNESS: feature = Template_FEATURE_SHARPNESS; config.sharpness = setting; break;
		case FOCUS: feature = Template_FEATURE_FOCUS; config.focus = setting; break;
		case GAMMA: feature = Template_FEATURE_GAMMA; config.gamma = setting; break;
	} if (feature<0) return 0;
		
	uint32_t value = (uint32_t)setting;
	template_feature_set_power(camera, feature, Template_ON);
	template_feature_set_mode(camera, feature, Template_FEATURE_MODE_MANUAL);
	if (template_feature_set_value(camera, feature, value)!= Template_SUCCESS) return false;
	
	return true;
}

int TemplateCamera::getCameraSetting(int mode) {
	templatefeature_t feature = (templatefeature_t)-1;
	switch (mode) {
		case BRIGHTNESS: feature = Template_FEATURE_BRIGHTNESS; break;
		case GAIN: feature = Template_FEATURE_GAIN; break;
		case SHUTTER: feature = Template_FEATURE_SHUTTER; break;
		case EXPOSURE: feature = Template_FEATURE_EXPOSURE; break;
		case SHARPNESS: feature = Template_FEATURE_SHARPNESS; break;
		case FOCUS: feature = Template_FEATURE_FOCUS; break;
		case GAMMA: feature = Template_FEATURE_GAMMA; break;
	} if (feature<0) return 0;

	uint32_t value = 0;
	if (template_feature_get_value(camera,  feature, &value)!= Template_SUCCESS) return 0;
	return (int)value;
}

int TemplateCamera::getMaxCameraSetting(int mode) {
	templatefeature_t feature = (templatefeature_t)-1;
	switch (mode) {
		case BRIGHTNESS: feature = Template_FEATURE_BRIGHTNESS; break;
		case GAIN: feature = Template_FEATURE_GAIN; break;
		case SHUTTER: feature = Template_FEATURE_SHUTTER; break;
		case EXPOSURE: feature = Template_FEATURE_EXPOSURE; break;
		case SHARPNESS: feature = Template_FEATURE_SHARPNESS; break;
		case FOCUS: feature = Template_FEATURE_FOCUS; break;
		case GAMMA: feature = Template_FEATURE_GAMMA; break;
	} if (feature<0) return 0;

	uint32_t min;
	uint32_t max;
	if (template_feature_get_boundaries(camera, feature, &min, &max)!= Template_SUCCESS) return 0;
	return (int)max;
}

int TemplateCamera::getMinCameraSetting(int mode) {
	templatefeature_t feature = (templatefeature_t)-1;
	switch (mode) {
		case BRIGHTNESS: feature = Template_FEATURE_BRIGHTNESS; break;
		case GAIN: feature = Template_FEATURE_GAIN; break;
		case SHUTTER: feature = Template_FEATURE_SHUTTER; break;
		case EXPOSURE: feature = Template_FEATURE_EXPOSURE; break;
		case SHARPNESS: feature = Template_FEATURE_SHARPNESS; break;
		case FOCUS: feature = Template_FEATURE_FOCUS; break;
		case GAMMA: feature = Template_FEATURE_GAMMA; break;
	} if (feature<0) return 0;

	uint32_t min;
	uint32_t max;
	if (template_feature_get_boundaries(camera, feature, &min, &max)!= Template_SUCCESS) return 0;
	return (int)min;
}

int TemplateCamera::getCameraSettingStep(int mode) {
	templatefeature_t feature = (templatefeature_t)-1;
	switch (mode) {
		case BRIGHTNESS: feature = Template_FEATURE_BRIGHTNESS; break;
		case GAIN: feature = Template_FEATURE_GAIN; break;
		case SHUTTER: feature = Template_FEATURE_SHUTTER; break;
		case EXPOSURE: feature = Template_FEATURE_EXPOSURE; break;
		case SHARPNESS: feature = Template_FEATURE_SHARPNESS; break;
		case FOCUS: feature = Template_FEATURE_FOCUS; break;
		case GAMMA: feature = Template_FEATURE_GAMMA; break;
	} if (feature<0) return 0;

	return 1;
}
