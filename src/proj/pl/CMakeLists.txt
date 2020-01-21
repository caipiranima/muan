include_directories(.)

fltk_wrap_ui(muan_pl ui_player.fl)

add_executable(muan_pl ${EXEC_TYPE}  main_player.cpp ${common_sources} ${muan_pl_FLTK_UI_SRCS} )


if(APPLE)
target_link_libraries(muan_pl common video filter image imglist jpg ffmpeg portvideo
                   tinyxml libjpeg
                   ${PORTVIDEO_LIBRARIES}
                   ${FLTK_LIBRARIES} ${OPENGL_LIBRARIES}
                   ${EXTRA_LIBS} 
                   ${MY_FFMPEG_LIBRARIES}
                   ${MY_FFMPEG_LIBSWSCALE_LIBRARIES}
				   ${DC1394_LIBRARY} ${LUA_LIBRARIES} )
elseif(UNIX)

target_link_libraries(muan_pl common video filter image imglist jpg ffmpeg portvideo 
                              dc1394 v4lconvert raw1394 iec61883 dv rom1394 dvcapture avc1394
			      tinyxml libjpeg
                              ${MPEG2_LIBRARIES} ${MPEG2CONVERT_LIBRARIES}
 			      ${PORTVIDEO_LIBRARIES}
 			      ${FLTK_LIBRARIES} ${OPENGL_LIBRARIES}
 			      ${EXTRA_LIBS} 
 			      ${MY_FFMPEG_LIBRARIES}
 			      ${MY_FFMPEG_LIBSWSCALE_LIBRARIES} 
                                  ${MY_SFML_LIBRARIES}  ${GST_LIBRARIES} ${GST_APP_LIBRARIES} ${LUA_LIBRARIES} )

elseif(WIN32)

	target_link_libraries(muan_pl common image imglist video filter jpg ffmpeg portvideo
			      tinyxml libjpeg
 			      ${PORTVIDEO_LIBRARIES}
 			      ${FLTK_LIBRARIES} ${OPENGL_LIBRARIES}
 			      ${EXTRA_LIBS} 
 			      ${MY_FFMPEG_LIBRARIES}
 			      ${MY_FFMPEG_LIBSWSCALE_LIBRARIES}
                                  ${MY_SFML_LIBRARIES}  ${LUA_LIBRARIES} )

endif()


if(APPLE)
	install(TARGETS muan_pl BUNDLE  DESTINATION muan  COMPONENT
	applications) 
elseif(WIN32)
	install(TARGETS muan_pl RUNTIME  DESTINATION bin  COMPONENT applications) 
else()
	install(TARGETS muan_pl RUNTIME  DESTINATION bin  COMPONENT applications) 
endif()
