#ifndef MUAN_SETTINGS_H
#define MUAN_SETTINGS_H

#include <fstream>
#include <iostream>
#include "tinyxml.h"

const char *config_file = "none";

static bool isize_override = false;
static int iframe_w = IMG_DV_W;
static int iframe_h = IMG_DV_H;

#ifndef MUAN_PL

/** Refreshes and shows informations on UI Current Frame Panel
 * @param _fnumber The number of a frame within the animation
 * @param _fduration The duration of a frame within the animation
 * @param _fpos The position of a frame within the animation (considering the duration)
 */
void refreshFrameCur(int _fnumber, int _fduration, int fpos) {
  char s[10];
  sprintf(s, "%5.5i", _fnumber);
  p->out_frame_number->value(s);
  sprintf(s, "%3i", _fduration);
  p->out_current_frame_duration->value(s);
  sprintf(s, "%d", fpos);
  p->out_frame_pos->value(s);
}   
   
/** Refreshes and shows informations on UI Total Frames Panel
 * @param _totImgCap The total number of frames within the animation
 * @param _totRealFrames The total number of frames within the animation considering the duration
 */
void refreshFrameTot(int _totImgCap, int _totRealFrames) {
  char s[10];
  sprintf(s, "%5.5i", _totImgCap);
  p->out_tot_img_cap->value(s);
  sprintf(s, "%5.5i", _totRealFrames);
  p->out_tot_frames->value(s);
}

/** Refreshes and shows message on UI
 * @param m The message
 */
void setMessage(const char* m) {
  p->out_message->value(m);
  p->redraw_message = true;	
}

/** Refreshes UI elements according to camera/memory mode.
 * @param camera_on The flag to indicate camera or memory mode.
 * @param mem_alert The flag to show (or not) message.
 */
void setLabelModeViewer(bool camera_on, bool mem_alert)
{
  p->camera_on = camera_on;	//atualizando situacao da interface.
				//precisa pois a interface pode estar true e se aqui nao conseguiu ligar vai ficar false.
#ifdef MUAN_AE
  if (camera_on)  {
    p->btn_mode->label(LBL_BTN_MODE_CAM);
	setMessage(""); //mcv: 22/01  
  }  else  {
    p->btn_mode->label(LBL_BTN_MODE_MEM);
    p->btn_flick->value(FALSE); //no modo memoria, FLICK foi desativado, entao atualiza interface
    if (mem_alert) {    
      fl_alert(MSG_CAMERA_OFF);
    }
  }
#else
  if (camera_on)  {
    p->mn_mode->label(LBL_BTN_MODE_CAM);
	setMessage(""); //mcv: 22/01  
  }  else  {
    p->mn_mode->label(LBL_BTN_MODE_MEM);
    p->btn_flick->value(FALSE); //no modo memoria, FLICK foi desativado, entao atualiza interface
    if (mem_alert) {    
      fl_alert(MSG_CAMERA_OFF);
    }
  }
#endif
}

/** Redraws UI refreshing informations.
 */
void redraw_panel( void* ){
   p->imgv->redraw();  // vai executar o draw definido na classe imgviewer
   //garantindo que a interface esta consitente com a situacao de video_on
   if ((p->camera_on != p->imgv->get_video_on()) && (!p->imgv->flick_on))
	   setLabelModeViewer(p->imgv->get_video_on(), TRUE);

   if(p->redraw_message) {
     p->redraw_file_name();
#ifdef MUAN_AE
     w->redraw();
#else
     p->win_info->redraw();
#endif
     p->redraw_message = false;
   }
   if( p->imgv->imgl != NULL && p->imgv->imgl->current != NULL ){
	refreshFrameCur(p->imgv->imgl->current->frame_number, p->imgv->imgl->current->frame_duration, p->imgv->imgl->current->frame_pos);
    refreshFrameTot(p->imgv->imgl->totFrames, p->imgv->imgl->totRealFrames);  
  } else {
    refreshFrameCur(0, 0, 0);
    refreshFrameTot(0, 0);  
  }  
}

/** Periodically saves animation in a backup file provided that AutoSave preference option is on.
 */
void autoSave(void *) {  
  //esta rotina nao deve atualizar a variavel file_changed da interface pois nao esta salvando sobre o arquivo em uso e sim no auto_save_file.    
  if (p->auto_save) {
    p->save_file(p->auto_save_file, FALSE);
    Fl::repeat_timeout(p->auto_save_time, &autoSave);
  }
}

/** Reads XML file
 */
void read_xml(const char* conf_file)
{
  TiXml::TiXmlDocument xml_settings( conf_file );
  xml_settings.LoadFile();
  if( xml_settings.Error() ) {
      std::cout << "Error loading camera configuration file: " << conf_file << std::endl;
      return;
  }
  TiXml::TiXmlHandle docHandle( &xml_settings );
  TiXml::TiXmlHandle prefs = docHandle.FirstChild("muan").FirstChild("prefs");
  TiXml::TiXmlElement* prefs_element = prefs.Element();
  if( prefs_element==NULL ) {
      std::cout << "Error loading prefs configuration file: " << conf_file << std::endl;
  }
  if(prefs_element->Attribute("load_mode")!=NULL) {
    p->load_mode = atoi(prefs_element->Attribute("load_mode"));
  }
  if(prefs_element->Attribute("play_sound")!=NULL) {
    p->play_sound = (strcmp(prefs_element->Attribute("play_sound"), "true" ) == 0)? true : false;
  }
  if(prefs_element->Attribute("show_splash")!=NULL) {
    p->show_splash = (strcmp(prefs_element->Attribute("show_splash"), "true" ) == 0)? true : false;
  }
  if(prefs_element->Attribute("save_path")!=NULL) {
    efree(p->save_path);
    p->save_path = (char*) emalloc (strlen(prefs_element->Attribute("save_path"))+1);
    sprintf(p->save_path,"%s",prefs_element->Attribute("save_path"));
  }
  if(prefs_element->Attribute("duration_default")!=NULL) {
    p->duration_default = atoi(prefs_element->Attribute("duration_default"));
  }
  TiXml::TiXmlHandle camera = docHandle.FirstChild("muan").FirstChild("camera");
  TiXml::TiXmlElement* camera_element = camera.Element();
  if( camera_element==NULL ) {
    std::cout << "Error loading camera configuration file: " << config_file << std::endl;
    return;
  }
  if(camera_element->Attribute("type")!=NULL) {
    if (strcmp(camera_element->Attribute("type"), "default") == 0) {
      p->camera_connection = CAM_DEFAULT;
    } else if (strcmp(camera_element->Attribute("type"), "v4l") == 0) {
      p->camera_connection = CAM_V4L;
    } else if (strcmp(camera_element->Attribute("type"), "dv1394") == 0) {
      p->camera_connection = CAM_DV1394;
    } else if (strcmp(camera_element->Attribute("type"), "dc1394") == 0) {
      p->camera_connection = CAM_DC1394;
    } else if (strcmp(camera_element->Attribute("type"), "gstreamer" ) == 0) {
      p->camera_connection = CAM_GST;
    } else {
      p->camera_connection = CAM_DEFAULT;
      ui_message("Unknown Type: changing Camera Connection to Default");
    }
    if(camera_element->Attribute("id")!=NULL) {
        efree(p->v4l_device);
        p->v4l_device = (char*) emalloc (strlen(camera_element->Attribute("id"))+1);
        sprintf(p->v4l_device,"%s",camera_element->Attribute("id"));
		if(strcmp(p->v4l_device,"auto") == 0) p->show_camera_config=true;
    }
#ifdef WIN32
    if (p->camera_connection != CAM_DEFAULT) {
      p->camera_connection = CAM_DEFAULT;
      ui_message("Win32: changing Camera Connection to Default");
    }
#endif
#ifdef __APPLE__
    if (p->camera_connection != CAM_DEFAULT && p->camera_connection != CAM_DC1394) {
      p->camera_connection = CAM_DEFAULT;
      ui_message("MacOS: changing Camera Connection to Default");
    }
#endif
  }
  TiXml::TiXmlHandle auto_save = docHandle.FirstChild("muan").FirstChild("auto_save");
  TiXml::TiXmlElement* autosave_element = auto_save.Element();
  if( autosave_element==NULL ) {
      std::cout << "Error loading prefs configuration file: " << conf_file << std::endl;
      return;
  }
  if(autosave_element->Attribute("mode")!=NULL) {
    p->auto_save = atoi(autosave_element->Attribute("mode"));
  }
  if(autosave_element->Attribute("time")!=NULL) {
    p->auto_save_time = atoi(autosave_element->Attribute("time"));
  }
  if(autosave_element->Attribute("file")!=NULL) {
    efree(p->auto_save_file);
    p->auto_save_file = (char*) emalloc (strlen(autosave_element->Attribute("file"))+1);
    sprintf(p->auto_save_file,"%s",autosave_element->Attribute("file"));
  }
  TiXml::TiXmlHandle iframe = docHandle.FirstChild("muan").FirstChild("iframe");
  TiXml::TiXmlElement* iframe_element = iframe.Element();
  if( iframe_element==NULL ) {
      std::cout << "Error loading prefs configuration file: " << conf_file << std::endl;
      return;
  }
  if(iframe_element->Attribute("width")!=NULL) {
    iframe_w = atoi(iframe_element->Attribute("width"));
  }
  if(iframe_element->Attribute("height")!=NULL) {
    iframe_h = atoi(iframe_element->Attribute("height"));
  }
  if(iframe_element->Attribute("override")!=NULL) {
    isize_override = (strcmp(iframe_element->Attribute("override"), "true" ) == 0)? true : false;
  }
  p->imgl_w = iframe_w;
  p->imgl_h = iframe_h;
  p->imgl_override = isize_override;
}

/** Reads preferences file and sets connection, animation and user interface parameters.
 */
void readPreferences ( void )
{
  //inicializando parametros
  p->load_mode = DEF_LOAD_MODE;
  p->duration_default = DEF_DURATION_DEFAULT;
  p->auto_save = DEF_AUTO_SAVE;
  p->auto_save_time = DEF_AUTO_SAVE_TIME;

  p->save_path = (char*) emalloc (strlen(DEF_SAVE_PATH)+1);
  strcpy(p->save_path, DEF_SAVE_PATH);

#ifdef WIN32
  char *pPath;

  pPath = getenv("TEMP");
  if(pPath != NULL) {
      strcat(pPath, "\\");
      strcat(pPath, DEF_AUTO_SAVE_FILE);

  } else {
      pPath = (char *)"C:\\Windows\\TEMP\\";
      strcat(pPath, DEF_AUTO_SAVE_FILE);
  }

  p->auto_save_file = (char*) emalloc (strlen(pPath)+1);
  strcpy(p->auto_save_file, pPath);

#else
  p->auto_save_file = (char*) emalloc (strlen(DEF_AUTO_SAVE_FILE)+1);
  strcpy(p->auto_save_file, DEF_AUTO_SAVE_FILE);
#endif

  p->play_sound = DEF_PLAY_SOUND;
  p->camera_connection = DEF_CAMERA_CONNECTION;
  p->show_splash = DEF_SHOW_SPLASH;

  read_xml(config_filename());

  setMessage("");
}

/** Write XML file
 */
void write_xml(const char* conf_file)
{
  TiXml::TiXmlDocument xml_settings( conf_file );
  xml_settings.LoadFile();
  if( xml_settings.Error() ) {
      std::cout << "Error loading configuration file: " << conf_file << std::endl;
      return;
  }	
  char config_value[64];	
  TiXml::TiXmlHandle docHandle( &xml_settings );
  TiXml::TiXmlHandle prefs = docHandle.FirstChild("muan").FirstChild("prefs");
  TiXml::TiXmlElement* prefs_element = prefs.Element();	
  if (prefs_element!=NULL) {
    if(prefs_element->Attribute("load_mode")!=NULL) {
      prefs_element->SetAttribute("load_mode", p->load_mode);
    }
    if(prefs_element->Attribute("play_sound")!=NULL) {
      if (p->play_sound)
	prefs_element->SetAttribute("play_sound", "true");
      else
	prefs_element->SetAttribute("play_sound", "false");
    }
    if(prefs_element->Attribute("show_splash")!=NULL) {
      if (p->show_splash)
        prefs_element->SetAttribute("show_splash", "true");
      else
        prefs_element->SetAttribute("show_splash", "false");
    }
    if(prefs_element->Attribute("save_path")!=NULL) {
      prefs_element->SetAttribute("save_path", p->save_path);
    }
    if(prefs_element->Attribute("duration_default")!=NULL) {
      sprintf(config_value,"%d", p->duration_default);
      prefs_element->SetAttribute("duration_default", config_value);
    }
    TiXml::TiXmlHandle docHandle( &xml_settings );
    TiXml::TiXmlHandle camera = docHandle.FirstChild("muan").FirstChild("camera");
    TiXml::TiXmlElement* camera_element = camera.Element();
    if( camera_element==NULL ) {
      std::cout << "Error loading camera configuration file: " << config_file << std::endl;
      return;
    }
    if(camera_element->Attribute("type")!=NULL) {
      switch ( p->camera_connection ) {
      case CAM_DEFAULT:
        camera_element->SetAttribute("type", "default");
		if(p->show_camera_config)
			p->v4l_device = "auto";
		else
			p->v4l_device = "0";
        break;
      case CAM_V4L:
        camera_element->SetAttribute("type", "v4l"); break;
      case CAM_DV1394:
	camera_element->SetAttribute("type", "dv1394"); break;
      case CAM_DC1394:
	camera_element->SetAttribute("type", "dc1394"); break;
      }
    }
    if(camera_element->Attribute("id")!=NULL) {
        camera_element->SetAttribute("id" , p->v4l_device);
    }
  }

  TiXml::TiXmlHandle iframe = docHandle.FirstChild("muan").FirstChild("iframe");
  TiXml::TiXmlElement* iframe_element = iframe.Element();
  if( iframe_element==NULL ) {
      std::cout << "[IFRAME] Error loading prefs configuration file: " << conf_file << std::endl;
      return;
  }
  if(iframe_element->Attribute("width")!=NULL) {
    iframe_element->SetAttribute("width", p->imgl_w);
  }
  if(iframe_element->Attribute("height")!=NULL) {
    iframe_element->SetAttribute("height", p->imgl_h);
  }
  if(iframe_element->Attribute("override")!=NULL) {
    if (p->imgl_override)
      iframe_element->SetAttribute("override", "true");
    else
      iframe_element->SetAttribute("override", "false");
  }
  iframe_w = p->imgl_w;
  iframe_h = p->imgl_h;

  TiXml::TiXmlHandle auto_save = docHandle.FirstChild("muan").FirstChild("auto_save");
  TiXml::TiXmlElement* autosave_element = auto_save.Element();
  if( autosave_element==NULL ) {
      std::cout << "[AUTO_SAVE] Error loading prefs configuration file: " << conf_file << std::endl;
      return;
  }
  if(autosave_element->Attribute("mode")!=NULL) {
    sprintf(config_value,"%d", p->auto_save);
    autosave_element->SetAttribute("mode", config_value);
  }
  if(autosave_element->Attribute("time")!=NULL) {
    sprintf(config_value,"%d", p->auto_save_time);
    autosave_element->SetAttribute("time", config_value);
  }
  if(autosave_element->Attribute("file")!=NULL) {
    autosave_element->SetAttribute("file", p->auto_save_file);
  }
  xml_settings.SaveFile();
  if( xml_settings.Error() ) 
    std::cout << "Error saving configuration file: "  << conf_file << std::endl;
}

void writePreferences ( void )
{
  write_xml(config_filename());
}

void ui_message(const char *s)
{
  fl_alert("%s",s);
}

int ui_choice(const char *s, const char *cancel, const char *yes, const char *no)
{
  return fl_choice(s, cancel, yes, no);
}

void ui_beep(void)
{
  PlayBeepSound();
}

void ui_setfilter(int stat)
{
  p->imgv->filter_on = stat;
  p->btn_filter->value(stat);
}

#else
// MUAN Player

void readPreferences ( void )
{
  //inicializando parametros
  p->load_mode = DEF_LOAD_MODE;
}

void setMessage(const char* m)
{}

int ui_choice(const char *s, const char *cancel, const char *yes, const char *no)
{
    return 0;
}

void ui_message(const char *s)
{}

void ui_beep(void)
{
}

void ui_setfilter(int stat)
{
}

#endif
#endif

