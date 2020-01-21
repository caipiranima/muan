include_directories(${LIBJPEG_INCLUDE_DIR} )
include_directories(${PORTVIDEO_INCLUDE_DIR} ${JPEG_INCLUDE_DIR} )
include_directories(${IMAGE_INCLUDE_DIR} ${IMGLIST_INCLUDE_DIR})
include_directories(${VIDEO_INCLUDE_DIR} ${FFMPEG_INCLUDE_DIR})
include_directories(${FILTER_INCLUDE_DIR})

include_directories(${FLTK_INCLUDE_DIR})

add_library(common STATIC defaults.h defaults.cpp imgviewer.cpp imgviewer.h lang_ui.h sndfile-play.cpp sndfile-play.h video_encoder.cpp video_encoder.h)
