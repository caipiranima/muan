include_directories(${VIDEO_INCLUDE_DIR})
include_directories(${IMAGE_INCLUDE_DIR} ${IMGLIST_INCLUDE_DIR})

add_library( video STATIC  video.cpp video.h )
