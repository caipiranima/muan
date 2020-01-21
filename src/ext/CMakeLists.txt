add_subdirectory(tinyxml)
add_subdirectory(libjpeg)

if (APPLE OR WIN32)
#
elseif(UNIX)
  add_subdirectory(dv1394)
endif()
