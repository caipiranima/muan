#-----------------------------------------------------------------------------
#
# FLTKConfig.cmake - FLTK CMake configuration file for external projects.
#
# This file is configured by FLTK and used by the UseFLTK.cmake module
# to load FLTK's settings for an external project.

# The FLTK source tree.
SET(FLTK_SOURCE_DIR "C:/Users/Administrator/Desktop/fltk-1.1.10")

# The FLTK include file directories.
SET(FLUID_COMMAND "C:/Program Files (x86)/FLTK/bin/fluid")
SET(FLTK_EXECUTABLE_DIRS "C:/Program Files (x86)/FLTK/bin")
SET(FLTK_LIBRARY_DIRS "C:/Program Files (x86)/FLTK/lib")
SET(FLTK_LIBRARIES "fltk_images;fltk;fltk_gl;fltk_forms;fltk_zlib;fltk_jpeg;fltk_png")
SET(FLTK_INCLUDE_DIRS "C:/Program Files (x86)/FLTK/")

# The C and C++ flags added by FLTK to the cmake-configured flags.
SET(FLTK_REQUIRED_C_FLAGS "")
SET(FLTK_REQUIRED_CXX_FLAGS "")

# The FLTK version number
SET(FLTK_VERSION_MAJOR "1")
SET(FLTK_VERSION_MINOR "1")
SET(FLTK_VERSION_PATCH "10")

# Is FLTK using shared libraries?
SET(FLTK_BUILD_SHARED_LIBS "OFF")
SET(FLTK_BUILD_SETTINGS_FILE "C:/Program Files (x86)/FLTK/lib/FLTK-1.1/FLTKBuildSettings.cmake")

# The location of the UseFLTK.cmake file.
SET(FLTK11_USE_FILE "C:/Program Files (x86)/FLTK/lib/FLTK-1.1/FLTKUse.cmake")

# The ExodusII library dependencies.
IF(NOT FLTK_NO_LIBRARY_DEPENDS)
  INCLUDE("C:/Program Files (x86)/FLTK/lib/FLTK-1.1/FLTKLibraryDepends.cmake")
ENDIF(NOT FLTK_NO_LIBRARY_DEPENDS)
