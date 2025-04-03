#ifndef DIPS_H
#define DIPS_H

#include <stdlib.h>
#include <stdio.h>
#include "Constants.h"
#include "Image.h"  // Include Image.h for the Image struct definition

/* Change color image to black & white */
Image *BlackNWhite(Image *image);

/* Convert image to negative */
Image *Negative(Image *image);

/* Apply a color filter */
Image *ColorFilter(Image *image, int target_r, int target_g, int target_b, int threshold, int replace_r, int replace_g, int replace_b);

/* Detect edges in an image */
Image *Edge(Image *image);

/* Flip image vertically */
Image *VFlip(Image *image);

/* Mirror image horizontally */
Image *HMirror(Image *image);

/* Shuffle the image */
Image *Shuffle(Image *image);

/* Border */
Image *AddBorder(Image *image, char color[SLEN], int border_width);

/* Pixelate the image */
Image *Pixelate(Image *image, int block_size);

#endif
