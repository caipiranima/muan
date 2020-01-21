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
#include "CameraEngine.h"

void CameraEngine::showSettingsDialog() {
}
	
void CameraEngine::control(int key) {
  if(!settingsDialog) 
    return;		
}

void CameraEngine::readSettings() {
  config.device = 0;
  config.color = true;
  config.width = SETTING_MAX;
  config.height = SETTING_MAX;

  config.fps = SETTING_MAX;
  config.fps = SETTING_MAX;
  config.format7 = false;
  config.xoff = 0;
  config.yoff = 0;
  sprintf(config.file,"none");		
  sprintf(config.folder,"none");		

  width = config.width;
  height = config.height;
  colour = config.color;
  bytes = (colour?3:1);

  TiXml::TiXmlDocument xml_settings( config_file );
  xml_settings.LoadFile();
  if( xml_settings.Error() ) {
      std::cout << "Error loading camera configuration file: " << config_file << std::endl;
      return;
  }
  TiXml::TiXmlHandle docHandle( &xml_settings );
  TiXml::TiXmlHandle camera = docHandle.FirstChild("muan").FirstChild("camera");
  TiXml::TiXmlElement* camera_element = camera.Element();

  if( camera_element==NULL ) {
      std::cout << "Error loading camera configuration file: " << config_file << std::endl;
      return;
  }
  if(camera_element->Attribute("id")!=NULL) {
    if (strcmp(camera_element->Attribute("id"), "auto" ) == 0) config.device=SETTING_AUTO;
    else config.device = atoi(camera_element->Attribute("id"));
  }
  if(camera_element->Attribute("file")!=NULL) {
#if !defined WIN32
    //sprintf(config.file,"/usr/local/share/muan/%s",camera_element->Attribute("file"));
    sprintf(config.file,"/usr/share/muan/%s",camera_element->Attribute("file"));
#else
    sprintf(config.file,"%s",camera_element->Attribute("file"));
#endif
  }
  TiXml::TiXmlElement* image_element = camera.FirstChild("image").Element();
  if (image_element!=NULL) {
    if ((image_element->Attribute("color")!=NULL) && ( strcmp( image_element->Attribute("color"), "true" ) == 0 )) config.color = true;
    if(image_element->Attribute("width")!=NULL) {
      if (strcmp( image_element->Attribute("width"), "max" ) == 0) config.width = SETTING_MAX;
      else config.width = atoi(image_element->Attribute("width"));
    }
    if(image_element->Attribute("height")!=NULL) {
      if (strcmp( image_element->Attribute("height"), "max" ) == 0) config.height = SETTING_MAX;
      else config.height = atoi(image_element->Attribute("height"));
    }
    if(image_element->Attribute("fps")!=NULL) {
      if (strcmp( image_element->Attribute("fps"), "max" ) == 0) config.fps = SETTING_MAX;
      else config.fps = atof(image_element->Attribute("fps"));
    }
  }
  TiXml::TiXmlElement* format7_element = camera.FirstChild("format7").Element();
  if (format7_element!=NULL) {
    config.format7 = true;
    if(format7_element->Attribute("xoff")!=NULL) {
      if (strcmp( format7_element->Attribute("xoff"), "max" ) == 0) config.xoff = SETTING_MAX;
      else if (strcmp( format7_element->Attribute("xoff"), "min" ) == 0) config.xoff = 0;
      else config.xoff = atoi(format7_element->Attribute("xoff"));
    }
    if(format7_element->Attribute("yoff")!=NULL) {
      if (strcmp( format7_element->Attribute("yoff"), "max" ) == 0) config.yoff = SETTING_MAX;
      else if (strcmp( format7_element->Attribute("yoff"), "min" ) == 0) config.yoff = 0;
      else config.yoff = atoi(format7_element->Attribute("yoff"));
    }
  }
  width = config.width;
  height = config.height;
  colour = config.color;
  bytes = (colour?3:1);
}

void CameraEngine::saveSettings() {
  if (strcmp( config_file, "none" ) == 0) {
    config_file = "./muan_conf.xml";
  }
  TiXml::TiXmlDocument xml_settings( config_file );
  xml_settings.LoadFile();
  if( xml_settings.Error() ) {
      std::cout << "Error loading camera configuration file: " << config_file << std::endl;
      return;
  }	
  TiXml::TiXmlHandle docHandle( &xml_settings );
  TiXml::TiXmlHandle camera = docHandle.FirstChild("muan").FirstChild("camera");

  TiXml::TiXmlElement* image_element = camera.FirstChild("image").Element();
  if (image_element!=NULL) {

#ifdef WIN32
    setvbuf (stdout, NULL, _IONBF, 0);
#endif

    //if ((image_element->Attribute("color")!=NULL) && ( strcmp( image_element->Attribute("color"), "true" ) == 0 )) config.color = true;	
	{
	  char width_value[10];
	  sprintf(width_value, "%d", width);
      image_element->SetAttribute("width", width_value);
    }
    
	{
	  char height_value[10];
      sprintf(height_value, "%d", height);
      image_element->SetAttribute("height", height_value);
    }
    
	{
	  char fps_value[10];
      sprintf(fps_value, "%d", fps);
      image_element->SetAttribute("fps", fps_value);      	 
    }
  }

  TiXml::TiXmlElement* settings_element = camera.FirstChild("settings").Element();	
  char config_value[64];	
  if (settings_element!=NULL) {
    if(settings_element->Attribute("brightness")!=NULL) {
      if (config.brightness==SETTING_MAX) settings_element->SetAttribute("brightness","max");
      else if (config.brightness==SETTING_MIN) settings_element->SetAttribute("brightness","min");
      else if (config.brightness==SETTING_AUTO) settings_element->SetAttribute("brightness","auto");
      else if (config.brightness==SETTING_DEFAULT) settings_element->SetAttribute("brightness","default");
      else {
	sprintf(config_value,"%d",config.brightness);
	settings_element->SetAttribute("brightness",config_value);
      }
    }
  }	
  xml_settings.SaveFile();
  if( xml_settings.Error() ) 
    std::cout << "Error saving camera configuration file: "  << config_file << std::endl;
}

void CameraEngine::uyvy2gray(int width, int height, unsigned char *src, unsigned char *dest) {

  for (int i=height*width/2;i>0;i--) {
    src++;
    *dest++ = *src++;
    src++;
    *dest++ = *src++;
  }
}

void CameraEngine::yuyv2gray(int width, int height, unsigned char *src, unsigned char *dest) {
  for (int i=height*width/2;i>0;i--) {
    *dest++ = *src++;
    src++;
    *dest++ = *src++;
    src++;
  }
}

void CameraEngine::uyvy2rgb(int width, int height, unsigned char *src, unsigned char *dest) {

  int R,G,B;
  int Y1,Y2;
  int U,V;
  for(int y=0;y<height;y++) {
    for(int x=0;x<width/2;x++) {
      U    = *src++ -128;
      Y1 = *src++;
      V    = *src++ -128;
      Y2 = *src++;

      R = (int)(Y1 + 1.370705f * V);
      G = (int)(Y1 - 0.698001f * V - 0.337633f * U);
      B = (int)(Y1 + 1.732446f * U);
						
      SAT(R);
      SAT(G);
      SAT(B);
	
      *dest++ = R;
      *dest++ = G;
      *dest++ = B;

      R = (int)(Y2 + 1.370705f * V);
      G = (int)(Y2 - 0.698001f * V - 0.337633f * U);
      B = (int)(Y2 + 1.732446f * U);
						
      SAT(R);
      SAT(G);
      SAT(B);
	
      *dest++ = R;
      *dest++ = G;
      *dest++ = B;

    }
  }		
}

void CameraEngine::yuyv2rgb(int width, int height, unsigned char *src, unsigned char *dest) {
	
  int R,G,B;
  int Y1,Y2;
  int U,V;

  for(int y=0;y<height;y++) {
    for(int x=0;x<width/2;x++) {
      Y1 = *src++;
      U    = *src++ -128;
      Y2 = *src++;
      V    = *src++ -128;

      R = (int)(Y1 + 1.370705f * V);
      G = (int)(Y1 - 0.698001f * V - 0.337633f * U);
      B = (int)(Y1 + 1.732446f * U);
						
      SAT(R);
      SAT(G);
      SAT(B);
	
      *dest++ = R;
      *dest++ = G;
      *dest++ = B;

      R = (int)(Y2 + 1.370705f * V);
      G = (int)(Y2 - 0.698001f * V - 0.337633f * U);
      B = (int)(Y2 + 1.732446f * U);
						
      SAT(R);
      SAT(G);
      SAT(B);
	
      *dest++ = R;
      *dest++ = G;
      *dest++ = B;

    }
  }		
}


void CameraEngine::bgr_to_rgb(unsigned char *img, unsigned int width, unsigned int height)
{
  register unsigned char *p = img + (width * height * 3), a;

  for (; img < p; img += 3) {
    a = *img;
    *img = img[2];
    img[2] = a;
  } 
}


void CameraEngine::applyCameraSetting(int mode, int value) {
#if 0
  switch (value) {
  case SETTING_DEFAULT: break;
  case SETTING_AUTO: setCameraSettingAuto(mode,true); break;
  case SETTING_MIN: setCameraSetting(mode,getMinCameraSetting(mode)); break;
  case SETTING_MAX: setCameraSetting(mode,getMaxCameraSetting(mode)); break;
  default: {
    int max = getMaxCameraSetting(mode);
    int min = getMinCameraSetting(mode);
    if (value<min) value = min;
    else if (value>max) value = max;
    setCameraSetting(mode,value);
  }
  }
#endif
}

void CameraEngine::applyCameraSettings() {
#if 0
  applyCameraSetting(BRIGHTNESS,config.brightness);
  applyCameraSetting(GAIN,config.gain);
  applyCameraSetting(SHUTTER,config.shutter);
  applyCameraSetting(EXPOSURE,config.exposure);
  applyCameraSetting(SHARPNESS,config.sharpness);
  applyCameraSetting(FOCUS,config.focus);
  applyCameraSetting(GAMMA,config.gamma);
#endif
}

