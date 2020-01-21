FIND_PATH(DC1394_INCLUDE_PATH control.h
  /usr/local/include/dc1394
  /usr/include/dc1394
  /opt/local/include/dc1394
)
 
FIND_LIBRARY(DC1394_LIBRARY dc1394 /usr/local/lib /usr/lib /opt/local/lib)
 
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(DC1394 DEFAULT_MSG DC1394_INCLUDE_PATH DC1394_LIBRARY)
 