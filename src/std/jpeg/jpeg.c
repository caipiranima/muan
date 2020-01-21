/**
 * This file implements methods for read and write jpeg files and was based on libjpeg example program.
 \file jpeg.c
 */
/*
 * Copyright (C) 1991-1998, Thomas G. Lane.
 * This file is part of the Independent JPEG Group's software.
 * For conditions of distribution and use, see the accompanying README file.
*/
#include "jpeg.h"

/**
 * Writes a jpeg file.
 * @param image
 * @param filename
 * @param quality
 */
//============================================================================+
void write_JPEG_file (unsigned char* image, int image_width, int image_height, char* filename, int quality)
//============================================================================+
{
  struct jpeg_compress_struct cinfo;
  struct jpeg_error_mgr jerr;

  FILE * outfile;		/* target file */
  JSAMPROW row_pointer[1];	/* pointer to JSAMPLE row[s] */
  int row_stride;		/* physical row width in image buffer */
  
  cinfo.err = jpeg_std_error(&jerr);
  
  jpeg_create_compress(&cinfo);

  if ((outfile = fopen(filename, "wb")) == NULL) {
    fprintf(stderr, "can't open %s\n", filename);
    return;
  }
  
  jpeg_stdio_dest(&cinfo, outfile);

  cinfo.image_width = image_width; 	/* image width and height, in pixels */
  cinfo.image_height = image_height;
  cinfo.input_components = 3;		/* # of color components per pixel */
  cinfo.in_color_space = JCS_RGB; 	/* colorspace of input image */

  jpeg_set_defaults(&cinfo);
  jpeg_set_quality(&cinfo, quality, TRUE /* limit to baseline-JPEG values */);

  jpeg_start_compress(&cinfo, TRUE);

  row_stride = image_width * 3;	/* JSAMPLEs per row in image_buffer */

  while (cinfo.next_scanline < cinfo.image_height) {
    row_pointer[0] = & image[cinfo.next_scanline * row_stride];
    (void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
  }
  
  jpeg_finish_compress(&cinfo);
  fclose(outfile);

  jpeg_destroy_compress(&cinfo);
}



/**
 * Reads a jpeg file.
 * @param filename
 * @return image
 */
//============================================================================+
unsigned char* read_JPEG_file (const char * filename, int image_width, int image_height)
//============================================================================+
{
  struct jpeg_decompress_struct cinfo;
  struct jpeg_error_mgr jerr;
  FILE * input_file;
  JDIMENSION num_scanlines;
  int factor, w, h;
  register char * bufferptr;
  register JSAMPROW ptr;
  register JDIMENSION col;
  char* image;
  JSAMPROW rowbuffer;

  cinfo.err = jpeg_std_error(&jerr);	
  jpeg_create_decompress(&cinfo);

  if ((input_file = fopen(filename, "rb"/*READ_BINARY*/)) == NULL) {
    fprintf(stderr, "read_JPEG_file: can't open %s\n", filename);
    return NULL;
  }

  jpeg_stdio_src(&cinfo, input_file);

  (void) jpeg_read_header(&cinfo, TRUE);

    //====   scaling image   =====================================    
    factor = 1;
    w = cinfo.image_width;
    h = cinfo.image_height;
    
    while ( ((w/factor>image_width) || (h/factor>image_height)) && (factor<8) ) {
      factor*=2;
      if (factor > 8) {
        fprintf(stderr, "read_JPEG_file: can't resize image %s.\n", filename);
        return NULL;
      }
    }
    cinfo.scale_num=1;           // mcv -> libjpeg.doc: Currently (version 6b), 
    cinfo.scale_denom=factor;    // the only supported scaling ratios are 1/1, 1/2, 1/4, and 1/8.

    //====   fim scaling image   =================================    
    
  (void) jpeg_start_decompress(&cinfo);

  image = (char*) malloc(image_width*image_height*3);
    
  rowbuffer = (JSAMPROW) malloc(cinfo.output_width*cinfo.out_color_components);

  bufferptr = image;

  if ((cinfo.output_width==image_width) && (cinfo.output_height==image_height)) {
	  while (cinfo.output_scanline < cinfo.output_height) {
      num_scanlines = jpeg_read_scanlines(&cinfo, &rowbuffer, 1);
      ptr = rowbuffer;
      for (col = (cinfo.output_width * cinfo.out_color_components); col > 0; col--) {
        PUTPPMSAMPLE(bufferptr, GETJSAMPLE(*ptr++));
      }  
    }
  }
  else
  { //mcv: adjusting jpg in center of image
    bufferptr += (((image_height-cinfo.output_height)/2)*image_width+ (image_width-cinfo.output_width)/2)*cinfo.out_color_components;
    while (cinfo.output_scanline < cinfo.output_height) {
      num_scanlines = jpeg_read_scanlines(&cinfo, &rowbuffer, 1);
      ptr = rowbuffer;
      for (col = (cinfo.output_width * cinfo.out_color_components); col > 0; col--) {
        PUTPPMSAMPLE(bufferptr, GETJSAMPLE(*ptr++));
      } 
      bufferptr += (image_width-cinfo.output_width)* cinfo.out_color_components;
    }
  }
  (void) jpeg_finish_decompress(&cinfo);

  jpeg_destroy_decompress(&cinfo);

  if (input_file != stdin)
    fclose(input_file);

  free(rowbuffer);
  
  return ((unsigned char*) image);
}
