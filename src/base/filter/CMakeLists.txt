include_directories(${VIDEO_INCLUDE_DIR})
include_directories(${IMAGE_INCLUDE_DIR} ${IMGLIST_INCLUDE_DIR})

add_library( filter STATIC  filter.cpp filter.h luaplug.cpp luaplug.h plugin.cpp plugin.h builtins.cpp builtins.h)
