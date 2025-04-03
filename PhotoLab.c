#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Constants.h"
#include "DIPs.h"
#include "Advanced.h"
#include "FileIO.h"
#include "Image.h"
#include "Test.h"

void PrintMenu();

int main() {
    Image *image = NULL;
    int option = 0;
    char fname[SLEN];
    int x, y, rc, W, H, block_size, shiftX, shiftY, newWidth, newHeight, target_r, target_g, target_b, threshold, factor_r, factor_g, factor_b, border_width;
    char color[SLEN];
    Image *watermark_image = NULL;
    int rotateDirection;

	#ifdef DEBUG
		return AutoTest();
	#endif
	
    PrintMenu();
    printf("Please make your choice: ");
    scanf("%d", &option);

    while (option != 18) {
        if (option == 1) {
            printf("Please input the file name to load: ");
            scanf("%s", fname);
            image = LoadImage(fname);
            printf("%s was read successfully!\n", fname);
            if (!image) {
                printf("Failed to load image.\n");
            }
        } else if (option == 2 && image) {
            printf("Please input the file name to save: ");
            scanf("%s", fname);
            rc = SaveImage(fname, image);
            if(rc){
                printf("\nCan't open file \"%s\" for writing!\n", fname);
            }
            else{ 
                printf("%s was saved successfully. \n", fname);
            }
        } else if (image) {
            switch(option) {
                case 3:
                    image = BlackNWhite(image);
                    printf("Black & White operation is done!\n");
                    break;
                case 4:
                    image = Negative(image);
                    printf("Negative operation is done!\n");
                    break;
                case 5:
                    printf("Enter Red   component for the target color: ");
                    scanf("%d", &target_r);
                    printf("Enter Green component for the target color: ");
                    scanf("%d", &target_g);
                    printf("Enter Blue  component for the target color: ");
                    scanf("%d", &target_b);
                    printf("Enter threshold for the color difference: ");
                    scanf("%d", &threshold);
                    printf("Enter value for Red component in the target color: ");
                    scanf("%d", &factor_r);
                    printf("Enter value for Green component in the target color: ");
                    scanf("%d", &factor_g);
                    printf("Enter value for Blue  component in the target color: ");
                    scanf("%d", &factor_b);
                    ColorFilter(image, target_r, target_g, target_b, threshold, factor_r, factor_g, factor_b);
                case 6:
                    image = Edge(image);
                    printf("Edge operation is done!\n");
                    break;
                case 7:
                    image = Shuffle(image);
                    printf("Shuffle operation is done!\n");
                    break;
                case 8:
                    image = VFlip(image);
                    printf("Vertical Flip operation is done!\n");
                    break;
                case 9:
                    image = HMirror(image);
                    printf("Horizontal Mirror operation is done!\n");
                    break;
                case 10:
                    printf("Enter border width: ");
                    scanf("%d", &border_width);
                    printf("Enter border color: ");
                    scanf("%s", color);
                    image = AddBorder(image, color, border_width);
                    printf("Add Border operation is done!\n");
                    break;
                case 11:
                    printf("Enter pixelate block size: ");
                    scanf("%d", &block_size);
                    image = Pixelate(image, block_size);
                    printf("Pixelate operation is done!\n");
                    break;
                case 12:
                    printf("Enter shift X: ");
                    scanf("%d", &shiftX);
                    printf("Enter shift Y: ");
                    scanf("%d", &shiftY);
                    image = Shift(image, shiftX, shiftY);
                    printf("Shift operation is done!\n");
                    break;
                case 13:
                    printf("Enter crop X: ");
                    scanf("%d", &x);
                    printf("Enter crop Y: ");
                    scanf("%d", &y);
                    printf("Enter crop width: ");
                    scanf("%d", &W);
                    printf("Enter crop height: ");
                    scanf("%d", &H);
                    image = Crop(image, x, y, W, H);
                    printf("Crop operation is done!\n");
                    break;
				case 14:
                    printf("Enter new width: ");
                    scanf("%d", &newWidth);
                    printf("Enter new height: ");
                    scanf("%d", &newHeight);
                    image = Resize(image, newWidth, newHeight);
                    printf("Resize operation is done!\n");
                    break;
                case 15:
                    watermark_image = LoadImage("watermark_template.ppm");
                    image = Watermark(image, watermark_image);
                    printf("Watermark operation is done!\n");
                    DeleteImage(watermark_image);
                    break;
                case 16:
                    printf("Enter rotation direction (0: clockwise, 1: counterclockwise): ");
                    scanf("%d", &rotateDirection);
                    image = RotateBy90(image, rotateDirection);
                    printf("RotateBy90 operation is done!\n");
                    break;
                case 17:
                    rc = AutoTest();
                    if(rc != 0){
                        printf("AutoTest failed, error code %d", rc);
                    }
                    else{ 
                        printf("AutoTest finished successfully.");
                    }
                    break;
                default:
                    printf("Invalid selection!\n");
                    break;
            }
        } 
         else {
            printf("No image to process!\n");
        }

        PrintMenu();
        printf("Please make your choice: ");
        scanf("%d", &option);
    }


    if (image) {
        DeleteImage(image);
    }
    printf("Exiting the program...\n");
    return 0;
}

void PrintMenu() {
    printf("\n--------------------------------------------\n");
	printf(" 1: Load a PPM image\n");
	printf(" 2: Save an image in PPM and JPEG format\n");
	printf(" 3: Change a color image to Black & White\n");
	printf(" 4: Make a negative of an image\n");
	printf(" 5: Color filter an image\n");
	printf(" 6: Sketch the edge of an image\n");
	printf(" 7: Shuffle an image\n");
	printf(" 8: Flip an image vertically\n");
	printf(" 9: Mirror an image horizontally\n");
    printf("10: Add Border to Image\n");
    printf("11: Pixelate an image\n");
    printf("12: Shift Image\n");
    printf("13: Crop Image\n");
    printf("14: Resize Image\n");
    printf("15: Add Watermark to Image\n");
    printf("16: Rotate Image by 90 degrees\n");
    printf("17: Test All Functions\n");
    printf("18: Exit\n");
    printf("--------------------------------------------\n");
}
