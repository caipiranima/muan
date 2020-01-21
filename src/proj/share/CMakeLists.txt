
if(APPLE)
        install(FILES muan_conf.xml release-notes.txt DESTINATION muan/share COMPONENT files)
        install(DIRECTORY ${PROJECT_SOURCE_DIR}/data/manual DESTINATION muan/share COMPONENT files)
elseif(WIN32)
	set(FFMPEG_DLL_DIR ${PROJECT_SOURCE_DIR}/src/ext/ffmpeg/win32/bin)
	set(MSVC10_DLL_DIR ${PROJECT_SOURCE_DIR}/src/ext/win32/vc10)
	set(DSVL_DLL_DIR ${PROJECT_SOURCE_DIR}/src/ext/dslib/win32)
	set(SFML_DLL_DIR ${PROJECT_SOURCE_DIR}/src/ext/sfml/win32/lib)
	set(SFML_EXT_DLL_DIR ${PROJECT_SOURCE_DIR}/src/ext/sfml/win32/extlibs/bin)		
        install(FILES 
			muan_conf.xml release-notes.txt 
			${DSVL_DLL_DIR}/DSVL.dll ${MSVC10_DLL_DIR}/msvcp100.dll  ${MSVC10_DLL_DIR}/msvcr100.dll 
			${FFMPEG_DLL_DIR}/avcodec-52.dll ${FFMPEG_DLL_DIR}/avdevice-52.dll ${FFMPEG_DLL_DIR}/avformat-52.dll ${FFMPEG_DLL_DIR}/avutil-49.dll ${FFMPEG_DLL_DIR}/swscale-0.dll 
			${SFML_DLL_DIR}/sfml-audio.dll ${SFML_DLL_DIR}/sfml-system.dll ${SFML_EXT_DLL_DIR}/openal32.dll ${SFML_EXT_DLL_DIR}/libsndfile-1.dll 
			DESTINATION bin 
			COMPONENT files)
        install(DIRECTORY ${PROJECT_SOURCE_DIR}/data/manual DESTINATION . COMPONENT files)
else()
    install(FILES muan_conf.xml release-notes.txt muan_icon.png DESTINATION share/muan COMPONENT files)
    install(FILES muan.desktop DESTINATION share/applications COMPONENT files)
    install(FILES muan.directory DESTINATION share/desktop-directories COMPONENT files)
    install(DIRECTORY ${PROJECT_SOURCE_DIR}/data/manual DESTINATION share/muan COMPONENT files)
endif()


