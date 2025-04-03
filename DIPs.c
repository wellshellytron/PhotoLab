#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "DIPs.h"
#include "Constants.h"



/* reverse image color */
Image *Negative(Image *image){
	assert(image != NULL);
	int x, y;
	for (y = 0; y < ImageHeight(image); y++) {
		for (x = 0; x < ImageWidth(image); x++) {
			SetPixelR(image, x, y, MAX_PIXEL - GetPixelR(image, x,y));
			SetPixelG(image, x, y, MAX_PIXEL - GetPixelG(image, x,y));
			SetPixelB(image, x, y, MAX_PIXEL - GetPixelB(image, x,y));
		}
	}
	return image;
}

/* color filter */
Image *ColorFilter(Image *image, int target_r, int target_g, int target_b, int threshold, int replace_r, int replace_g, int replace_b){
	assert(image != NULL);
	int x, y;

	replace_r = (replace_r > MAX_PIXEL) ? MAX_PIXEL : (replace_r < 0) ? 0 : replace_r;
	replace_g = (replace_g > MAX_PIXEL) ? MAX_PIXEL : (replace_g < 0) ? 0 : replace_g;
	replace_b = (replace_b > MAX_PIXEL) ? MAX_PIXEL : (replace_b < 0) ? 0 : replace_b;

	for (y = 0; y < ImageHeight(image); y++){
		for (x = 0; x < ImageWidth(image); x++){
			if (abs(GetPixelR(image, x,y) - target_r) <= threshold
					&& abs(GetPixelG(image, x,y) - target_g) <= threshold
					&& abs(GetPixelB(image, x,y) - target_b) <= threshold) {
				SetPixelR(image, x, y, replace_r);
				SetPixelG(image, x, y, replace_g);
				SetPixelB(image, x, y, replace_b);
			}
		}
	}
	return image;
}

/* edge detection */
Image *Edge(Image *image) {
	assert(image != NULL);
	int             x, y, m, n, a, b;
	unsigned char   tmpR[ImageWidth(image)][ImageHeight(image)];
	unsigned char   tmpG[ImageWidth(image)][ImageHeight(image)];
	unsigned char   tmpB[ImageWidth(image)][ImageHeight(image)];
	for (y = 0; y < ImageHeight(image); y++){
		for (x = 0; x < ImageWidth(image); x++) {
			tmpR[x][y] = GetPixelR(image, x,y);
			tmpG[x][y] = GetPixelG(image, x,y);
			tmpB[x][y] = GetPixelB(image, x,y);
		}
	}
	int sumR = 0;   /* sum of the intensity differences with neighbors */
	int sumG = 0;
	int sumB = 0;
	for (y = 1; y < ImageHeight(image) - 1; y++){
		for (x = 1; x < ImageWidth(image) - 1; x++){
			for (n = -1; n <= 1; n++){
				for (m = -1; m <= 1; m++) {
					a = (x + m >= ImageWidth(image)) ? ImageWidth(image) - 1 : (x + m < 0) ? 0 : x + m;
					b = (y + n >= ImageHeight(image)) ? ImageHeight(image) - 1 : (y + n < 0) ? 0 : y + n;
					sumR += (tmpR[x][y] - tmpR[a][b]);
					sumG += (tmpG[x][y] - tmpG[a][b]);
					sumB += (tmpB[x][y] - tmpB[a][b]);
				}
			}
			SetPixelR(image, x, y, (sumR > MAX_PIXEL) ? MAX_PIXEL: (sumR < 0) ? 0: sumR);
			SetPixelG(image, x, y, (sumG > MAX_PIXEL) ? MAX_PIXEL: (sumG < 0) ? 0: sumG);
			SetPixelB(image, x, y, (sumB > MAX_PIXEL) ? MAX_PIXEL: (sumB < 0) ? 0: sumB);
			sumR = sumG = sumB = 0;
		}
	}
	/* set all 24 borders to 0 */
	for (y = 0; y < ImageHeight(image); y++) {
		SetPixelR(image, 0, y, 0);
		SetPixelG(image, 0, y, 0);
		SetPixelB(image, 0, y, 0);
		SetPixelR(image, ImageWidth(image) - 1, y, 0);
		SetPixelG(image, ImageWidth(image) - 1, y, 0);
		SetPixelB(image, ImageWidth(image) - 1, y, 0);
	}
	
	for (x = 0; x < ImageWidth(image); x++) {
		SetPixelR(image, x, 0, 0);
		SetPixelG(image, x, 0, 0);
		SetPixelB(image, x, 0, 0);
		SetPixelR(image, x, ImageHeight(image) - 1, 0);
		SetPixelG(image, x, ImageHeight(image) - 1, 0);
		SetPixelB(image, x, ImageHeight(image) - 1, 0);
	}
	return image;

}

/* mirror image horizontally */
Image *HMirror(Image *image)
{
	assert(image != NULL);
	int x, y;

	for (y = 0; y < ImageHeight(image); y++) {
		for (x = 0; x < ImageWidth(image) / 2; x++) {
			SetPixelR(image, ImageWidth(image) - 1 - x, y, GetPixelR(image, x,y));
			SetPixelG(image, ImageWidth(image) - 1 - x, y, GetPixelG(image, x,y));
			SetPixelB(image, ImageWidth(image) - 1 - x, y, GetPixelB(image, x,y));
		}
	}
	return image;

}

/* pixelate the image */
Image *Pixelate(Image *image, int block_size)
{
	assert(image != NULL);
    int x, y, bx, by;
    int sumR, sumG, sumB;
    int count;

    for (y = 0; y < ImageHeight(image) - ImageHeight(image) % block_size; y += block_size) {
        for (x = 0; x < ImageWidth(image) - ImageWidth(image) % block_size; x += block_size) {
            sumR = sumG = sumB = 0; // initialize
            count = 0;

            for (by = 0; by < block_size; by++) {
                for (bx = 0; bx < block_size; bx++) {
                    sumR += GetPixelR(image, x + bx,y + by);
                    sumG += GetPixelG(image, x + bx,y + by);
                    sumB += GetPixelB(image, x + bx,y + by);
                    count++;
                }
            }

            // calculate average RGB value
            sumR = sumR / count;
            sumG = sumG / count;
            sumB = sumB / count;

            // write new values to pixels in the block
            for (by = 0; by < block_size; by++) {
                for (bx = 0; bx < block_size; bx++) {
                    SetPixelR(image, x + bx, y + by, sumR);
                    SetPixelG(image, x + bx, y + by, sumG);
                    SetPixelB(image, x + bx, y + by, sumB);
                }
            }
        }
    }
	return image;

}

/* change color image to black & white */
Image *BlackNWhite(Image *image)
{
	assert(image != NULL);
	int             x, y, tmp;

	for (y = 0; y < ImageHeight(image); y++)
	{
		for (x = 0; x < ImageWidth(image); x++)
		{
			tmp = (GetPixelR(image, x,y) + GetPixelG(image, x,y) + GetPixelB(image, x,y) )/ 3;
			SetPixelR(image, x,y, tmp);
			SetPixelG(image, x,y, tmp);
			SetPixelB(image, x,y, tmp);
		}
	}
	return image;

}

/* flip image vertically */
Image *VFlip(Image *image)
{
	assert(image != NULL);
	int             x, y;
	unsigned char   r, g, b;

	for (y = 0; y < ImageHeight(image)/2; y++) {
		for (x = 0; x < ImageWidth(image); x++) {
			r = GetPixelR(image, x,ImageHeight(image) - 1 - y);
			g = GetPixelG(image, x,ImageHeight(image) - 1 - y);
			b = GetPixelB(image, x,ImageHeight(image) - 1 - y);

			SetPixelR(image, x,ImageHeight(image) - 1 - y, GetPixelR(image, x, y));
			SetPixelG(image, x,ImageHeight(image) - 1 - y, GetPixelG(image, x, y));
			SetPixelB(image, x,ImageHeight(image) - 1 - y, GetPixelB(image, x, y));

			SetPixelR(image, x, y, r);
			SetPixelG(image, x, y, g);
			SetPixelB(image, x, y, b);
		}
	}
	return image;

}

/* Add Border to the image*/
Image *AddBorder(Image *image, char color[SLEN], int border_width){
	assert(image != NULL);
	int x, y, i, r, g, b;

	if (strcmp(color, "red") == 0) {
		r = 255; g = 0; b = 0;
	} else if (strcmp(color, "green") == 0) {
		r = 0; g = 255; b = 0;
	} else if (strcmp(color, "blue") == 0) {
		r = 0; g = 0; b = 255;
	} else if (strcmp(color, "black") == 0) {
		r = 0; g = 0; b = 0;
	} else if (strcmp(color, "white") == 0) {
		r = 255; g = 255; b = 255;
	} else if (strcmp(color, "cyan") == 0) {
		r = 0; g = 255; b = 255;
	} else if (strcmp(color, "pink") == 0) {
		r = 255; g = 192; b = 203;
	} else if (strcmp(color, "orange") == 0) {
		r = 255; g = 165; b = 0;
	} else {
		printf("please choose a color from the options\n");
		return image;
	}
	
	
	for(i = 0; i < border_width; i++){
		for (y = 0; y < ImageHeight(image); y++) {
			SetPixelR(image, i, y, r);
			SetPixelG(image, i, y, g);
			SetPixelB(image, i, y, b);
			SetPixelR(image, ImageWidth(image) - 1 - i, y, r);
			SetPixelG(image, ImageWidth(image) - 1 - i, y, g);
			SetPixelB(image, ImageWidth(image) - 1 - i, y, b);
		}
		
		for (x = 0; x < ImageWidth(image); x++) {
			SetPixelR(image, x, i, r);
			SetPixelG(image, x, i, g);
			SetPixelB(image, x, i, b);
			SetPixelR(image, x, ImageHeight(image) - 1 - i, r);
			SetPixelG(image, x, ImageHeight(image) - 1 - i, g);
			SetPixelB(image, x, ImageHeight(image) - 1 - i, b);
		}
	}
	return image;
}

/* Shuffle the image */
Image *Shuffle(Image *image)
{
	assert(image != NULL);
	int block_width = ImageWidth(image)/SHUFF_WIDTH_DIV;
	int block_height = ImageHeight(image)/SHUFF_HEIGHT_DIV;
	int i, j, x, y;
	unsigned char tempR[block_width][block_height];
	unsigned char tempG[block_width][block_height];
	unsigned char tempB[block_width][block_height];

	for (i = 0; i < SHUFF_HEIGHT_DIV/2; i++){ // only need to iterate throught half of the blocks
		for (j = 0; j < SHUFF_WIDTH_DIV; j++){
			for (x = 0; x < block_width; x++){
				for (y = 0; y < block_height; y++){
					tempR[x][y] = GetPixelR(image, x + (j * block_width), y + (i * block_height));
					tempG[x][y] = GetPixelG(image, x + (j * block_width), y + (i * block_height));
					tempB[x][y] = GetPixelB(image, x + (j * block_width), y + (i * block_height));
					SetPixelR(image, x + (j * block_width), y + (i * block_height), GetPixelR(image, x + ((SHUFF_WIDTH_DIV - 1 -j) * block_width), y + ((SHUFF_HEIGHT_DIV - 1 -i) * block_height)));
					SetPixelG(image, x + (j * block_width), y + (i * block_height), GetPixelG(image, x + ((SHUFF_WIDTH_DIV - 1 -j) * block_width), y + ((SHUFF_HEIGHT_DIV - 1 -i) * block_height)));
					SetPixelB(image, x + (j * block_width), y + (i * block_height), GetPixelB(image, x + ((SHUFF_WIDTH_DIV - 1 -j) * block_width), y + ((SHUFF_HEIGHT_DIV - 1 -i) * block_height)));
					SetPixelR(image, x + ((SHUFF_WIDTH_DIV - 1 -j) * block_width), y + ((SHUFF_HEIGHT_DIV - 1 -i) * block_height), tempR[x][y]);
					SetPixelG(image, x + ((SHUFF_WIDTH_DIV - 1 -j) * block_width), y + ((SHUFF_HEIGHT_DIV - 1 -i) * block_height), tempG[x][y]);
					SetPixelB(image, x + ((SHUFF_WIDTH_DIV - 1 -j) * block_width), y + ((SHUFF_HEIGHT_DIV - 1 -i) * block_height), tempB[x][y]);
				}
			}
		}
	}
	return image;

}