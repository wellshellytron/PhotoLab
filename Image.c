#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Image.h"

/* Get the R intensity of pixel (x, y) in image */
unsigned char GetPixelR(const Image *image, unsigned int x, unsigned int y) {
    assert(image != NULL);
    assert(image->R != NULL);
    assert(x < image->W && y < image->H);
    return image->R[y * image->W + x];
}

/* Get the G intensity of pixel (x, y) in image */
unsigned char GetPixelG(const Image *image, unsigned int x, unsigned int y) {
    assert(image != NULL);
    assert(image->G != NULL);
    assert(x < image->W && y < image->H);
    return image->G[y * image->W + x];
}

/* Get the B intensity of pixel (x, y) in image */
unsigned char GetPixelB(const Image *image, unsigned int x, unsigned int y) {
    assert(image != NULL);
    assert(image->B != NULL);
    assert(x < image->W && y < image->H);
    return image->B[y * image->W + x];
}

/* Set the R intensity of pixel (x, y) in image to r */
void SetPixelR(Image *image, unsigned int x, unsigned int y, unsigned char r) {
    assert(image != NULL);
    assert(image->R != NULL);
    assert(x < image->W && y < image->H);
    image->R[y * image->W + x] = r;
}

/* Set the G intensity of pixel (x, y) in image to g */
void SetPixelG(Image *image, unsigned int x, unsigned int y, unsigned char g) {
    assert(image != NULL);
    assert(image->G != NULL);
    assert(x < image->W && y < image->H);
    image->G[y * image->W + x] = g;
}

/* Set the B intensity of pixel (x, y) in image to b */
void SetPixelB(Image *image, unsigned int x, unsigned int y, unsigned char b) {
    assert(image != NULL);
    assert(image->B != NULL);
    assert(x < image->W && y < image->H);
    image->B[y * image->W + x] = b;
}

/* Allocate dynamic memory for the image structure and its R/G/B values */
Image *CreateImage(unsigned int Width, unsigned int Height) {
    assert(Width > 0 && Height > 0);  // Ensure valid dimensions

    Image *image = (Image *)malloc(sizeof(Image));
    assert(image != NULL);

    image->W = Width;
    image->H = Height;
    
    image->R = (unsigned char *)malloc(Width * Height * sizeof(unsigned char));
    image->G = (unsigned char *)malloc(Width * Height * sizeof(unsigned char));
    image->B = (unsigned char *)malloc(Width * Height * sizeof(unsigned char));

    if (!(image->R && image->G && image->B)) {
        fprintf(stderr, "Error: Unable to allocate memory for image data\n");
        free(image->R);
        free(image->G);
        free(image->B);
        free(image);
        return NULL;
    }

    return image;
}

/* Free the memory for the R/G/B values and Image structure */
void DeleteImage(Image *image) {
    assert(image != NULL);
    free(image->R);
    free(image->G);
    free(image->B);
    free(image);
}

/* Return the image's width in pixels */
unsigned int ImageWidth(const Image *image) {
    assert(image != NULL);
    return image->W;
}

/* Return the image's height in pixels */
unsigned int ImageHeight(const Image *image) {
    assert(image != NULL);
    return image->H;
}
