include_directories( ${PROJECT_SOURCE_DIR}/src/include /opt/local/include)

add_library( ffmpeg STATIC  ffmpeg_rw.c ffmpeg_rw.h )
