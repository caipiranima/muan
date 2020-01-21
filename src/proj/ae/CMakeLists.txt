fltk_wrap_ui(muan_ae ui_ae.fl)

set(SHARE ${PROJECT_SOURCE_DIR}/data/)

if(APPLE)
	# set muan icon 
	set( MUAN_ICON ${CMAKE_SOURCE_DIR}/data/res/muan.icns )
    # set how it shows up in the Info.plist file
    set( MACOSX_BUNDLE_ICON_FILE muan.icns)
    # set where in the bundle to put the icns file
    set_source_files_properties( ${MUAN_ICON} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)

    # include the icns file in the target
	add_executable(muan_ae MACOSX_BUNDLE main_ae.cpp ${MUAN_ICON} ${common_sources} ${muan_ae_FLTK_UI_SRCS} )
	add_dependencies( muan_ae ${common_sources} )

	target_link_libraries(muan_ae common image imglist video filter jpg ffmpeg portvideo
                   tinyxml libjpeg
                   ${PORTVIDEO_LIBRARIES}
                   ${FLTK_LIBRARIES} ${OPENGL_LIBRARIES}
                   ${EXTRA_LIBS} 
                   ${MY_FFMPEG_LIBRARIES}
                   ${MY_FFMPEG_LIBSWSCALE_LIBRARIES}
		   ${DC1394_LIBRARY} 
                   ${MY_SFML_LIBRARIES} ${LUA_LIBRARIES} )

elseif(UNIX)
	add_executable(muan_ae ${EXEC_TYPE} main_ae.cpp ${common_sources} ${muan_ae_FLTK_UI_SRCS} )
	add_dependencies( muan_ae ${common_sources} )
    target_link_libraries(muan_ae common image imglist video filter jpg ffmpeg portvideo
                          dc1394 v4lconvert raw1394 iec61883 dv rom1394 dvcapture avc1394
                          tinyxml libjpeg
                          ${MPEG2_LIBRARIES} ${MPEG2CONVERT_LIBRARIES}
 			      ${PORTVIDEO_LIBRARIES}
 			      ${FLTK_LIBRARIES} ${OPENGL_LIBRARIES}
 			      ${EXTRA_LIBS} 
 			      ${MY_FFMPEG_LIBRARIES}
 			      ${MY_FFMPEG_LIBSWSCALE_LIBRARIES} 
                  ${MY_SFML_LIBRARIES} ${GST_LIBRARIES} ${GST_APP_LIBRARIES} ${LUA_LIBRARIES})

elseif(WIN32)
	include_directories( ${PROJECT_SOURCE_DIR} )
	add_executable(muan_ae ${EXEC_TYPE} main_ae.cpp muan_ae_win32.rc ${common_sources} ${muan_ae_FLTK_UI_SRCS} )
	add_dependencies( muan_ae ${common_sources} ) 

	target_link_libraries(muan_ae common image imglist video filter jpg ffmpeg portvideo 
			      tinyxml libjpeg
 			      ${PORTVIDEO_LIBRARIES}
 			      ${FLTK_LIBRARIES} ${OPENGL_LIBRARIES}
 			      ${EXTRA_LIBS} 
 			      ${MY_FFMPEG_LIBRARIES}
 			      ${MY_FFMPEG_LIBSWSCALE_LIBRARIES} 
                  ${MY_SFML_LIBRARIES} ${LUA_LIBRARIES} )

endif()

if(APPLE)
	install(TARGETS muan_ae BUNDLE  DESTINATION muan  COMPONENT applications) 
elseif(WIN32)
	install(TARGETS muan_ae RUNTIME  DESTINATION bin  COMPONENT applications) 
else()
	install(TARGETS muan_ae RUNTIME  DESTINATION bin  COMPONENT applications) 
endif()

