/*
* frame.h -- utilities for process digital video frames
*/
#ifndef _FRAME_H
#define _FRAME_H 1

#include <iostream>
using std::cerr;
using std::endl;

#include <time.h>
#include <string>
#include <stdio.h>
using std::string;

extern "C" {
#include "image.h"
}

namespace muan {
class Frame
{
private:
  Image *img;
public:
  Frame(int width, int height);
  Frame(const Frame &that);
  Frame *operator=(const Frame &that);
  ~Frame();
  int ExtractRGB( void *rgb );
  int StoreRGB( void *rgb );
  int GetWidth();
  int GetHeight();
  unsigned char * GetData();
  Image *GetImage();
};
}

using namespace muan;

#endif
