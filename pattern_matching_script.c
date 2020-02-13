#include "pattern_matching_functions.h"

#define HEADER_LENGTH 54
#define TEMPLATE_NUMBER 10
#define FILE_NAME_LENGTH 100
#define WIDTH_POSITION_IN_HEADER 18
#define HEIGHT_POSITION_IN_HEADER 22
#define CORRELATION_THRESHOLD 0.5
#define MAXIMUM_OVERLAY 0.2

/*
To compile:  	gcc pattern_matching_script.c pattern_matching_functions.c -o script -lm
To run:		    ./script
*/

int main()
{
    unsigned char source_file_name[] = "input_resources/pattern_matching.txt";
    unsigned char BMP_sorce_file_name[FILE_NAME_LENGTH];
    unsigned char BMP_output_file_name[FILE_NAME_LENGTH];

    FILE *fin;

    unsigned int H, W, w, h, detections_array_length = 0, i;
    unsigned char *headerBMP;
    Detection *detections_array;
    Pixel *BMP_array, *border_color_array;

    fin = fopen(source_file_name, "r");
    if (fin == NULL)
    {
        printf("In function -main- file could not be opened %s!", source_file_name);
        return 0;
    }

    fgets(BMP_sorce_file_name, FILE_NAME_LENGTH, fin);
    removeTrailingTerminator(BMP_sorce_file_name);

    fgets(BMP_output_file_name, FILE_NAME_LENGTH, fin);
    removeTrailingTerminator(BMP_output_file_name);

    readWidthAndHeight(BMP_sorce_file_name, &W, &H);
    allocateMemoryForUnsignedCharArrays(&headerBMP, HEADER_LENGTH);
    allocateMemoryForPixelArrays(&BMP_array, W * H);
    loadLinearizedHeaderInInternalMemory(BMP_sorce_file_name, &headerBMP);
    loadLinearizedBMPImageInInternalMemory(BMP_sorce_file_name, &BMP_array, W, H);
    grayScaleLinearizedImage(&BMP_array, H, W);

    allocateMemoryForPixelArrays(&border_color_array, TEMPLATE_NUMBER);

    templateMatching(fin, &detections_array, &detections_array_length, &border_color_array, &BMP_array, &h, &w, H, W);
    if (fclose(fin) != 0)
        printf("\nIn function -main- file could not be closed %s\n!", source_file_name);

    eliminationOfNonMaximums(&detections_array, &detections_array_length, h, w, H, W);
    loadLinearizedBMPImageInInternalMemory(BMP_sorce_file_name, &BMP_array, W, H);
    addBlackBorder(&BMP_array, h, w, H, W);

    for (i = 0; i < detections_array_length; i++)
        drawOutline(&BMP_array, detections_array[i].index, &border_color_array[detections_array[i].digit], h, w, H, W);

    removeBlackBorder(&BMP_array, h, w, H, W);
    saveLinearizedBMPImageInExternalMemory(BMP_output_file_name, headerBMP, BMP_array, W, H);

    free(detections_array);
    free(border_color_array);
    free(BMP_array);
    free(headerBMP);
    return 0;
}
