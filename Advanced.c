#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "Advanced.h"
#include "Constants.h"

/* Crop */
Image *Crop(Image *image, int x, int y, int W, int H){
    assert(image != NULL);

    int i, j;
    if (x + W > ImageWidth(image)) {
        W = ImageWidth(image) - x;
    }
    if (y + H > ImageHeight(image)) {
        H = ImageHeight(image) - y;
    }

    Image *newimg = CreateImage(W,H);

    for(i = 0; i < W; i++){
        for(j = 0; j < H; j++){
            SetPixelR(newimg, i, j, GetPixelR(image, x + i, y + j));
            SetPixelG(newimg, i, j, GetPixelG(image, x + i, y + j));
            SetPixelB(newimg, i, j, GetPixelB(image, x + i, y + j));
        }
    }
    DeleteImage(image);
    return newimg;
}

/* Resize */
Image *Resize(Image *image, int newWidth, int newHeight){
    assert(image != NULL);
    float ScaleX, ScaleY;
    ScaleX = (float)newWidth/ImageWidth(image);
    ScaleY = (float)newHeight/ImageHeight(image);

    Image *newimg = CreateImage(newWidth, newHeight);
    for(int i = 0; i < newWidth; i++){
        for(int j = 0; j < newHeight; j++){
            SetPixelR(newimg, i, j, GetPixelR(image, (int)(i/ScaleX), (int)(j/ScaleY)));
            SetPixelG(newimg, i, j, GetPixelG(image, (int)(i/ScaleX), (int)(j/ScaleY)));
            SetPixelB(newimg, i, j, GetPixelB(image, (int)(i/ScaleX), (int)(j/ScaleY)));
        }
    }
    DeleteImage(image);
    return newimg;
}

/* Watermark */
Image *Watermark(Image *image, const Image *watermark_image){
    assert(image != NULL);
    int wR, wG, wB;
    float waterFactor = 1.45;
    
    for(int i = 0; i < ImageWidth(image); i++){
        for(int j = 0; j < ImageHeight(image); j++){
            wR = GetPixelR(image, i, j);
            wG = GetPixelG(image, i, j);
            wB = GetPixelB(image, i, j);
            if(GetPixelR(watermark_image, i % ImageWidth(watermark_image), j % ImageHeight(watermark_image)) == 0 && 
               GetPixelG(watermark_image, i % ImageWidth(watermark_image), j % ImageHeight(watermark_image)) == 0 && 
               GetPixelB(watermark_image, i % ImageWidth(watermark_image), j % ImageHeight(watermark_image)) == 0){
                if((wR = (int) wR * waterFactor) > 255){
                    wR = 255;
                }
                SetPixelR(image, i, j, wR);
                if((wG = (int) wG * waterFactor) > 255){
                    wG = 255;
                }
                SetPixelG(image, i, j, wG);
                if((wB = (int) wB * waterFactor) > 255){
                    wB = 255;
                }
                SetPixelB(image, i, j, wB);
            }
        }
    }
    return image;
}

/* Shift */
Image *Shift(Image *image, int shiftX, int shiftY){
    assert(image != NULL);
    Image *newimg = CreateImage(ImageWidth(image), ImageHeight(image));
    //shift x
    for(int j = 0; j < ImageHeight(image); j++){
        for(int i = 0; i + shiftX < ImageWidth(image); i++){
            SetPixelR(newimg, i + shiftX, j, GetPixelR(image, i, j));
            SetPixelG(newimg, i + shiftX, j, GetPixelG(image, i, j));
            SetPixelB(newimg, i + shiftX, j, GetPixelB(image, i, j));
        }
        for(int i = 0; i < shiftX; i++){
            SetPixelR(newimg, i, j, GetPixelR(image, ImageWidth(image) - shiftX + i, j));
            SetPixelG(newimg, i, j, GetPixelG(image, ImageWidth(image) - shiftX + i, j));
            SetPixelB(newimg, i, j, GetPixelB(image, ImageWidth(image) - shiftX + i, j));
        }
    }

    //shift y
    for(int i = 0; i < ImageWidth(image); i++){
        for(int j = 0; j + shiftY < ImageHeight(image); j++){
            SetPixelR(image, i, j + shiftY, GetPixelR(newimg, i, j));
            SetPixelG(image, i, j + shiftY, GetPixelG(newimg, i, j));
            SetPixelB(image, i, j + shiftY, GetPixelB(newimg, i, j));
        }
        for(int j = 0; j < shiftY; j++){
            SetPixelR(image, i, j, GetPixelR(newimg, i, ImageHeight(newimg) - shiftY + j));
            SetPixelG(image, i, j, GetPixelG(newimg, i, ImageHeight(newimg) - shiftY + j));
            SetPixelB(image, i, j, GetPixelB(newimg, i, ImageHeight(newimg) - shiftY + j));
        }
    }
    DeleteImage(newimg);
    return image;
}

/* Rotate by 90 */
Image *RotateBy90(Image *image, int rotateDirection){
    assert(image != NULL);
    Image *newimg = CreateImage(ImageHeight(image), ImageWidth(image));

    if(rotateDirection == 1){
        for(int i = 0; i < ImageHeight(image); i++){
            for(int j = 0; j < ImageWidth(image); j++){
                SetPixelR(newimg, i, j, GetPixelR(image, ImageWidth(image) - 1 - j, i));
                SetPixelG(newimg, i, j, GetPixelG(image, ImageWidth(image) - 1 - j, i));
                SetPixelB(newimg, i, j, GetPixelB(image, ImageWidth(image) - 1 - j, i));
            }
        }
    } else if(rotateDirection == 0){
        for(int i = 0; i < ImageHeight(image); i++){
            for(int j = 0; j < ImageWidth(image); j++){
                SetPixelR(newimg, i, j, GetPixelR(image, j, ImageHeight(image) - 1 - i));
                SetPixelG(newimg, i, j, GetPixelG(image, j, ImageHeight(image) - 1 - i));
                SetPixelB(newimg, i, j, GetPixelB(image, j, ImageHeight(image) - 1 - i));
            }
        }
    }
    DeleteImage(image);
    return newimg;
}