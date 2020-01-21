/**
 * This file contains the labels, hints and messages for system Muan user interface in diferent languages.
 \file lang_ui.h
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


#ifndef LANG_UI_H
#define LANG_UI_H

#include <string.h>
#include "defaults.h"


#if defined(__APPLE__)
    #define Aacute "\347"
    #define Acirc  "\345"
    #define Uacute "\362"
    #define agrave "\210"
    #define aacute "\207"
    #define acirc  "\211"
    #define atilde "\213"
    #define ccedil "\215"
    #define eacute "\216"
    #define ecirc  "\220"
    #define iacute "\222"
    #define ntilde "\226"
    #define oacute "\227"
    #define otilde "\233"
    #define uacute "\234"
    #define ucirc  "\236"
#else
    #define Aacute "\301"
    #define Acirc  "\302"
    #define Uacute "\332"
    #define agrave "\340"
    #define aacute "\341"
    #define acirc  "\342"
    #define atilde "\343"
    #define ccedil "\347"
    #define eacute "\351"
    #define ecirc  "\352"
    #define iacute "\355"
    #define ntilde "\361"
    #define oacute "\363"
    #define otilde "\365"
    #define uacute "\372"
    #define ucirc  "\373"
#endif


//==============================================================================
#ifdef LANG_EN
//==============================================================================
  #define LBL_MUAN "Manipulator Universal of ANimation"

#ifdef WIN32
  #define MANUAL_FILE_OS MUAN_MANUAL_PATH "\muan_os_en.html"
  #define MANUAL_FILE_AE MUAN_MANUAL_PATH "\muan_ae_en.html"
#else
  #define MANUAL_FILE_OS MUAN_MANUAL_PATH "/muan_os_en.html"
  #define MANUAL_FILE_AE MUAN_MANUAL_PATH "/muan_ae_en.html"
#endif

  #define LBL_WIN_SPLASH "MUAN* - version " MUAN_VERSION
  #define LBL_COORD "Concept and Application"
  #define LBL_DESENVOLVIMENTO "System Development"
  #define LBL_PARCERIA "Technological Partnership"
  #define LBL_BTN_START "Start..."

  #define SPLASH_IMAGE "EN"

  #define LBL_WIN_ABOUT "About"
  #define LBL_TEXTO_ABOUT "MUAN is a Stop Motion Animation System. The system allows animation movie production offering an integrated kit of hardware and software. It consist of a computer with Linux, Mac OS or Windows, a digital video camera and support over necessary accessories. The software was conceived by ANIMA MUNDI and developed by the VISGRAF Laboratory with the sponsorship of IBM."
  #define LBL_LINK_SITE "For more information, visit the website http://www.visgraf.impa.br/muan2/"

  #define LBL_BTN_CLOSE "Close"

#define LBL_WIN_PRINCIPAL "IMPA-VISGRAF/ Anima Mundi                                   MUAN* " MUAN_VERSION "                               Technological Partnership IBM"
  #define LBL_WIN_TOOL "Tools"
  #define LBL_WIN_IMAGE "Capture Window"
  #define LBL_WIN_IMGTOOL "Navigation"
  #define LBL_WIN_INFO "Info"
  
  #define LBL_BTN_EXIT "Exit"
  #define HNT_BTN_EXIT "Quit the application"

  #define LBL_BTN_NEW "New"
  #define HNT_BTN_NEW ""

  #define LBL_BTN_LOAD "Load"
  #define HNT_BTN_LOAD ""

  #define LBL_BTN_INSERT "Insert"
  #define HNT_BTN_INSERT ""

  #define LBL_BTN_SAVE "Save"
  #define HNT_BTN_SAVE ""

  #define LBL_BTN_SAVE_AS "Save As"
  #define HNT_BTN_SAVE_AS ""

  #define LBL_BTN_EXPORT "Export"
  #define HNT_BTN_EXPORT "Export animation as mpg video or jpg image list"

  #define LBL_BTN_IMPORT "Import Images"
  #define HNT_BTN_IMPORT "Import jpg images from directory"

  #define LBL_BTN_FULLSCR "Full Screen"
  #define HNT_BTN_FULLSCR ""

  #define LBL_BTN_MODE_CAM "Camera -> Memory"
  #define LBL_BTN_MODE_MEM "Memory -> Camera"
  #define HNT_BTN_MODE ""
  
  #define LBL_BTN_RANGE "Range"
  #define HNT_BTN_RANGE ""

  #define LBL_BTN_BEGIN "Begin"
  #define HNT_BTN_BEGIN "In memory mode, click to set the current frame as the beginning of the range."

  #define LBL_BTN_END "End"
  #define HNT_BTN_END "In memory mode, click to set the current frame as the end of the range."

  #define LBL_BTN_LOOP "Loop"
  #define HNT_BTN_LOOP ""

  #define LBL_BTN_FLICK "Flip"
  #define HNT_BTN_FLICK ""

  #define HNT_BTN_FIRST "First"
  #define HNT_BTN_REW "Back"
  #define HNT_BTN_PAUSE "Pause"
  #define HNT_BTN_PLAY "Play"
  #define HNT_BTN_FWD "Next"
  #define HNT_BTN_LAST "Last"

  #define LBL_EDT_GO_TO "Go to"
  #define HNT_EDT_GO_TO ""

  #define LBL_EDT_DURATION "Duration"
  #define HNT_EDT_DURATION ""

  #define LBL_BTN_COPY "Copy"
  #define HNT_BTN_COPY ""

  #define LBL_BTN_PASTE "Paste"
  #define HNT_BTN_PASTE ""

  #define LBL_BTN_INVERTED_PASTE "Inverted Paste"
  #define HNT_BTN_INVERTED_PASTE ""

  #define LBL_BTN_CAPTURE "CAPTURE"
  #define HNT_BTN_CAPTURE ""

  #define LBL_VERSION "MUAN* " MUAN_VERSION

  #define LBL_BTN_ABOUT "About"
  #define HNT_BTN_ABOUT ""

  #define LBL_BTN_MANUAL "Manual"
  #define HNT_BTN_MANUAL ""

  #define LBL_BTN_BUG "Bug Report"
  #define HNT_BTN_BUG ""

  #define LBL_BTN_PROCESS "Process Frames"
  #define HNT_BTN_PROCESS ""

  #define LBL_BTN_FILTER "Camera Filter"
  #define HNT_BTN_FILTER ""
  
  #define LBL_BTN_MSELECT "select filter"
  #define HNT_BTN_MSELECT ""

  #define LBL_BTN_FSELECT "select filter"
  #define HNT_BTN_FSELECT ""

  #define LBL_BTN_PREFERENCES "Preferences"
  #define HNT_BTN_PREFERENCES ""

  #define LBL_BTN_CLEAR "Clear"
  #define HNT_BTN_CLEAR " Clear ALL frames"
  
  #define LBL_BTN_REMOVE "Remove"
  #define HNT_BTN_REMOVE "Remove the actual frame"

  #define LBL_BTN_REMOVE_DIRECT "Remove without confirmation"
  #define HNT_BTN_REMOVE_DIRECT "Remove the current frame without confirmation"

  #define LBL_GB_CURRENT "Current"

  #define LBL_OUT_FRAME_NUMBER "Capture"
  #define HNT_OUT_FRAME_NUMBER ""

  #define LBL_OUT_CURRENT_FRAME_DURATION "Duration"
  #define HNT_OUT_CURRENT_FRAME_DURATION ""

  #define LBL_OUT_FRAME_POS "Frame"
  #define HNT_OUT_FRAME_POS ""

  #define LBL_GB_TOTAL "Total"

  #define LBL_OUT_TOT_IMG_CAP "Captures"
  #define HNT_OUT_TOT_IMG_CAP ""

  #define LBL_OUT_TOT_FRAMES "Frames"
  #define HNT_OUT_TOT_FRAMES ""

  #define LBL_OUT_FILE_NAME "File:"
  #define HNT_OUT_FILE_NAME ""



  #define LBL_WIN_PREFERENCES       "Preferences"
  #define LBL_CMB_LOAD_MODE         "Load Mode        "
  #define LBL_MODO_NUM_MUAN         "Using MUAN numbering"
  #define LBL_MODO_COMPARA_FRAMES   "Compare Frames"
  #define LBL_MODO_TODOS_FRAMES     "All Frames        "
  #define LBL_EDT_FIRST_FRAME_FILE  "First Frame       "
  #define HNT_BTN_FIRST_FRAME_FILE  "Select file"
  #define LBL_EDT_SAVE_PATH         "Save Path       "
  #define HNT_BTN_SAVE_PATH         "Select directory"
  #define LBL_EDT_DURATION_DEFAULT  "Default Duration"
  #define LBL_CK_SHOW_SPLASH        "Show Splash"
  #define LBL_CK_AUTO_SAVE          "Auto Save"
  #define LBL_EDT_AUTO_SAVE_FILE    "File "
  #define HNT_BTN_AUTO_SAVE_FILE    "Select file"
  #define LBL_AUTO_SAVE_TIME        "Time"
  #define LBL_OUT_SECONDS           "seconds"
  #define LBL_FIRST_FRAME_FILE_CHOOSER "Select the first frame file"
  #define LBL_SAVE_PATH_DIR_CHOOSER    "Select the directory where to save animations"
  #define LBL_AUTO_SAVE_FILE_CHOOSER   "Inform the name of the auto save avi file"
  #define LBL_GB_CAMERA_CONNECTION     "Camera Connection"
  #define LBL_GB_FW_CONF              "Firewire Configuration"
  #define LBL_EDT_FW_DEVICE_NAME      "Device Name"
  #define LBL_GB_V4L_CONF              "V4L Configuration"
  #define LBL_EDT_V4L_DEVICE_NAME          "Device Name"


  #define LBL_YES "Yes"
  #define LBL_NO "No"
  #define LBL_CANCEL "Cancel"
    
  #define LBL_LOAD_FILE_CHOOSER "Load file..."
  #define LBL_INSERT_FILE_CHOOSER "Insert file..."
  #define LBL_IMPORT_JPEG_FILE_CHOOSER "Import jpeg images from..."
  #define LBL_EXPORT_FILE_CHOOSER "Export animation..."
  #define MSG_SAVE "Saving ..."
  #define LBL_SAVE_FILE_CHOOSER "Saving avi file..."
  #define LBL_SAVE_FILE_CHOOSER_TO_CLOSE "Saving AVI to close application..."
  #define LBL_CONFIRM_SAVE_TO_CLOSE "Closing application. File is not save.\nSave now?"
  #define LBL_CONFIRM_SAVE "File is not save.\nSave now?"
  #define MSG_INVALID_FILE_FORMAT "Invalid file format.\n"
  #define MSG_INFORM_FILE_FORMAT "Inform file format (file extension)."
  #define MSG_OVERWRITE_FILE "File already exists.\nOverwrite?"
  
  #define MSG_CONFIRM_CLEAR "Are you sure you want to remove ALL frames?"
  #define MSG_CONFIRM_REMOVE_RANGE "Are you sure you want to remove ALL frames IN RANGE?"
  #define MSG_CONFIRM_REMOVE "Are you sure you want to remove this frame?"
  #define MSG_CANT_REMOVE "Operation not allowable. Change to Memory Mode."

  #define MSG_CONFIRM_PROCESS "Are you sure you want to process frames?"
  
  #define MSG_WRONG_DEVICE "MUAN Error: Wrong device configuration\n"
  #define MSG_CAMERA_OFF "Camera off. Application in Memory Mode."
  #define MSG_INFORM_CAPTURE_NUMBER "Inform capture number:"
  #define MSG_INVALID_FRAME_NUMBER "Invalid frame number!"
  #define MSG_INVALID_RANGE "Invalid range! Redefine."
  #define LBL_CAMERA "CAMERA"
  #define LBL_SAVING "...SAVING..."

  #define LBL_MN_SYSTEM "&System"
  #define LBL_MN_FILE "&File"
  #define LBL_MN_VIEW "&View"
  #define LBL_MN_TOOLBARS "&Toolbars"
  #define LBL_MN_VIEW_TOOL "&Main Toolbar"
  #define LBL_MN_VIEW_IMGTOOL "&Navigation Toolbar"
  #define LBL_MN_VIEW_IMAGE "&Capture Window"
  #define LBL_MN_VIEW_INFO "&Information Window"
  
  #define LBL_MN_ANIMATION "&Animation"
  #define LBL_MN_HELP "&Help"

  #define LBL_UNTITLED "Untitled"

  #define LBL_GB_IMAGE_SIZE "Image Size"

  #define MESSAGE_CHOICE "Changing Camera Connection: MUAN will save prefs and quit"
  #define MESSAGE_CHOICE_ALL "MUAN will save prefs and quit"

  #define MESSAGE_SAVE_AS_RESOLUTION "Save with resolution"
  #define LBL_SAVE_AS_RESOLUTION "Current"

#else

//==============================================================================
#ifdef LANG_SP
//==============================================================================

  #define LBL_MUAN "Manipulador Universal de ANimaciones"

#ifdef WIN32
  #define MANUAL_FILE_OS MUAN_MANUAL_PATH "\muan_os_sp.html"
  #define MANUAL_FILE_AE MUAN_MANUAL_PATH "\muan_ae_sp.html"
#else
  #define MANUAL_FILE_OS MUAN_MANUAL_PATH "/muan_os_sp.html"
  #define MANUAL_FILE_AE MUAN_MANUAL_PATH "/muan_ae_sp.html"
#endif

  #define LBL_WIN_SPLASH "MUAN* - version " MUAN_VERSION
  #define LBL_COORD "Coordinaci" oacute "n"
//  #define LBL_DESENVOLVIMENTO "Desenvolvimiento"
  #define LBL_DESENVOLVIMENTO "Desarrollo"
  #define LBL_PARCERIA "Sociedad Tecnol" oacute "gica"
  #define LBL_BTN_START "Iniciar..."

  #define SPLASH_IMAGE "SP"

  #define LBL_WIN_ABOUT "Sobre"
  #define LBL_TEXTO_ABOUT "Muan es un sistema de animaci" oacute "n stop motion. El sistema permite la producci" oacute "n de pel" iacute "cula de animaci" oacute "n que oferece un kit integrado de hardware y software. Se compone de un ordenador con Linux, Mac OS o Windows, una c" aacute "mara de v" iacute "deo digital y soporte para otros dispositivos. El software fue concebido por Anima Mundi y desarrollado por el Laboratorio VISGRAF con el apoyo de IBM."
  #define LBL_LINK_SITE "Para obtener m" aacute "s informaci" oacute "n, visite el sitio http://www.visgraf.impa.br/muan2/"
  #define LBL_BTN_CLOSE "Cerrar"

  #define LBL_WIN_PRINCIPAL "IMPA-VISGRAF/ Anima Mundi                                   MUAN* " MUAN_VERSION "                                  Sociedade Tecnologica IBM"
  #define LBL_WIN_TOOL "Herramientas"
  #define LBL_WIN_IMAGE "Pantalla de la Imagen"
  #define LBL_WIN_IMGTOOL "Navegaci" oacute "n"
  #define LBL_WIN_INFO "Informaci" oacute "n"

  #define LBL_BTN_EXIT "Salir"
  #define HNT_BTN_EXIT "Cerrar aplicaci" oacute "n"

  #define LBL_BTN_NEW "&Nuevo"
  #define HNT_BTN_NEW ""

  #define LBL_BTN_LOAD "Car&gar"
  #define HNT_BTN_LOAD ""

  #define LBL_BTN_INSERT "Insertar"
  #define HNT_BTN_INSERT ""

  #define LBL_BTN_SAVE "Guardar"
  #define HNT_BTN_SAVE ""
  
  #define LBL_BTN_SAVE_AS "Guardar Como"
  #define HNT_BTN_SAVE_AS ""
  
  #define LBL_BTN_EXPORT "Exportar"
  #define HNT_BTN_EXPORT "Exportar animaci" oacute "n como mpg ou lista de im" aacute "genes jpeg"

  #define LBL_BTN_IMPORT "Importar Im" aacute "genes"
  #define HNT_BTN_IMPORT "Importar lista de im" aacute "genes jpeg de un diret" oacute "rio"

  #define LBL_BTN_FULLSCR "Pant.Entera"
  #define HNT_BTN_FULLSCR "Pantalla Entera"

  #define LBL_BTN_MODE_CAM "C" aacute "mara -> Memoria"
  #define LBL_BTN_MODE_MEM "Memoria -> C" aacute "mara"
  #define HNT_BTN_MODE ""
  
  #define LBL_BTN_RANGE "Rango"
  #define HNT_BTN_RANGE ""

  #define LBL_BTN_BEGIN "Inicio"
  //#define HNT_BTN_BEGIN "En el modo memoria, haga click para marcar el inicio del segmento como siendo el cuadro actual."
  #define HNT_BTN_BEGIN "En el modo memoria, pinche para marcar el inicio del segmento como siendo el cuadro actual."

  #define LBL_BTN_END "Fin"
  //#define HNT_BTN_END "En el modo memoria, haga click para marcar el fin del segmento como siendo el cuadro actual."
  #define HNT_BTN_END "En el modo memoria, pinche para marcar el fin del segmento como siendo el cuadro actual."

  #define LBL_BTN_LOOP "Loop"
  #define HNT_BTN_LOOP ""

  #define LBL_BTN_FLICK "Flip"
  #define HNT_BTN_FLICK ""

  #define HNT_BTN_FIRST "Primero"
  #define HNT_BTN_REW "Retroceder"
  #define HNT_BTN_PAUSE "Pausa"
  #define HNT_BTN_PLAY "Play"
  #define HNT_BTN_FWD "Siguiente"
  #define HNT_BTN_LAST "" Uacute "ltimo"

  #define LBL_EDT_GO_TO "Ir a"
  #define HNT_EDT_GO_TO ""

  #define LBL_BTN_COPY "Copia"
  #define HNT_BTN_COPY ""

  #define LBL_BTN_PASTE "Pasta"
  #define HNT_BTN_PASTE ""

  #define LBL_BTN_INVERTED_PASTE "Pasta Invertida"
  #define HNT_BTN_INVERTED_PASTE ""

  #define LBL_EDT_DURATION "Duraci" oacute "n"
  #define HNT_EDT_DURATION ""

  #define LBL_BTN_CAPTURE "CAPTURAR"
  #define HNT_BTN_CAPTURE ""

  #define LBL_VERSION "MUAN* " MUAN_VERSION

  #define LBL_BTN_ABOUT "Sobre"
  #define HNT_BTN_ABOUT ""

  #define LBL_BTN_MANUAL "Manual"
  #define HNT_BTN_MANUAL ""

  #define LBL_BTN_BUG "Informe de Errores"
  #define HNT_BTN_BUG ""

  #define LBL_BTN_PROCESS "Processa Frames"
  #define HNT_BTN_PROCESS ""

  #define LBL_BTN_FILTER "Filtro Camera"
  #define HNT_BTN_FILTER ""
  
  #define LBL_BTN_MSELECT "seleccionar filtro"
  #define HNT_BTN_MSELECT ""

  #define LBL_BTN_FSELECT "seleccionar filtro"
  #define HNT_BTN_FSELECT ""

  #define LBL_BTN_PREFERENCES "Preferencias"
  #define HNT_BTN_PREFERENCES ""

  #define LBL_BTN_CLEAR "Limpiar"
  #define HNT_BTN_CLEAR "Limpiar TODOS los cuadros"
  
  #define LBL_BTN_REMOVE "Remover"
  #define HNT_BTN_REMOVE "Remover el cuadro actual"

  #define LBL_BTN_REMOVE_DIRECT "Remover sin confirmaci" oacute "n"
  #define HNT_BTN_REMOVE_DIRECT "Remover el cuadro actual sin confirmaci" oacute "n"

  #define LBL_GB_CURRENT "Actual"

  #define LBL_OUT_FRAME_NUMBER "Captura"
  #define HNT_OUT_FRAME_NUMBER ""

  #define LBL_OUT_CURRENT_FRAME_DURATION "Duraci" oacute "n"
  #define HNT_OUT_CURRENT_FRAME_DURATION ""

  #define LBL_OUT_FRAME_POS "Cuadro"
  #define HNT_OUT_FRAME_POS ""

  #define LBL_GB_TOTAL "Total"

  #define LBL_OUT_TOT_IMG_CAP "Capturas"
  #define HNT_OUT_TOT_IMG_CAP ""

  #define LBL_OUT_TOT_FRAMES "Cuadros"
  #define HNT_OUT_TOT_FRAMES ""

  #define LBL_OUT_FILE_NAME "Archivo:"
  #define HNT_OUT_FILE_NAME ""



  #define LBL_WIN_PREFERENCES       "Preferencias"
  #define LBL_CMB_LOAD_MODE         "Modo Cargar        "
  #define LBL_MODO_NUM_MUAN         "Usando numeraci" oacute "n del MUAN"
  #define LBL_MODO_COMPARA_FRAMES   "Comparando Cuadros"
  #define LBL_MODO_TODOS_FRAMES     "Todos los Cuadros"
  #define LBL_EDT_FIRST_FRAME_FILE  "Primer cuadro       "
  #define HNT_BTN_FIRST_FRAME_FILE  "Seleccionar archivo"
  #define LBL_EDT_SAVE_PATH         "Guardar en            "
  #define HNT_BTN_SAVE_PATH         "Seleccione directorio"
  #define LBL_EDT_DURATION_DEFAULT  "Duraci" oacute "n estandard"
  #define LBL_CK_SHOW_SPLASH        "Mostrar Splash"
  #define LBL_CK_AUTO_SAVE          "Guardar Autom" aacute "tico"
  #define LBL_EDT_AUTO_SAVE_FILE    "Archivo"
  #define HNT_BTN_AUTO_SAVE_FILE    "Seleccionar Archivo"
  #define LBL_AUTO_SAVE_TIME        "Tiempo "
  #define LBL_OUT_SECONDS           "segundos"
  #define LBL_FIRST_FRAME_FILE_CHOOSER "Seleccione el archivo del cuadro de abertura"
  #define LBL_SAVE_PATH_DIR_CHOOSER    "Seleccione el directorio"
  #define LBL_AUTO_SAVE_FILE_CHOOSER "Informe el nombre del archivo AVI donde la animaci" oacute "n ser" aacute " guardada autom" aacute "ticamente"
  #define LBL_GB_CAMERA_CONNECTION     "Camera Connection"
  #define LBL_GB_FW_CONF              "Firewire Configuraci" oacute "n"
  #define LBL_EDT_FW_DEVICE_NAME      "Device          "
  #define LBL_GB_V4L_CONF              "V4L Configuraci" oacute "n"
  #define LBL_EDT_V4L_DEVICE_NAME          "Device          "


  #define LBL_YES "Si"
  #define LBL_NO "No"
  #define LBL_CANCEL "Cancelar"
    
  #define LBL_LOAD_FILE_CHOOSER "Cargar archivo..."
  #define LBL_INSERT_FILE_CHOOSER "Inserir archivo..."
  #define LBL_IMPORT_JPEG_FILE_CHOOSER "Importar im" aacute "genes jpeg de ..."
  #define LBL_EXPORT_FILE_CHOOSER "Exportar animaci" oacute "n ..."
  #define MSG_SAVE "Guardando ..."
  #define LBL_SAVE_FILE_CHOOSER "Guardando archivo AVI..."
  #define LBL_SAVE_FILE_CHOOSER_TO_CLOSE "Guardando AVI para salir de la aplicaci" oacute "n..."
  #define LBL_CONFIRM_SAVE_TO_CLOSE "Cerrando la aplicaci" oacute "n. El archivo actual no est" aacute " guardado.\nDesea guardarlo ahora?"
  #define LBL_CONFIRM_SAVE "El archivo actual no est" aacute " guardado.\nDesea guardarlo ahora?"
  #define MSG_INVALID_FILE_FORMAT "Formato de archivo inv" aacute "lido.\n"
  #define MSG_INFORM_FILE_FORMAT "Informe la extensi" oacute "n (formato) del archivo."
//  #define MSG_OVERWRITE_FILE "El archivo ya existe.\nDesea re-escribirlo?"
  #define MSG_OVERWRITE_FILE "El archivo ya existe.\nDesea reescribirlo?"
  
  #define MSG_CONFIRM_CLEAR "Est" aacute " seguro que desea limpiar la animaci" oacute "n actual?\nTodos los cuadros seran perdidos."
  #define MSG_CONFIRM_REMOVE_RANGE "SEGMENTO ACTIVO! Est" aacute " seguro que desea remover TODOS los cuadros indicados?"
  #define MSG_CONFIRM_REMOVE "Est" aacute " seguro que desea remover el cuadro actual?"
  #define MSG_CANT_REMOVE "Esta operaci" oacute "n no ser" aacute " ejecutada. Alterne para el modo memoria para visualizar el(los) cuadro(s) a ser eliminado(s)."
  
  #define MSG_CONFIRM_PROCESS "Esta seguro que desea processar cuadros?"

  #define MSG_WRONG_DEVICE "MUAN Error: Configuraci" oacute "n del aparato equivocado\n"
  #define MSG_CAMERA_OFF "C" aacute "mara aparentemente apagada. Aplicaci" oacute "n en modo Memoria."
  #define MSG_INFORM_CAPTURE_NUMBER "Informe o número da captura desejada:"
  #define MSG_INVALID_FRAME_NUMBER "N" uacute "mero de cuadro inv" aacute "lido!"
  #define MSG_INVALID_RANGE "Rango inv" aacute "lido: redefinir."
  #define LBL_CAMERA "C" Aacute "MARA"
  #define LBL_SAVING "...GUARDANDO..."

  #define LBL_MN_SYSTEM "&Sistema"
  #define LBL_MN_FILE "&Archivo"
  #define LBL_MN_VIEW "&Exibir"
  #define LBL_MN_TOOLBARS "&Barras"
  #define LBL_MN_VIEW_TOOL "&Principal"
  #define LBL_MN_VIEW_IMGTOOL "&Navegaci" oacute "n"
  #define LBL_MN_VIEW_IMAGE "Pantalla de la &Imagen"
  #define LBL_MN_VIEW_INFO "Pantalla de la I&nformaci" oacute "n"
  #define LBL_MN_ANIMATION "&Animaci" oacute "n"
  #define LBL_MN_HELP "&Ayuda"


  #define LBL_UNTITLED "Nuevo"

  #define LBL_GB_IMAGE_SIZE "Tama" ntilde "o da imagem"

  #define MESSAGE_CHOICE "Conexi" oacute "n de la c" aacute "mara en constante cambio: MUAN ahorrar" aacute " Preferencias y salir"
  #define MESSAGE_CHOICE_ALL "El MUAN guarda las preferencias y cerrar"

  #define MESSAGE_SAVE_AS_RESOLUTION "Guardar con la resoluci" oacute "n"
  #define LBL_SAVE_AS_RESOLUTION "Corriente"

//==============================================================================
#else   //LANG_PT
//==============================================================================

  #define LBL_MUAN "Manipulador Universal de ANima" ccedil "" otilde "es"
#ifdef WIN32
  #define MANUAL_FILE_OS MUAN_MANUAL_PATH "\muan_os_pt.html"
  #define MANUAL_FILE_AE MUAN_MANUAL_PATH "\muan_ae_pt.html"
#else
  #define MANUAL_FILE_OS MUAN_MANUAL_PATH "/muan_os_pt.html"
  #define MANUAL_FILE_AE MUAN_MANUAL_PATH "/muan_ae_pt.html"
#endif
  #define LBL_WIN_SPLASH "MUAN* - vers" atilde "o " MUAN_VERSION
  #define LBL_COORD "Coordena" ccedil "" atilde "o"
  #define LBL_DESENVOLVIMENTO "Desenvolvimento"
  #define LBL_PARCERIA "Parceria Tecnol" oacute "gica"
  #define LBL_BTN_START "Iniciar..."

  #define SPLASH_IMAGE "PT"

  #define LBL_WIN_ABOUT "Sobre"
  #define LBL_TEXTO_ABOUT "O MUAN " eacute " um Sistema de Anima" ccedil "" atilde "o Stop Motion que permite produzir filmes de anima" ccedil "" atilde "o a partir de um kit integrado de hardware e software.  O sistema consiste de um computador com Linux, Mac Os ou Windows, uma c" acirc "mera de v" iacute "deo digital e suporte a outros dispositivos. O software foi concebido pelo ANIMA MUNDI e desenvolvido pelo Laborat" oacute "rio VISGRAF com o apoio da IBM."
  #define LBL_LINK_SITE "Para mais informa" ccedil "" otilde "es, visite o site http://www.visgraf.impa.br/muan2/"
  #define LBL_BTN_CLOSE "Fechar"

  #define LBL_WIN_PRINCIPAL "IMPA-VISGRAF/ Anima Mundi                                    MUAN* " MUAN_VERSION "                               Parceria Tecnol" oacute "gica IBM"
  #define LBL_WIN_TOOL "Principal"
  #define LBL_WIN_IMAGE "Janela de Captura"
  #define LBL_WIN_IMGTOOL "Navega" ccedil "" atilde "o"
  #define LBL_WIN_INFO "Informa" ccedil "" atilde "o"

  #define LBL_BTN_EXIT "Sair"
  #define HNT_BTN_EXIT "Fechar aplica" ccedil "" atilde "o"

  #define LBL_BTN_NEW "Novo"
  #define HNT_BTN_NEW "Cria uma nova anima" ccedil "" atilde "o vazia"

  #define LBL_BTN_LOAD "Carregar"
  #define HNT_BTN_LOAD "Abre uma arquivo existente"

  #define LBL_BTN_INSERT "Inserir"
  #define HNT_BTN_INSERT "Insere no arquivo atual uma anima" ccedil "" atilde "o em avi ou mpg ou ainda imagens ras ou jpg"

  #define LBL_BTN_SAVE "Salvar"
  #define HNT_BTN_SAVE "Salva o arquivo atual"
  
  #define LBL_BTN_SAVE_AS "Salvar Como"
  #define HNT_BTN_SAVE_AS "Salva (copia) o arquivo atual com outro nome"

  #define LBL_BTN_EXPORT "Exportar"
  #define HNT_BTN_EXPORT "Exportar anima" ccedil "" atilde "o como v" iacute "deo mpg ou lista de imagens jpg"

  #define LBL_BTN_IMPORT "Importar Imagens"
  #define HNT_BTN_IMPORT "Importar lista de imagens jpg a partir de um diret" oacute "rio"

  #define LBL_BTN_FULLSCR "Tela Cheia"
  #define HNT_BTN_FULLSCR ""

  #define LBL_BTN_MODE_CAM "C" acirc "mera -> Mem" oacute "ria"
  #define LBL_BTN_MODE_MEM "Mem" oacute "ria -> C" acirc "mera"
  #define HNT_BTN_MODE "Alterna entre os modos C" acirc "mera e Mem" oacute "ria"
  
  #define LBL_BTN_RANGE "Trecho"
  #define HNT_BTN_RANGE ""

  #define LBL_BTN_BEGIN "Inicio"
  #define HNT_BTN_BEGIN "No modo mem" oacute "ria, clique para marcar o Inicio do Trecho como sendo o frame atual."

  #define LBL_BTN_END "Fim"
  #define HNT_BTN_END "No modo mem" oacute "ria, clique para marcar o Fim do Trecho como sendo o frame atual."

  #define LBL_BTN_LOOP "Loop"
  #define HNT_BTN_LOOP ""

  #define LBL_BTN_FLICK "Flipar"
  #define HNT_BTN_FLICK ""

  #define LBL_BTN_FIRST "Primeiro"
  #define HNT_BTN_FIRST "Primeiro"
  #define LBL_BTN_REW "Anterior"
  #define HNT_BTN_REW "Anterior"
  #define LBL_BTN_PAUSE "Parar"
  #define HNT_BTN_PAUSE "Parar"
  #define LBL_BTN_PLAY "Tocar"
  #define HNT_BTN_PLAY "Tocar"
  #define LBL_BTN_FWD "Pr" oacute "ximo"
  #define HNT_BTN_FWD "Pr" oacute "ximo"
  #define LBL_BTN_LAST "" Uacute "ltimo"
  #define HNT_BTN_LAST "" Uacute "ltimo"

  #define LBL_EDT_GO_TO "Ir para"
  #define HNT_EDT_GO_TO ""

  #define LBL_BTN_COPY "Copiar"
  #define HNT_BTN_COPY ""

  #define LBL_BTN_PASTE "Colar"
  #define HNT_BTN_PASTE ""

  #define LBL_BTN_INVERTED_PASTE "Colar Invertido"
  #define HNT_BTN_INVERTED_PASTE ""

  #define LBL_EDT_DURATION "Dura" ccedil "" atilde "o"
  #define HNT_EDT_DURATION ""

  #define LBL_BTN_CAPTURE "CAPTURAR"
  #define HNT_BTN_CAPTURE ""

  #define LBL_VERSION "MUAN* " MUAN_VERSION

  #define LBL_BTN_ABOUT "Sobre"
  #define HNT_BTN_ABOUT ""

  #define LBL_BTN_MANUAL "Manual"
  #define HNT_BTN_MANUAL ""

  #define LBL_BTN_BUG "Reportar Erro"
  #define HNT_BTN_BUG ""

  #define LBL_BTN_PROCESS "Processa Frames"
  #define HNT_BTN_PROCESS ""

  #define LBL_BTN_FILTER "Filtro Camera"
  #define HNT_BTN_FILTER ""
  
  #define LBL_BTN_MSELECT "selecionar filtro"
  #define HNT_BTN_MSELECT ""

  #define LBL_BTN_FSELECT "selecionar filtro"
  #define HNT_BTN_FSELECT ""

  #define LBL_BTN_PREFERENCES "Preferencias"
  #define HNT_BTN_PREFERENCES ""

  #define LBL_BTN_CLEAR "Limpar"
  #define HNT_BTN_CLEAR "Apaga TODOS os frames da anima" ccedil "" atilde "o"
  
  #define LBL_BTN_REMOVE "Remover"
  #define HNT_BTN_REMOVE "Remove o frame atual"

  #define LBL_BTN_REMOVE_DIRECT "Remove sem confirma" ccedil "" atilde "o"
  #define HNT_BTN_REMOVE_DIRECT "Remove o frame atual sem confirma" ccedil "" atilde "o"

  #define LBL_GB_CURRENT "Atual"

  #define LBL_OUT_FRAME_NUMBER "Captura"
  #define HNT_OUT_FRAME_NUMBER ""

  #define LBL_OUT_CURRENT_FRAME_DURATION "Dura" ccedil "" atilde "o"
  #define HNT_OUT_CURRENT_FRAME_DURATION ""

  #define LBL_OUT_FRAME_POS "Frame"
  #define HNT_OUT_FRAME_POS ""

  #define LBL_GB_TOTAL "Total"

  #define LBL_OUT_TOT_IMG_CAP "Capturas"
  #define HNT_OUT_TOT_IMG_CAP ""

  #define LBL_OUT_TOT_FRAMES "Frames"
  #define HNT_OUT_TOT_FRAMES ""

  #define LBL_OUT_FILE_NAME "Arquivo:"
  #define HNT_OUT_FILE_NAME ""



  #define LBL_WIN_PREFERENCES       "Prefer" ecirc "ncias"
  #define LBL_CMB_LOAD_MODE         "Modo de carregar "
  #define LBL_MODO_NUM_MUAN         "Usando numera" ccedil "" atilde "o do MUAN"
  #define LBL_MODO_COMPARA_FRAMES   "Comparando Frames"
  #define LBL_MODO_TODOS_FRAMES     "Todos os Frames"
  #define LBL_EDT_FIRST_FRAME_FILE  "Frame de abertura"
  #define HNT_BTN_FIRST_FRAME_FILE  "Selecionar arquivo"
  #define LBL_CK_SHOW_SPLASH        "Exibir Splash"
  #define LBL_EDT_SAVE_PATH         "Salvar em              "
  #define HNT_BTN_SAVE_PATH         "Selecionar diret" oacute "rio"
  #define LBL_EDT_DURATION_DEFAULT  "Dura" ccedil "" atilde "o padr" atilde "o    "
  #define LBL_CK_AUTO_SAVE          "Salvar autom" aacute "tico"
  #define LBL_EDT_AUTO_SAVE_FILE    "Arquivo"
  #define HNT_BTN_AUTO_SAVE_FILE    "Selecionar arquivo"
  #define LBL_AUTO_SAVE_TIME        "Tempo   "
  #define LBL_OUT_SECONDS           "segundos"
  #define LBL_FIRST_FRAME_FILE_CHOOSER "Selecione o arquivo do frame de abertura"
  #define LBL_SAVE_PATH_DIR_CHOOSER    "Selecione o diret" oacute "rio onde salvar as anima" ccedil "" otilde "es"
  #define LBL_AUTO_SAVE_FILE_CHOOSER   "Informe o nome do arquivo AVI onde a anima" ccedil "" atilde "o ser" aacute " salva automaticamente"
  #define LBL_GB_CAMERA_CONNECTION     "Tipo de Conex" atilde "o"
  #define LBL_GB_FW_CONF              "Configura" ccedil "" otilde "es Firewire"
  #define LBL_EDT_FW_DEVICE_NAME          "Device          "
  #define LBL_GB_V4L_CONF              "Configura" ccedil "" otilde "es V4L"
  #define LBL_EDT_V4L_DEVICE_NAME          "Device          "



  #define LBL_YES "Sim"
  #define LBL_NO "N" atilde "o"
  #define LBL_CANCEL "Cancelar"
    
  #define LBL_LOAD_FILE_CHOOSER "Carregar arquivo..."
  #define LBL_INSERT_FILE_CHOOSER "Inserir arquivo..."
  #define LBL_IMPORT_JPEG_FILE_CHOOSER "Importar imagens JPG de ..."
  #define LBL_EXPORT_FILE_CHOOSER "Exportar anima" ccedil "" atilde "o ..."
  #define MSG_SAVE "Salvando..."
  #define LBL_SAVE_FILE_CHOOSER "Salvando arquivo avi..."
  #define LBL_SAVE_FILE_CHOOSER_TO_CLOSE "Salvando AVI para sair da aplica" ccedil "" atilde "o..."
  #define LBL_CONFIRM_SAVE_TO_CLOSE "Fechando aplica" ccedil "" atilde "o. O arquivo atual n" atilde "o est" aacute " salvo.\nDeseja salva-lo agora?"
  #define LBL_CONFIRM_SAVE "O arquivo atual n" atilde "o est" aacute " salvo.\nDeseja salva-lo agora?"
  #define MSG_INVALID_FILE_FORMAT "Formato de arquivo inv" aacute "lido\n"
  #define MSG_INFORM_FILE_FORMAT "Informe a extens" atilde "o (formato) do arquivo."
  #define MSG_OVERWRITE_FILE "Arquivo j" aacute " existente.\nDeseja sobrescreve-lo?"
  
  #define MSG_CONFIRM_CLEAR "Tem certeza que deseja limpar a anima" ccedil "" atilde "o atual?\nTodos os frames ser" atilde "o perdidos."
  #define MSG_CONFIRM_REMOVE_RANGE "TRECHO LIGADO! Tem certeza que deseja remover TODOS os frames indicados?"
  #define MSG_CONFIRM_REMOVE "Tem certeza que deseja remover o frame atual?"
  #define MSG_CANT_REMOVE "Esta opera" ccedil "" atilde "o n" atilde "o ser" aacute " executada. Alterne para o modo mem" oacute "ria para visualizar o(s) frame(s) a ser(em) removido(s)."
  
  #define MSG_CONFIRM_PROCESS "Tem certeza que deseja processar frames?"

  #define MSG_WRONG_DEVICE "MUAN Error: Wrong device configuration\n"
  #define MSG_CAMERA_OFF "C" acirc "mera aparentemente desligada. Aplica" ccedil "" atilde "o em modo Mem" oacute "ria."
  #define MSG_INFORM_CAPTURE_NUMBER "Informe o n" uacute "mero da captura desejada:"
  #define MSG_INVALID_FRAME_NUMBER "N" uacute "mero de frame inv" aacute "lido!"
  #define MSG_INVALID_RANGE "Intervalo inv" aacute "lido! Defina novamente."
  #define LBL_CAMERA "C" Acirc "MERA"
  #define LBL_SAVING "...SALVANDO..."

  #define LBL_MN_SYSTEM "&Sistema"
  #define LBL_MN_FILE "&Arquivo"
  #define LBL_MN_VIEW "&Exibir"
  #define LBL_MN_TOOLBARS "&Barras de Ferramentas"
  #define LBL_MN_VIEW_TOOL "&Principal"
  #define LBL_MN_VIEW_IMGTOOL "&Navegacao"
  #define LBL_MN_VIEW_IMAGE "Janela de &Captura"
  #define LBL_MN_VIEW_INFO "Janela de &Informacoes"
  #define LBL_MN_ANIMATION "A&nimacao"
  #define LBL_MN_HELP "A&juda"

  #define LBL_UNTITLED "Novo"

  #define LBL_GB_IMAGE_SIZE "Tamanho da imagem"

  #define MESSAGE_CHOICE "A conex" atilde "o com a c" acirc "mera mudou: : o MUAN vai salvar as Prefer" ecirc "ncias e sair."
  #define MESSAGE_CHOICE_ALL "O MUAN vai salvar as Prefer" ecirc "ncias e sair."

  #define MESSAGE_SAVE_AS_RESOLUTION "Salvar com a resolu" ccedil "" atilde "o"
  #define LBL_SAVE_AS_RESOLUTION "Atual"

#endif

#endif
#endif
