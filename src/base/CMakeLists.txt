include_directories( ${PORTVIDEO_INCLUDE_DIR} ${TINYXML_INCLUDE_DIR})
include_directories(${LIBJPEG_INCLUDE_DIR} )

add_subdirectory(image)  
add_subdirectory(imglist)  
add_subdirectory(video)
add_subdirectory(filter)
add_subdirectory(common)


