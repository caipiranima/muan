# MUAN Reloaded

cmake_minimum_required(VERSION 2.6)

project(muan CXX C)

set(VERSION 12)

#set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_BUILD_TYPE "Release")

#Define default language and version
if( DEFINED DEFAULT_LANG )
   if( DEFAULT_LANG STREQUAL "pt" )
       add_definitions(-DLANG_PT)
       message("Building Portuguese version")
   elseif( DEFAULT_LANG STREQUAL "sp" )
       add_definitions(-DLANG_SP)
       message("Building Spanish version")
   else()
       add_definitions(-DLANG_EN)
       set( DEFAULT_LANG "en")
       message("Building English version")
   endif()
else( DEFINED DEFAULT_LANG )
   add_definitions(-DLANG_EN)
   set( DEFAULT_LANG "en")
endif( DEFINED DEFAULT_LANG )


if(APPLE)
    add_definitions(-DMUAN_MANUAL_PATH="/Applications/muan/share/manual/")
elseif(WIN32)
	# Defined in the CPACK session
else()
	#add_definitions(-DMUAN_MANUAL_PATH="/usr/local/share/muan/manual/")
    add_definitions(-DMUAN_MANUAL_PATH="/usr/share/muan/manual/")
endif()

if(APPLE)
	set (CMAKE_OSX_ARCHITECTURES  "i386")
	set(CMAKE_OSX_SYSROOT "/Developer/SDKs/MacOSX10.6.sdk")
endif(APPLE)

set(BUILD_SHARED_LIBS false)
set(DATA_DIR ${PROJECT_SOURCE_DIR}/data)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/extra/cmake-modules" ${CMAKE_MODULE_PATH})

find_package(OpenGL REQUIRED)

if(APPLE)
	# find_package(FLTK REQUIRED)
	set(FLTK_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src/ext/fltk)
	set(FLTK_BASE_LIBRARY ${PROJECT_SOURCE_DIR}/src/ext/fltk/macos/lib/libfltk.a)
	set(FLTK_GL_LIBRARY ${PROJECT_SOURCE_DIR}/src/ext/fltk/macos/lib/libfltk_gl.a)
	set(FLTK_FORMS_LIBRARY ${PROJECT_SOURCE_DIR}/src/ext/fltk/macos/lib/libfltk_forms.a)
	set(FLTK_IMAGES_LIBRARY ${PROJECT_SOURCE_DIR}/src/ext/fltk/macos/lib/libfltk_images.a) 
	set(FLTK_Z_LIBRARY ${PROJECT_SOURCE_DIR}/src/ext/fltk/macos/lib/libfltk_z.a)	
	set(FLTK_FLUID_EXECUTABLE ${PROJECT_SOURCE_DIR}/src/ext/fltk/macos/fluid/fluid)
	set(FLTK_LIBRARIES ${FLTK_BASE_LIBRARY} ${FLTK_GL_LIBRARY}
		${FLTK_FORMS_LIBRARY} ${FLTK_FORMS_LIBRARY} ${FLTK_Z_LIBRARY} )
	
	include_directories(/opt/local/include)

	set(MY_FFMPEG_LIBRARIES
		${PROJECT_SOURCE_DIR}/src/ext/ffmpeg/macos/libavcodec.a
		${PROJECT_SOURCE_DIR}/src/ext/ffmpeg/macos/libavdevice.a
		${PROJECT_SOURCE_DIR}/src/ext/ffmpeg/macos/libavformat.a
		${PROJECT_SOURCE_DIR}/src/ext/ffmpeg/macos/libavutil.a
		${PROJECT_SOURCE_DIR}/src/ext/ffmpeg/macos/libbz2.a 
        )
	set(MY_FFMPEG_LIBSWSCALE_LIBRARIES
		${PROJECT_SOURCE_DIR}/src/ext/ffmpeg/macos/libswscale.a
        )

	include_directories(${PROJECT_SOURCE_DIR}/src/ext/sfml/include)
    set(MY_SFML_LIBRARIES
        ${PROJECT_SOURCE_DIR}/src/ext/sfml/macos/lib/libsfml-audio-s.a 
        ${PROJECT_SOURCE_DIR}/src/ext/sfml/macos/extlibs/libsndfile.a 
        ${PROJECT_SOURCE_DIR}/src/ext/sfml/macos/extlibs/libFLAC.a 
        ${PROJECT_SOURCE_DIR}/src/ext/sfml/macos/extlibs/libogg.a 
        ${PROJECT_SOURCE_DIR}/src/ext/sfml/macos/extlibs/libvorbis.a 
        ${PROJECT_SOURCE_DIR}/src/ext/sfml/macos/extlibs/libvorbisenc.a 
        ) 
	include_directories(${PROJECT_SOURCE_DIR}/src/ext/lua/include)
	set(LUA_LIBRARIES ${PROJECT_SOURCE_DIR}/src/ext/lua/macos/lib/liblua.a)
elseif(WIN32)
	#
    set(FLTK_DIR ${PROJECT_SOURCE_DIR}/src/ext/fltk/win32)
	set(FLTK_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src/ext/fltk/win32/include)
	set(FLTK_BASE_LIBRARY${PROJECT_SOURCE_DIR}/src/ext/fltk/win32/lib/fltk.lib)
	set(FLTK_GL_LIBRARY ${PROJECT_SOURCE_DIR}/src/ext/fltk/win32/lib/fltk_gl.lib)
	set(FLTK_FORMS_LIBRARY ${PROJECT_SOURCE_DIR}/src/ext/fltk/win32/lib/fltk_forms.lib)
	set(FLTK_IMAGES_LIBRARY ${PROJECT_SOURCE_DIR}/src/ext/fltk/win32/lib/fltk_images.lib) 
	set(FLTK_Z_LIBRARY ${PROJECT_SOURCE_DIR}/src/ext/fltk/win32/lib/fltk_zlib.lib)	
    set(FLTK_FLUID_EXECUTABLE ${PROJECT_SOURCE_DIR}/src/ext/fltk/win32/bin/fluid.exe)
    find_package(FLTK REQUIRED)

	set(FFMPEG_ROOT ${PROJECT_SOURCE_DIR}/src/ext/ffmpeg/win32)
	include_directories(${FFMPEG_ROOT}/include)
	message(" ffmpeg ${FFMPEG_ROOT} ")
	set(MY_FFMPEG_LIBRARIES
		${FFMPEG_ROOT}/lib/avcodec-52.lib
		${FFMPEG_ROOT}/lib/avdevice-52.lib
		${FFMPEG_ROOT}/lib/avformat-52.lib
		${FFMPEG_ROOT}/lib/avutil-49.lib 
 		)
	set(MY_FFMPEG_LIBSWSCALE_LIBRARIES
		${FFMPEG_ROOT}/lib/swscale-0.lib
		)
        set(DSVL_LIBRARY  ${PROJECT_SOURCE_DIR}/src/ext/dslib/win32/dsvl.lib)
	include_directories(${PROJECT_SOURCE_DIR}/src/ext/dslib)
	set(PORTVIDEO_LIBRARIES ${DSVL_LIBRARY})
	include_directories(${PROJECT_SOURCE_DIR}/src/ext/sfml/include)
	set(MY_SFML_LIBRARIES		
		${PROJECT_SOURCE_DIR}/src/ext/sfml/win32/lib/sfml-audio.lib
		${PROJECT_SOURCE_DIR}/src/ext/sfml/win32/extlibs/libs-vc2005/OpenAL32.lib
		${PROJECT_SOURCE_DIR}/src/ext/sfml/win32/extlibs/libs-vc2005/sndfile.lib
		)
       include_directories(${PROJECT_SOURCE_DIR}/src/ext/lua/include)
        set(LUA_LIBRARIES
            ${PROJECT_SOURCE_DIR}/src/ext/lua/win32/lib/lua.lib)
else()
	set(ARCH "i386")
	if(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "x86_64")
		set(ARCH "amd64")
	endif()

	set(FLTK_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src/ext/fltk)
	set(FLTK_BASE_LIBRARY ${PROJECT_SOURCE_DIR}/src/ext/fltk/linux/${ARCH}/lib/libfltk.a)
	set(FLTK_GL_LIBRARY ${PROJECT_SOURCE_DIR}/src/ext/fltk/linux/${ARCH}/lib/libfltk_gl.a)
	set(FLTK_FORMS_LIBRARY ${PROJECT_SOURCE_DIR}/src/ext/fltk/linux/${ARCH}/lib/libfltk_forms.a)
	set(FLTK_IMAGES_LIBRARY ${PROJECT_SOURCE_DIR}/src/ext/fltk/linux/${ARCH}/lib/libfltk_images.a) 
	set(FLTK_Z_LIBRARY ${PROJECT_SOURCE_DIR}/src/ext/fltk/linux/${ARCH}/lib/libfltk_z.a)	
	set(FLTK_FLUID_EXECUTABLE ${PROJECT_SOURCE_DIR}/src/ext/fltk/linux/${ARCH}/fluid/fluid)
	set(FLTK_LIBRARIES ${FLTK_BASE_LIBRARY} ${FLTK_GL_LIBRARY}
		${FLTK_FORMS_LIBRARY} ${FLTK_FORMS_LIBRARY} ${FLTK_Z_LIBRARY} )
	
	find_package(FLTK REQUIRED)
	#find_package(FFMPEG  REQUIRED)
	set(MY_FFMPEG_LIBRARIES
		${PROJECT_SOURCE_DIR}/src/ext/ffmpeg/linux/${ARCH}/libavcodec.a
		${PROJECT_SOURCE_DIR}/src/ext/ffmpeg/linux/${ARCH}/libavdevice.a
		${PROJECT_SOURCE_DIR}/src/ext/ffmpeg/linux/${ARCH}/libavformat.a
		${PROJECT_SOURCE_DIR}/src/ext/ffmpeg/linux/${ARCH}/libavutil.a
		${PROJECT_SOURCE_DIR}/src/ext/ffmpeg/linux/${ARCH}/libbz2.a 
		${PROJECT_SOURCE_DIR}/src/ext/ffmpeg/linux/${ARCH}/libavfilter.a 
        )
	set(MY_FFMPEG_LIBSWSCALE_LIBRARIES
		${PROJECT_SOURCE_DIR}/src/ext/ffmpeg/linux/${ARCH}/libswscale.a
        )

	include_directories(${PROJECT_SOURCE_DIR}/src/ext/sfml/include)
	set(MY_SFML_LIBRARIES
		${PROJECT_SOURCE_DIR}/src/ext/sfml/linux/lib/${ARCH}/libsfml-audio-s.a 
                -lsndfile
		)
       include_directories(${PROJECT_SOURCE_DIR}/src/ext/lua/include)
        set(LUA_LIBRARIES
			${PROJECT_SOURCE_DIR}/src/ext/lua/linux/lib/${ARCH}/liblua.a)

        find_package(PkgConfig REQUIRED)
        pkg_check_modules(GST REQUIRED gstreamer-0.10)
        pkg_check_modules(GST_APP gstreamer-app-0.10)

        pkg_check_modules(MPEG2 REQUIRED libmpeg2)
        pkg_check_modules(MPEG2CONVERT REQUIRED libmpeg2convert)
        #find_package(MPEG2 REQUIRED)
endif()

if(APPLE OR UNIX)
   find_package(DC1394)
   if(NOT DC1394_FOUND)
	message("not found libdc1394 ${DC1394_LIBRARY}")
  endif()
  if(APPLE)
        set(DC1394_LIBRARY  ${PROJECT_SOURCE_DIR}/src/ext/dc1394/macosx/libdc1394.a  ${PROJECT_SOURCE_DIR}/src/ext/dc1394/macosx/libusb-1.0.a)
  else()
        set(DC1394_LIBRARY ${PROJECT_SOURCE_DIR}/src/ext/dc1394/linux/libdc1394.a)
		#set(MY_FFMPEG_LIBRARIES -lavcodec -lavformat -lavutil -lswscale)
		#set(MY_FFMPEG_LIBRARIES)
  endif()
  set(PORTVIDEO_LIBRARIES ${DC1394_LIBRARY})
 endif()

set(CPACK_PACKAGE_NAME "muan-${DEFAULT_LANG}")
set(CPACK_PACKAGE_VENDOR "VISGRAF/IMPA")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Stop-Motion Application")
set(CPACK_PACKAGE_VERSION "12.0.5")
set(CPACK_PACKAGE_VERSION_MAJOR "12")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "5")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "muan12")
set(CPACK_COMPONENTS_ALL applications files)

add_definitions(-DMUAN_VERSION="v${CPACK_PACKAGE_VERSION}")

if(APPLE)
   set(CPACK_GENERATOR "DragNDrop")
elseif(WIN32)
   set(CPACK_GENERATOR "NSIS")
   #set(CPACK_PACKAGE_EXECUTABLES "muan_ae" "muan_ae" "muan_os" "muan_os" "muan_pl" "muan_pl")
   set(CPACK_PACKAGE_EXECUTABLES "muan_ae" "muan_ae" "muan_pl" "muan_pl")
   set(CPACK_NSIS_INSTALL_ROOT "C:\\\\muan\\\\")
   set(CPACK_CREATE_DESKTOP_LINKS "muan_ae")
   set(CPACK_NSIS_MODIFY_PATH "ON")
   
   set(MUAN_ROOT_DIR "${CPACK_NSIS_INSTALL_ROOT}${CPACK_PACKAGE_INSTALL_DIRECTORY}\\\\")
   add_definitions(-DMUAN_ROOT_DIR="${MUAN_ROOT_DIR}")
   add_definitions(-DMUAN_MANUAL_PATH="${MUAN_ROOT_DIR}\\\\manual\\\\")
else()
   set(CPACK_GENERATOR "DEB")
   set(CPACK_DEBIAN_PACKAGE_DEPENDS "libdc1394-22 (>= 2.1.2-2), libsamplerate0 (>= 0.1.7-3), libdv4 (>= 1.0.0-2ubuntu2), libavc1394-0 (>= 0.5.3-1build4), libiec61883-0 (>= 1.2.0-0.1build1),libv4l-0 (>= 0.6.4-1ubuntu1)")
   set( CPACK_DEBIAN_PACKAGE_MAINTAINER "VISGRAF Lab <visgraflab@impa.br>" )
   set( CPACK_DEBIAN_PACKAGE_SECTION "Video" )
   set( CPACK_DEBIAN_PACKAGE_VERSION ${CPACK_PACKAGE_VERSION}-0ubuntu1 )
   set( CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "${PROJECT_SOURCE_DIR}/pack/debian/preinst;${PROJECT_SOURCE_DIR}/pack/debian/postinst;${PROJECT_SOURCE_DIR}/pack/debian/prerm;" )
   set( CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}_${CPACK_DEBIAN_PACKAGE_VERSION}_${ARCH}" )
   #execute_process( COMMAND dpkg --print-architecture OUTPUT_VARIABLE CPACK_DEBIAN_PACKAGE_ARCHITECTURE )
endif()

include(CPack)
add_subdirectory(src)

