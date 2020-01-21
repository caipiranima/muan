set(PROJ_INC_DIR ${PROJECT_SOURCE_DIR}/src/proj/inc)  
set(common_sources ${PROJ_INC_DIR}/muan_ui.h ${PROJ_INC_DIR}/settings.h )

include_directories(${PROJ_INC_DIR})
include_directories(${COMMON_INCLUDE_DIR})
include_directories(${LIBJPEG_INCLUDE_DIR} )
include_directories(${PORTVIDEO_INCLUDE_DIR} ${JPEG_INCLUDE_DIR} )
include_directories(${IMAGE_INCLUDE_DIR} ${IMGLIST_INCLUDE_DIR})
include_directories(${VIDEO_INCLUDE_DIR} ${FFMPEG_INCLUDE_DIR})
include_directories(${FILTER_INCLUDE_DIR})
include_directories(${TINYXML_INCLUDE_DIR} )

include_directories(${FLTK_INCLUDE_DIR})
link_directories(${FLTK_DIR}/lib)



#if (NOT FFMPEG_FOUND)
#   message("NOT FOUND ffmpeg ${FFMPEG_LIBRARIES}")
#endif()

IF(APPLE)
   set(GUI_TYPE MACOSX_BUNDLE)
   include_directories ( /Developer/Headers/FlatCarbon )
   find_library(CARBON_LIBRARY Carbon)
   find_library(QUICKTIME_LIBRARY QuickTime )
   find_library(IOKIT_LIBRARY IOKit )
   find_library(APP_SERVICES_LIBRARY ApplicationServices )
  find_library(OPENAL_LIBRARY OpenAL ) 
   mark_as_advanced (CARBON_LIBRARY
                     QUICKTIME_LIBRARY IOKIT_LIBRARY
                     APP_SERVICES_LIBRARY)
   set( EXTRA_LIBS ${CARBON_LIBRARY} ${QUICKTIME_LIBRARY}
   		      ${IOKIT_LIBRARY}  ${APP_SERVICES_LIBRARY}  ${OPENAL_LIBRARY} )
endif (APPLE)

if(WIN32)
include_directories(${WIN32MISC_INCLUDE_DIR} ${WIN32TYPES_INCLUDE_DIR})
endif(WIN32)

if(APPLE)
	set(EXEC_TYPE "MACOSX_BUNDLE")
elseif(WIN32)
	set(EXEC_TYPE "WIN32")
else()
	set(EXEC_TYPE "")
endif()

#add_subdirectory(os) 

add_subdirectory(ae)  
add_subdirectory(pl)  
add_subdirectory(share)  
add_subdirectory(plugins)  
