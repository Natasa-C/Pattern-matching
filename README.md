# Pattern-matching

An algorithm for encrypting and decrypting bmp files. The encrypted images have a uniform distribution of pixel values in each color channel, so as to hide the uneven distribution of pixel values in the original image that can provide relevant statistical information.

## Compile and run
### pattern_matching_script.c
> To compile:  	gcc pattern_matching_script.c pattern_matching_functions.c -o script -lm

> To run:		    ./script

### Output for the pattern_matching_script.c

BMP_input.bmp              |  BMP_output.bmp       
:-------------------------:|:-------------------------:
![BMP_input](https://user-images.githubusercontent.com/57111995/74466212-7b159500-4e9f-11ea-99b6-527447ed7925.jpg)  |  ![BMP_output](https://user-images.githubusercontent.com/57111995/74466217-7c46c200-4e9f-11ea-875f-f19acb2c74bd.jpg)


## Project theme
Digital image processing is a very important area of mathematics and computer science. The project theme is the recognition of patterns (customized in this project to handwritten numbers) in an image.

The scenario to be implemented in this project is the following: person A sends to person B an image I encrypted using an encryption algorithm. B can decrypt the encrypted image received from A thus obtaining the initial image I on which applies an algorithm to recognize the handwritten figures in the image I. Person B then sends to the person A the resulting image that he encrypts. Person A decrypts the encrypted image received from B and can view the solution, recognizing the numbers written by hand. The theme of the project is the implementation of the pattern recognition module of handwritten numbers.

In this project we will be working with color images, which we can manipulate in C language as binary files. Images are in BMP (bitmap) format. Unlike other formats (JPG, JPEG, PNG, etc.) the BMP format does not compress images, but stores 3 bytes per pixel for color images. This feature makes the BMP format suitable for this project as we can explicitly access the pixel intensity values that make up the color image. To view the images on our personal computer we must have a specific program installed (IrfanView, Paint, Gimp, Preview, ImageJ etc.).

The project will be structured in one module that deals with the recognition of handwritten numbers in an image using the template matching method.

## BMP format
BMP format (bitmap) is a file format used to store two-dimensional digital images of arbitrary width, height and resolution, monochrome or color. In this project you will only work with color images. Basically, in BMP format, the image is viewed as a pixel array, and each pixel is a full value. The first 3 bytes of a pixel representation are the intensity of the 3 color channels R (Red), G (green), B (blue). Consequently, the intensity of each color channel R, G, B is given by a natural value between 0 and 255. For example, a pixel with values (0, 0, 0) represents a black pixel, and a pixel with a black color the values (255, 255, 255) represent a white pixel. At [RGB Color Codes Chart](https://www.rapidtables.com/web/color/RGB_Color.html) you can find the correspondence between RGB triplets and colors.

The BMP format is described here: [BMP file format](https://en.wikipedia.org/wiki/BMP_file_format) in a comprehensive way. The BMP format includes a fixed-size data area, called a header, and a variable-size data area that contains the pixels of the image itself. The header, which occupies the first 54 bytes of the file, contains information about the BMP format, as well as information about the image size, the number of bytes used to represent a pixel, etc.

The size of the image in bytes is specified in the header by an unsigned integer value, so it is stored on 4 bytes, starting with the byte with the order number 2. The image size in pixels is expressed as W × H, where W represents the number of pixels per width, and H represents the number of pixels per height. The image width expressed in pixels is stored on four unsigned bytes starting with the 18th byte in the header, and the height is stored on the next 4 unsigned bytes in the header, respectively starting with the 22nd octet in the header.

For fast processing of images in reading and writing, BMP images have the property that each line has a number of bytes that is a multiple of 4. This is achieved by adding padding bytes so that the total number of bytes on a line becomes multiple of 4. The number of bytes of a line is 3 × width (3 bytes per pixel on a line). Thus, if an image has 11 pixels in width (as with the templates we will work with) the number of bytes of padding is 3 (3 × 11 = 33 bytes per line, so at the end of each line, 3 padding bytes will be added so that we have 33 + 3 = 36 multiple of 4 bytes). Usually the padding bytes added are 0. 

Because the encoding of a BMP image in a binary file follows the little-endian standard, the bytes corresponding to the 3 color channels R, G, B are stored from right to left, that is, in order B, G, R. A color image can be transformed into a grayscale image by replacing the (R, G, B) values of each pixel with the values (R', G', B') defined as follows:

<p align="center">R' = G' = B' = [ 0.299 ∗ R + 0.587 ∗ G + 0.114 ∗ B]</p>

where by [x] we note the whole part of the real number x. The grayscale image obtained has the property that it also uses 3 bytes to represent the color of each pixel, but all the values on the 3 channels are equal.

![fig1](https://user-images.githubusercontent.com/57111995/74440714-31b14f80-4e77-11ea-9a73-ce1ddb057b31.png)

