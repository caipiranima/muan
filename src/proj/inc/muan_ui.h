/* muau ui */
#ifndef _MUAN_UI_H_
#define _MUAN_UI_H_

#include <string.h>

#include "sndfile-play.h"
#include "plugin.h"
#include "filter.h"


#define BUG_REPORT "http://www.visgraf.impa.br/muan2/br/muan_feedback.html"

#ifdef WIN32
//Workaround: Windows doesn't define this function
char * rindex (char *s, int c)
{
  return strrchr (s, c);
}
#endif


#if not defined(__APPLE__) && not defined(WIN32)

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

int getdir (string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}

void ui_set_number_of_video_devices(MUAN_UI *ui)
{
    string dir = string("/dev/");
    vector<string> files = vector<string>();

    char camId[4];
    int id=0;

    getdir(dir,files);
//    ui->cmb_camera_v4l->add("0");
    for (unsigned int i = 0;i < files.size();i++) {
        if( files[i].find("video") != string::npos) {
            sprintf(camId, "%d", id++);
            ui->cmb_camera_v4l->add(camId);
        }
    }

    ui->cmb_camera_v4l->value(0);
    id = atoi(ui->v4l_device);
    if(id < files.size()) {
        ui->cmb_camera_v4l->value(id);
    }
}

#endif

// load file
int ui_load_file(MUAN_UI *ui, char* fname)
{
  if (fname!= NULL) {
    char *ext = strrchr(fname, '.');
    if ((strcmp(ext, ".avi")==0) || (strcmp(ext, ".AVI")==0) ) {
      VideoEncoder encoder;
      setMessage("Loading AVI...");
      encoder.avi_read(ui->imgv->imgl, fname, ui->load_mode);
      setMessage("");
    }else if ( (strcmp(ext, ".jpg")==0) || (strcmp(ext, ".JPG")==0) ){
      setMessage("Loading image...");
      insert_frame_from_imagefile(ui->imgv->imgl, fname);
      setMessage("");
    } else if ((strcmp(ext, ".mpg")==0) || (strcmp(ext, ".MPG")==0) || (strcmp(ext, ".mp4")==0))  {
      VideoEncoder encoder;
      printf("Loading MPG...");
      encoder.mpg_read(ui->imgv->imgl, fname);
      printf("  OK.\n");
    } else {
      char msg[255]= MSG_INVALID_FILE_FORMAT;
      strcat(msg, "\n");
      printf("%s",msg);
      return 0;
    }
    return 1;
  } else return 0;
}


//FLIP

void ui_flick(MUAN_UI *ui)
{
    if (ui->imgv->transp_on) {
       ui->btn_flick->value(!ui->btn_flick->value());
    }
    ui->imgv->stop();

    if ((ui->btn_flick->value()) && (!ui->camera_on)) {
      ui->camera_on = TRUE;
      ui->imgv->setModeViewer(TRUE, FALSE, setLabelModeViewer);
    }
    ui->imgv->flick_on = ui->btn_flick->value();

    if ((!ui->btn_flick->value()) && (ui->imgv->get_video_on() != ui->camera_on))  {
      ui->imgv->setModeViewer(ui->imgv->get_video_on(), FALSE, setLabelModeViewer);
    }

    ui->imgv->redraw();
}

//TRANSPARENCIA
void ui_transp(MUAN_UI *ui)
{
    if (ui->imgv->flick_on) {
       ui->btn_transp->value(!ui->btn_transp->value());
       return;
    }
    ui->imgv->stop();

    if ((ui->btn_transp->value()) && (!ui->camera_on))
    {
      ui->camera_on = TRUE;
      ui->imgv->setModeViewer(TRUE, FALSE, setLabelModeViewer);
    }

    ui->imgv->transp_on = ui->btn_transp->value();


    if ((!ui->btn_transp->value()) && (ui->imgv->get_video_on() != ui->camera_on))
    {
      ui->imgv->setModeViewer(ui->imgv->get_video_on(), FALSE, setLabelModeViewer);
    }


    ui->imgv->redraw();
}

// NEW
void ui_new_project(MUAN_UI *ui)
{
  if (ui->check_file(FALSE) > 0) {
    imglist_clear(ui->imgv->imgl);
    ui->camera_mode_changed = FALSE;
    ui->file_changed = FALSE;
    ui->file_name[0]='\0';
    ui->redraw_message = TRUE;

    ui->sl_timeline->value (imglist_getCurrentFnum(ui->imgv->imgl));
    ui->edt_duration->value(NULL);
    ui->edt_go_to_frame->value(NULL);
    ui->edt_begin->value(NULL);
    ui->edt_end->value(NULL);
    ui->btn_range->value(0);
    ui->btn_loop->value(0);
    

    // Reset flick mode
    {
        ui->btn_flick->value(0);
        ui->imgv->stop();
        ui->imgv->flick_on = ui->btn_flick->value();

        if ((!ui->btn_flick->value()) && (ui->imgv->get_video_on() != ui->camera_on))
        {
            ui->imgv->setModeViewer(ui->imgv->get_video_on(), FALSE, setLabelModeViewer);
        }
    }

    // Reset transparency mode
    {
        ui->btn_transp->value(0);
        ui->sl_transp->value(0.75);
        ui->imgv->transp_fac = 0.75;
        ui->imgv->transp_on = FALSE;
    }
    
    //Reset camera filter
    {
  	    			
 		ui->btn_filter->value(0);
                ui->btn_fselect->label(LBL_BTN_FSELECT);

    }
    
    //Reset process filter
    {
    	ui->btn_process->value(0);
        ui->btn_mselect->label(LBL_BTN_MSELECT);
    }
    
    ui->imgv->redraw();

  }
}

// LOAD
int ui_load(MUAN_UI *ui)
{
  char *fname = fl_file_chooser( LBL_LOAD_FILE_CHOOSER, "*.{avi,mpg,jpg}", "",  0 );

  if (fname != NULL) {
    ui->set_memory_mode();
    imglist_clear(ui->imgv->imgl);
    ui_load_file(ui,fname);
    imglist_rew(ui->imgv->imgl );
    ui->file_changed = FALSE;
    strcpy(ui->file_name, fname);
    ui->redraw_message = TRUE;
    return 1;
  }
}

// INSERT
int ui_insert(MUAN_UI *ui)
{
  char *fname = fl_file_chooser( LBL_INSERT_FILE_CHOOSER, "*.{avi,mpg,jpg}","",  0 );
  if (fname != NULL) {
    ui->set_memory_mode();
    ui_load_file(ui,fname);
    ui->file_changed = TRUE;
    ui->redraw_message = TRUE;
    return 1;
  }
}


// SAVE_AS
int ui_save_as(MUAN_UI *ui, Bool _quit)
{
  int is_fullhd=1;
  
  if(ui->is_save_as)
	  is_fullhd = fl_choice( MESSAGE_SAVE_AS_RESOLUTION, "FullHD", LBL_SAVE_AS_RESOLUTION, NULL );

  char *fname = fl_file_chooser( LBL_SAVE_FILE_CHOOSER, "*.avi", ui->save_path , 0 );
  Bool sobrescrever = FALSE;

  while ((fname != NULL) && (!sobrescrever)) {
    fl_filename_setext(fname, ".avi");
    if (ui->file_exists(fname)) {
      //confirma sobrescrever?
      switch (fl_choice(MSG_OVERWRITE_FILE, LBL_CANCEL, LBL_YES, LBL_NO)) {
      case 0: fname=NULL;
        break;
      case 1: sobrescrever = TRUE;
        break;
      case 2: fname = fl_file_chooser( LBL_SAVE_FILE_CHOOSER, "*.avi", ui->file_name , 0 );
        break;
      }
    } else  {
      sobrescrever = TRUE;  //se arquivo nao existe
    }
  }

  if (fname != NULL)  {
	if(is_fullhd == 0) {
	  ui->out_width = 1920;
	  ui->out_height = 1080;
	} else {
		strcpy(ui->file_name, fname);
	}

    ui->save_file(fname, _quit);
    ui->file_changed = FALSE;
    return 1;
  }
  return 0;
}

// save file
void ui_save_file(MUAN_UI *ui, char* _fname, Bool _quit)
{
  VideoEncoder encoder;
  setMessage(MSG_SAVE);
  ui->imgv->is_saving = TRUE;
  ui->win_principal->deactivate();
  ui->redraw_message = TRUE;
  Fl::wait(0);
  encoder.avi_write( _fname, ui->imgv->imgl, AVI_DV2_FORMAT, MAX_FRAMES, MAX_FILE_SIZE, false, false, ui->out_width, ui->out_height);
  ui->win_principal->activate();
  ui->imgv->is_saving = FALSE;
  setMessage("");
  ui->redraw_message = TRUE;
  ui->out_width=0;
  ui->out_height=0;
}

// SAVE
int ui_save(MUAN_UI *ui, Bool _quit)
{
    if (ui->file_name[0] == '\0' || ui->is_save_as == TRUE) //arquivo ainda nao salvo
    {
      return ui->save_as(_quit);
    }
    else //arquivo ja salvo
    {
      ui_save_file(ui, ui->file_name, _quit);
      ui->file_changed = FALSE;
      return 1;
    }
}

/*
 * IMPORT IMAGES
 */
int ui_import_jpg_list(MUAN_UI *ui)
{

  char* fname = fl_dir_chooser(LBL_IMPORT_JPEG_FILE_CHOOSER, ui->save_path, 0);

  if (fname != NULL) {
    ui->win_principal->cursor(FL_CURSOR_WAIT);
    Fl::check();
    ui->set_memory_mode();
    VideoEncoder encoder;
    encoder.jpg_read(ui->imgv->imgl, fname, ui->load_mode);
    ui->file_changed = TRUE;
    ui->redraw_message = TRUE;
    ui->win_principal->cursor(FL_CURSOR_DEFAULT);
    Fl::check();
    return 1;
  }
  return 0;
}

// EXPORT_FILE
void ui_export_file(MUAN_UI *ui, char* fname)
{
  if (strlen(fname)>0) {
    ui->win_principal->cursor(FL_CURSOR_WAIT);
    Fl::check();
    VideoEncoder encoder;
    char *ext = strrchr(fname, '.');
    char filename[250];
    strncpy(filename, fname, ext-fname);
    filename[ext-fname]='\0';

    if ((strcmp(ext, ".jpg")==0) || (strcmp(ext, ".JPG")==0))  {
      encoder.jpg_write( ui->imgv->imgl, filename, JPEG_QUALITY);
    }  else if ((strcmp(ext, ".avi")==0) || (strcmp(ext, ".AVI")==0))  {
      encoder.avi_write( fname, ui->imgv->imgl, AVI_DV2_FORMAT, MAX_FRAMES, MAX_FILE_SIZE, false, false, ui->out_width, ui->out_height);
    }  else if ((strcmp(ext, ".mpg")==0) || (strcmp(ext, ".MPG")==0))  {
      encoder.mpg_write( ui->imgv->imgl, fname, ui->out_width, ui->out_height);
    }
    ui->win_principal->cursor(FL_CURSOR_DEFAULT);
    Fl::check();
  }
}

// EXPORT
void ui_export(MUAN_UI *ui)
{
    Bool ok = FALSE;
    char *fname = fl_file_chooser( LBL_EXPORT_FILE_CHOOSER, "*.{avi,jpg,mpg}", ui->save_path, 0 );
    Bool sobrescrever = FALSE;

    while ((!ok) && (fname != NULL))  {
      char *ext = strrchr(fname, '.');
      if (ext == NULL) {
        fl_alert(MSG_INFORM_FILE_FORMAT);
        fname = fl_file_chooser( LBL_EXPORT_FILE_CHOOSER, "*.{avi,jpg,mpg}", fname, 0 );
        continue;
      }
      else {
        if ( (strcmp(ext, ".avi")==0)||(strcmp(ext, ".AVI")==0) ||
             (strcmp(ext, ".jpg")==0)||(strcmp(ext, ".JPG")==0) ||
             (strcmp(ext, ".mpg")==0)||(strcmp(ext, ".MPG")==0)   )
          ok = TRUE;
        else {
          fl_alert(MSG_INVALID_FILE_FORMAT);
          fname = fl_file_chooser( LBL_EXPORT_FILE_CHOOSER, "*.{avi,jpg,mpg}", fname, 0 );
          continue;
        }
      }

      if (ui->file_exists(fname))  {
        //confirma sobrescrever?
        switch (fl_choice(MSG_OVERWRITE_FILE, LBL_CANCEL, LBL_YES, LBL_NO))  {
          case 0: fname=NULL;
                  ok=TRUE;
                  break;
          case 1: ok = TRUE;
                  break;
          case 2: fname = fl_file_chooser( LBL_EXPORT_FILE_CHOOSER, "*.{avi,jpg,mpg}", ui->file_name, 0 );
                  break;
        }
      } else    //se arquivo nao existe
      {
        ok = TRUE;
      }
    } // fim while

    if (fname != NULL) {
      ui_export_file(ui, fname);
    }
}

// CHANGE MODE CAMERA/MEMORY
void ui_change_mode(MUAN_UI *ui)
{
    ui->camera_on = !ui->camera_on;
    ui->imgv->setModeViewer(ui->camera_on, FALSE, setLabelModeViewer);
}

// FIRST
void ui_first(MUAN_UI *ui)
{
  ui->set_memory_mode ();
  ui->imgv->stop ();
  imglist_rew (ui->imgv->imgl);
  ui->sl_timeline->value (imglist_getCurrentFnum(ui->imgv->imgl));
}

// REW
void ui_rew(MUAN_UI *ui)
{
  ui->set_memory_mode ();
  ui->imgv->stop ();
  imglist_step_backward (ui->imgv->imgl);
  ui->sl_timeline->value (imglist_getCurrentFnum(ui->imgv->imgl));
}

// PAUSE
void ui_pause(MUAN_UI *ui)
{
  ui->imgv->stop();
  imglist_step_foward (ui->imgv->imgl);
  ui->sl_timeline->value (imglist_getCurrentFnum(ui->imgv->imgl));
}

// PLAY
void ui_play(MUAN_UI *ui)
{
  ui->set_memory_mode ();
  char s[10];
  int beginValue = atoi (ui->edt_begin->value ());
  int endValue = atoi (ui->edt_end->value ());
  if (ui->btn_range->value ())    {
    if (beginValue <= 0)	{
      beginValue = 1;
    }
    if (endValue <= 0)	{
      endValue = imglist_getTotalRealFrames (ui->imgv->imgl);
    }
    ui->imgv->playInRange (beginValue, endValue);
  }  else    {
    ui->sl_timeline->redraw();
    imglist_rew (ui->imgv->imgl);
    ui->sl_timeline->range(1, imglist_getTotalFrames (ui->imgv->imgl));
    ui->imgv->play ();
    ui->sl_timeline->value (imglist_getCurrentFnum(ui->imgv->imgl));
    ui->sl_timeline->redraw();
  };
}

// FWD
void ui_fwd(MUAN_UI *ui)
{
  ui->set_memory_mode();
  ui->imgv->stop();
  imglist_step_foward(ui->imgv->imgl );
  ui->sl_timeline->value (imglist_getCurrentFnum(ui->imgv->imgl));
}

// LAST
void ui_last(MUAN_UI *ui)
{
  ui->set_memory_mode();
  ui->imgv->stop();
  imglist_go_to_end( ui->imgv->imgl );
  ui->sl_timeline->value (imglist_getCurrentFnum(ui->imgv->imgl));
}

// GOTO
void ui_go_to_frame(MUAN_UI *ui)
{
  if (ui->camera_on) {
  ui->camera_on = FALSE;
  ui->imgv->setModeViewer(ui->camera_on, FALSE, setLabelModeViewer);
  }

  char s[10];
  int value = atoi(ui->edt_go_to_frame->value());
  if(value > 0) {
    int totalFrames = imglist_getTotalFrames(ui->imgv->imgl);
    if(value > totalFrames) {
      value = totalFrames;
      sprintf(s, "%5i", value);
      ui->edt_go_to_frame->value(s);
    }
  } else {
    value = 1;
    sprintf(s, "%5i", value);
    ui->edt_go_to_frame->value(s);
  }
  ui->imgv->goToFrame(/*out_current_frame_duration,*/ value);
  ui->imgv->redraw();

  ui->edt_go_to_frame->value(NULL);
  ui->sl_timeline->value (imglist_getCurrentFnum(ui->imgv->imgl));
}

// DURATION
void ui_duration(MUAN_UI *ui)
{
  int value = -1;
  if (strcmp(ui->edt_duration->value(), "") > 0) { 
    char s[10];
    value = atoi(ui->edt_duration->value());
    if (value <= 0 || value > 120) {
      if (value <= 0) value = 1;
      if (value > 120) value = 120;
      sprintf(s,"%d", value);
      ui->edt_duration->value(s);
    }
  }
  if (!ui->camera_on){
    int beginValue=imglist_getCurrentFnum(ui->imgv->imgl);
    int endValue=imglist_getCurrentFnum(ui->imgv->imgl);

    if(ui->btn_range->value()) {
      beginValue = atoi(ui->edt_begin->value());
      endValue = atoi(ui->edt_end->value());
      if(beginValue <= 0) {
        beginValue = 1;
      }
      if(endValue <= 0) {
        endValue = ui->imgv->imgl->totFrames;
      }
    }
    if (value > 0) {
      imglist_setFrameDuration(ui->imgv->imgl, beginValue, endValue, value);
      ui->file_changed = TRUE;
    }
    ui->imgv->redraw();
    ui->edt_duration->value(NULL);
  }
}

// CAPTURE
void ui_capture(MUAN_UI *ui)
{
  if (!ui->camera_on){
    ui->camera_on = TRUE;
    ui->imgv->setModeViewer(ui->camera_on, FALSE, setLabelModeViewer);
  }
  ui->imgv->stop ();
  int duration = atoi(ui->edt_duration->value());
  if(duration > 0) {
    ui->imgv->insert_frame(3, duration);
  } else {
    ui->imgv->insert_frame(3, ui->duration_default);
  }
  if (ui->play_sound)
      PlayBeepSound();
  ui->file_changed = TRUE;
  ui->sl_timeline->range (1, imglist_getCurrentFnum(ui->imgv->imgl));
  ui->sl_timeline->value(imglist_getCurrentFnum(ui->imgv->imgl));
  ui->sl_timeline->redraw ();
}

// ABOUT
void ui_about(MUAN_UI *ui)
{
  ui->make_about_window();
  ui->win_about->end();
  ui->win_about->set_modal();
  ui->win_about->show();
  while (ui->win_about->shown())
    Fl::wait();
  free(ui->win_about);
}

// MANUAL
void ui_manual(MUAN_UI *ui)
{
    char* aux = (char *) malloc(strlen(MANUAL_FILE_AE)+11);

#ifdef WIN32
    strcpy(aux, "start ");
#elif defined __APPLE__
    strcpy(aux, "open ");
#else
    strcpy(aux, "xdg-open ");
#endif
    aux = strcat(aux, MANUAL_FILE_AE);
    int status = system(aux);
}

// BUG_REPORT
void ui_bug_report(MUAN_UI *ui)
{

    char* aux = (char *) malloc(strlen(BUG_REPORT)+11);

#ifdef WIN32
    strcpy(aux, "start ");
#elif defined __APPLE__
    strcpy(aux, "open ");
#else
    strcpy(aux, "xdg-open ");
#endif

    aux = strcat(aux, BUG_REPORT);
    int status = system(aux);

}

// REMOVE
void ui_remove(MUAN_UI *ui)
{
  if (!ui->camera_on) {
    int resposta;
    int beginValue=imglist_getCurrentFnum(ui->imgv->imgl);
    int endValue=imglist_getCurrentFnum(ui->imgv->imgl);

    if(ui->btn_range->value()) {
      if (fl_choice(MSG_CONFIRM_REMOVE_RANGE, LBL_NO, NULL, LBL_YES))    {
        resposta = 1;
        beginValue = atoi(ui->edt_begin->value());
        endValue = atoi(ui->edt_end->value());
        if(beginValue <= 0) {
          beginValue = 1;
        }
        if(endValue <= 0) {
          endValue = ui->imgv->imgl->totFrames;
        }
      } else
        resposta = 0;
    }  else
      resposta = (fl_choice(MSG_CONFIRM_REMOVE, LBL_NO, NULL, LBL_YES));

    if (resposta)  {
      imglist_removeInRange( ui->imgv->imgl, beginValue, endValue );
      ui->edt_begin->value(NULL);
      ui->edt_end->value(NULL);
      ui->btn_range->value(0);
      ui->file_changed = TRUE;
      ui->redraw_message = TRUE;
    }
  } else {
    fl_alert(MSG_CANT_REMOVE);
  };
}

// TIMELINE
void ui_timeline(MUAN_UI *ui)
{
  ui->sl_timeline->type(FL_HOR_NICE_SLIDER);
  ui->sl_timeline->redraw();
  ui->set_memory_mode();
  ui->imgv->stop();
  ui->sl_timeline->range(1, ui->imgv->imgl->totFrames);
  ui->imgv->goToFrame(ui->sl_timeline->value());
  ui->imgv->redraw();
}

#ifdef MUAN_AE

// SELECT LUA PLUGIN MODULE
void ui_plugin_select(MUAN_UI *ui, int type)
{
  static char fbutton_label[32];
  static char mbutton_label[32];
  char *modules_dir = plugin_path(type);
  char *end, *fullname = fl_file_chooser( "Select Camera Plugin", "*.lua", modules_dir,  0 );
  if (fullname == NULL)
    return;
  if (type == 0) {
    strncpy(fbutton_label, fl_filename_name(fullname), 32);
    end=rindex(fbutton_label, '.'); 
    if (end != NULL) *end = '\0';
    ui->btn_fselect->label(fbutton_label);
  } else if (type == 1) {
    strncpy(mbutton_label, fl_filename_name(fullname), 32);
    end=rindex(mbutton_label, '.'); *end = '\0';
    ui->btn_mselect->label(mbutton_label);
  }
  plugin_select(type, fullname);
}


// CAMERA FILTER - LUA PLUGIN
void ui_filter(MUAN_UI *ui)
{
  if (!plugin_loaded(PLUGIN_CAM)) {
    fl_alert("(Function Undefined) - Please Select a Camera Filter");
    ui->btn_filter->value(!ui->btn_filter->value());
    return;
  }
  ui->imgv->filter_on = ui->btn_filter->value();
  if (ui->imgv->filter_on) {
    if (!ui->camera_on) {
      ui->camera_on = !ui->camera_on;
      ui->imgv->setModeViewer(ui->camera_on, FALSE, setLabelModeViewer);
    }
    int value = atoi(ui->edt_duration->value());
    if (value <= 0)
      value = ui->duration_default;
    if (camfilter_init(imglist_peek_current_frame(ui->imgv->imgl), value) == -1)
      ui_setfilter(FALSE);
  } else {
    camfilter_close();
  }
  ui->imgv->redraw();
}

// PROCESS FILTER - LUA PLUGIN
#undef PROC_CONFIRM
#define PROC_MESSAGE

void ui_process(MUAN_UI *ui)
{
  int resposta=TRUE;
  int beginValue=1;
  int endValue=imglist_getTotalFrames(ui->imgv->imgl);

  if (!plugin_loaded(PLUGIN_MEM)) {
    fl_alert("(Function Undefined) - Please Select a Memory Filter");
    return;
  }
#ifdef PROC_CONFIRM
  if (fl_choice(MSG_CONFIRM_PROCESS, LBL_NO, NULL, LBL_YES)==FALSE) 
    return;
#endif
  if (ui->imgv->filter_on)	{
   ui->btn_filter->value(!ui->btn_filter->value());
   ui_filter(ui);
  }
  if(ui->btn_range->value()) {
    beginValue = atoi(ui->edt_begin->value());
    endValue = atoi(ui->edt_end->value());
    if(beginValue <= 0)
      beginValue = 1;
  } else {
    if(endValue <= 0)
      endValue = ui->imgv->imgl->totFrames;
  }
  if (resposta)  {
    Frame *frm; int i;
    if (procfilter_init(imglist_peek_current_frame(ui->imgv->imgl), endValue-beginValue+1) == -1)
      return;
    ui->set_memory_mode();
#ifdef PROC_MESSAGE
    ui->imgv->is_saving = 2;
    setMessage("Processing Frames");
    ui->win_principal->deactivate();
    ui->redraw_message = TRUE;
    Fl::wait(0);
#endif
    for (i = beginValue; i <= endValue; i++) {
      imglist_go_to_frame(ui->imgv->imgl, i);
      frm = imglist_peek_current_frame(ui->imgv->imgl);
      if (procfilter_exec(frm, i) == -1)
	break;
    }
    ui->btn_range->value(0);
#ifdef PROC_MESSAGE
    ui->win_principal->activate();
    ui->imgv->is_saving = FALSE;
    setMessage("");
    ui->redraw_message = TRUE;
#endif
    procfilter_close();
  }
}

#endif

#endif
