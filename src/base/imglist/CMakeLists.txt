include_directories(${VIDEO_INCLUDE_DIR}  ${IMAGE_INCLUDE_DIR} ${JPEG_INCLUDE_DIR})
include_directories(${IMGLIST_INCLUDE_DIR})

add_library( imglist STATIC frame.cpp imglist.cpp imgnode.cpp frame.h imglist.h )
