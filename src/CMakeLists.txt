
set(LIBJPEG_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src/ext/libjpeg)  
set(TINYXML_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src/ext/tinyxml) 
set(PORTVIDEO_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src/std/portvideo/include) 
set(COMMON_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src/base/common) 
set(IMAGE_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src/base/image) 
set(IMGLIST_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src/base/imglist)
set(VIDEO_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src/base/video)
set(FILTER_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src/base/filter)
set(JPEG_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src/std/jpeg)
set(FFMPEG_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src/std/ffmpeg)
set(FFMPEGLIB_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src/ext/ffmpeg/src)


if(WIN32)
set(WIN32MISC_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src/ext/win32/misc)
set(WIN32TYPES_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src/ext/win32/msinttypes)
endif(WIN32)

include_directories( ${PROJECT_SOURCE_DIR}/src/include /opt/local/include )
include_directories( ${COMMON_INCLUDE_DIR}  ${FFMPEGLIB_INCLUDE_DIR} )

add_subdirectory(ext)  
add_subdirectory(std)  
add_subdirectory(base)
add_subdirectory(proj)

