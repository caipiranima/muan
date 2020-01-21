include_directories( ${LIBJPEG_INCLUDE_DIR} ${PROJECT_SOURCE_DIR}/src/include /opt/local/include)

add_library( jpg STATIC  jpeg.c jpeg.h )
