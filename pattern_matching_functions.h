#ifndef PATTERN_MATCHING_FUNCTIONS
#define PATTERN_MATCHING_FUNCTIONS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct
{
    unsigned char B, G, R;
} Pixel;

typedef struct
{
    unsigned int digit;
    unsigned int index;
    float correlation;
} Detection;

void removeTrailingTerminator(unsigned char *string);
void allocateMemoryForUnsignedCharArrays(unsigned char **array, unsigned int length);
void allocateMemoryForPixelArrays(Pixel **array, unsigned int length);
void allocateMemoryForUnsignedIntArrays(unsigned int **array, unsigned int length);
void allocateMemoryForDetectionArrays(Detection **vector, unsigned int dimensiune);
void readWidthAndHeight(unsigned char *source_file_name, int *width, int *height);
void loadLinearizedHeaderInInternalMemory(unsigned char *source_file_name, unsigned char **vector);
void loadLinearizedBMPImageInInternalMemory(unsigned char *souce_file_name, Pixel **image_array, unsigned int W, unsigned int H);
void saveLinearizedBMPImageInExternalMemory(unsigned char *destination_file_name, unsigned char *header_array, Pixel *BMP_image_array, unsigned int W, unsigned int H);
void grayScaleLinearizedImage(Pixel **BMP_array, unsigned int H, unsigned int W);
void addBlackBorder(Pixel **BMP_array, unsigned int h, unsigned int w, unsigned int H, unsigned int W);
void removeBlackBorder(Pixel **BMP_array, unsigned int h, unsigned int w, unsigned int H, unsigned int W);
void calculateMeanAndDeviation(Pixel *BMP_array, unsigned int x, unsigned int y, unsigned int h, unsigned int w, unsigned int W, float *mean, float *deviation);
void templateMatchingForASingleTemplate(Detection **detections_array, unsigned int digit, int *detections_array_length, Pixel *BMP_array, Pixel *template_array, unsigned int h, unsigned int w, unsigned int H, unsigned int W, float ps);
void templateMatching(FILE *fin, Detection **detections_array, unsigned int *detections_array_length, Pixel **border_color_array, Pixel **BMP_array, unsigned int *h, unsigned int *w, int H, unsigned int W);
void drawOutline(Pixel **BMP_array, unsigned int position, Pixel *C, unsigned int h, unsigned int w, unsigned int H, unsigned int W);
int cmpcorrelation(const void *a, const void *b);
void sortDetectionInDescendingOrder(Detection **detections_array, unsigned int detections_array_length);
int overlayCheck(unsigned int xC, unsigned int yC, unsigned int xD, unsigned int yD, unsigned int h, unsigned int w, float suprapunereMaxima);
void calculateIntersectionCoordinates(Detection **detections_array, unsigned int *xC, unsigned int *yC, unsigned int *xD, unsigned int *yD, unsigned int i, unsigned int j, unsigned int h, unsigned int w, unsigned int H, unsigned int W);
void eliminationOfNonMaximums(Detection **detections_array, unsigned int *detections_array_length, unsigned int h, unsigned int w, unsigned int H, unsigned int W);

#endif