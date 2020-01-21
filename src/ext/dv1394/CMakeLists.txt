CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

if(WIN32)
#
elseif(UNIX)
        SET(CMAKE_CXX_FLAGS "-DHAVE_CONFIG_H -I ${CMAKE_CURRENT_SOURCE_DIR} -D_REENTRANT -D_FILE_OFFSET_BITS=64 -g -O2 -MD -MP -MF")
        #ADD_LIBRARY(dvcapture STATIC avi.cc error.cc  filehandler.cc  frame.cc  dvframe.cc hdvframe.cc ieee1394io.cc  riff.cc)
        ADD_LIBRARY(dvcapture STATIC avi.cc  filehandler.cc  hdvframe.cc  iec13818-2.cc   smiltime.cc  stringutils.cc
dvframe.cc  error.cc frame.cc  iec13818-1.cc  ieee1394io.cc  riff.cc  srt.cc v4l2reader.cc raw1394util.c)
        TARGET_LINK_LIBRARIES(dvcapture -lraw1394 -lavc1394 -lrom1394 -lraw1394 -liec61883 -lraw1394 -ldv -lm  -ljpeg -lpthread)
else()
#
endif()
