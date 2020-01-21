
include_directories( ${PORTVIDEO_INCLUDE_DIR} ${TINYXML_INCLUDE_DIR} ${IMAGE_INCLUDE_DIR} )

set(CMAKE_CXX_FLAGS="-DNDEBUG")

set(sources common/CameraEngine.cpp common/CameraTool.cpp
	    common/FileCamera.cpp common/RingBuffer.cpp)

if(APPLE)
	set(sources ${sources}  macosx/MacVdigCamera.cpp macosx/VdigGrab.c)
elseif(UNIX)

        string(REPLACE "-I" " -I" GST_CFLAGS ${GST_CFLAGS})
        #string(REPLACE "-l" " -l" GST_LDFLAGS ${GST_LDFLAGS})

	include_directories( ${PROJECT_SOURCE_DIR}/src/std/portvideo/linux)
	include_directories( ${PROJECT_SOURCE_DIR}/src/ext)
	include_directories( ${PROJECT_SOURCE_DIR}/src/ext/dv1394)

        set(sources ${sources} linux/DC1394Camera.cpp linux/V4Linux2Camera.cpp linux/DV1394Camera.cpp linux/GStreamerCamera.cpp)

        set_property(SOURCE "linux/GStreamerCamera.cpp" APPEND PROPERTY COMPILE_FLAGS ${GST_CFLAGS})
        set_property(SOURCE "common/CameraTool.cpp" APPEND PROPERTY COMPILE_FLAGS ${GST_CFLAGS})

        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DLINUX -DHAVE_CONFIG_H -Wall -O3 -finline-functions -ffast-math -funroll-all-loops -fomit-frame-pointer")

elseif(WIN32)
	set(sources ${sources} win32/DSlibCamera.cpp)
endif()

add_library( portvideo STATIC  ${sources} )
