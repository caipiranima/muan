
fltk_wrap_ui(muan_os ui.fl)

add_executable(muan_os ${EXEC_TYPE} main.cpp ${common_sources} ${muan_os_FLTK_UI_SRCS} )


if(APPLE)
target_link_libraries(muan_os common image imglist video jpg ffmpeg portvideo
                   tinyxml libjpeg
                   ${PORTVIDEO_LIBRARIES}
                   ${FLTK_LIBRARIES} ${OPENGL_LIBRARIES}
                   ${EXTRA_LIBS} 
                   ${MY_FFMPEG_LIBRARIES}
                   ${MY_FFMPEG_LIBSWSCALE_LIBRARIES}
	           ${DC1394_LIBRARY}
		   ${MY_SFML_LIBRARIES}  )
elseif(UNIX)

	target_link_libraries(muan_os common image imglist video jpg ffmpeg portvideo dc1394 v4lconvert raw1394 iec61883 dv rom1394 dvcapture avc1394
			      tinyxml libjpeg
 			      ${PORTVIDEO_LIBRARIES}
 			      ${FLTK_LIBRARIES} ${OPENGL_LIBRARIES}
 			      ${EXTRA_LIBS} 
 			      ${MY_FFMPEG_LIBRARIES}
 			      ${MY_FFMPEG_LIBSWSCALE_LIBRARIES} 
				  ${MY_SFML_LIBRARIES} )
elseif(WIN32)

	target_link_libraries(muan_os common image imglist video jpg ffmpeg portvideo
			      tinyxml libjpeg
 			      ${PORTVIDEO_LIBRARIES}
 			      ${FLTK_LIBRARIES} ${OPENGL_LIBRARIES}
 			      ${EXTRA_LIBS} 
 			      ${MY_FFMPEG_LIBRARIES}
 			      ${MY_FFMPEG_LIBSWSCALE_LIBRARIES}
				  ${MY_SFML_LIBRARIES} )

endif()

if(APPLE)
	install(TARGETS muan_os BUNDLE  DESTINATION muan  COMPONENT
	applications) 
elseif(WIN32)
	install(TARGETS muan_os RUNTIME  DESTINATION bin  COMPONENT applications) 
else()
	install(TARGETS muan_os RUNTIME  DESTINATION bin  COMPONENT applications) 
endif()



