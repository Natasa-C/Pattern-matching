# Pattern-matching

An algorithm for the recognition of patterns (customized in this project to handwritten numbers) in a bmp image using a set of ten templates for the ten digits to be recognized.

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

# The pattern recognition module
Digital image processing is a branch of computer science that uses algorithms for image processing in digital (and not analog) format in order to extract useful information from images to solve complex problems. Such a complex problem is the recognition of patterns, customized in this project to the problem of recognizing the numbers written by hand in an image.

![Screenshot at 2020-02-13 18-40-01](https://user-images.githubusercontent.com/57111995/74456972-48b06b80-4e90-11ea-8488-2ce610777fab.png)

The problem of recognizing handwritten figures is a fundamental problem in digital image processing. The problem is difficult because the numbers differ in size, appearance, color, gradient, etc. The most complex algorithms use machine learning and learn a model for each digit from tens of thousands of images. Their performance on this issue is comparable to that of people.

For this project we will use a simple method in recognizing handwritten figures in an image, namely finding templates ([Template matching](https://en.wikipedia.org/wiki/Template_matching)). This method consists of finding small parts of an image that match a template image. For the problem of recognizing handwritten figures we will use 10-digit images as templates. Each template is a color image (it has 3 channels) with dimensions 11 × 15 pixels (11 pixels wide, 15 pixels high). The template matching algorithm applied for a color image I  and a template S (a color image representing a figure) works as follows:
1) transform the color image I and the template S into grayscale images.
2) slide the current template on image I by centering the template in each point of the image I. Calculate for each position (x, y) in image I the correlation ([Cross-correlation](https://en.wikipedia.org/wiki/Cross-correlation)) between the current template and the corresponding content of the image given by the window f<sub>1</sub> = f<sub>1</sub> (x, y) centered on point (x, y). The formula for calculating the correlation between template S and window f<sub>1</sub> is the following:
![form1](https://user-images.githubusercontent.com/57111995/74458099-de98c600-4e91-11ea-9eb3-8609f28fedef.png)

where:
- n represents the number of pixels of template S (in particular for templates used with dimensions 11 × 15 pixels we have n = 11 * 15 = 165);
- indices i and j represent line i and column j in template S (15 lines and 11 columns);
- S (i, j) represents the value of the grayscale intensity of the pixel from line i and column j in template S. For a grayscale image, a pixel P = (P<sup>R</sup>, P<sup>G</sup>, P<sup>B</sup>) is represented by a triplet with all the values equal P<sup>R</sup> = P<sup>G</sup> = P<sup>B</sup> . In this case the value of the grayscale intensity of P is P<sup>R</sup>;
- S<sup>-</sup> represents the average of the grayscale intensities of the pixels in the S window (the average of the 165 pixels in the S template);
- σ<sub>S</sub> represents the standard deviation of the pixel grayscale intensities values in the S pattern:
![form2](https://user-images.githubusercontent.com/57111995/74458596-9f1ea980-4e92-11ea-92a2-cfec30c0efb1.png)
- f<sub>I</sub>(i, j) represents the value of the grayscale intensity of the pixel from line i and column j in the window f<sub>I</sub>;
- f<sup>-</sup><sub>I</sub> represents the average of the values of the grayscale intensities of the pixels in the window f<sub>I</sub> (average of 165 pixels in window f<sub>I</sub>);
- σ<sub>f<sub>I</sub></sub> represents the standard deviation of the values of the grayscale intensities of the pixels in the window f<sub>I</sub> :
![form3](https://user-images.githubusercontent.com/57111995/74459030-4996cc80-4e93-11ea-911e-094118e3d423.png)

At the edges of the image I, the template S comes out of the image I. You can implement this limit case by adding pixels with the value 0 (black pixels) outside the image I. A less elegant option is to consider only the positions (x, y) in image I for which template S fits in image I.

Correlation between template S and the corresponding window f<sub>I</sub> is large at the positions (x, y) of the image I where the content of the image matches the content of the template S. The correlation is a real number between -1 and 1, a correlation value of 1 indicates a perfect correlation with the template S. For viewing the windows f<sub>I</sub> with a high correlation with the S pattern (named in the following detections) the following are realized:
1. windows with correlation greater than a threshold p<sub>S</sub> are kept as detections. Low values of threshold p<sub>S</sub> lead to a large number of detections f<sub>I</sub> , high values of the threshold p<sub>S</sub> lead to a small number of detections f<sub>I</sub> .
2. for visualizing the f<sub>I</sub> detections we can color the outline of the window f<sub>I</sub> with a certain color in the picture.

The figure shows the results obtained for templates with figures 0 and 5 and thresholds 0.35 and 0.70.

![hghghg](https://user-images.githubusercontent.com/57111995/74459853-a777e400-4e94-11ea-8914-730292e6d05a.png)

Running all 10 templates on image I for different values will lead to similar results, depending on the threshold chosen. When we gather the detections of all the figures we will see that they overlap very much:
![we1](https://user-images.githubusercontent.com/57111995/74460106-0fc6c580-4e95-11ea-923d-1bd173b256cd.png)

In practice, a technique called elimination of non-maximum is used to avoid this phenomenon. It consists of the following:
1) all detections obtained for all 10 templates are placed in a one-dimensional array D;
2) D is sorted decreasing according to the correlation score of each detection;
3) the table D is processed from left (detections with very high score) to right (detections with very low score) as follows: all detections d<sub>j</sub> which overlaps spatially with the current detection d<sub>i</sub>, with i <j and score (d<sub>i</sub>)> score (d<sub>j</sub>) is deleted.

Spatial overlap between two detections d<sub>i</sub> and d<sub>j</sub> is measured as the ratio between the intersection and the meeting area of the two windows. (suprapunere = overlap, aria = area)

![we2](https://user-images.githubusercontent.com/57111995/74460650-de9ac500-4e95-11ea-8322-7d9c7bc00b75.png)

In this project we will consider that two windows overlap if their spatial overlap is > 0.2.


![we3](https://user-images.githubusercontent.com/57111995/74460726-0c800980-4e96-11ea-8f5f-e621fa257605.png)

After applying the non-maximum elimination algorithm we eliminate all overlapping detections. The remaining detections provide better performance for the handwriting digit recognition algorithm using template matching.

## Requirements:
1) Write a function that implements the template matching operation between an image I and a template S. The function will have as parameters the image I, the template S and the threshold p<sub>S</sub> and provides f<sub>I</sub> which have a higher correlation than the threshold p<sub>S</sub>.
2) Write a function that receives as an parameter an image I, a window f<sub>I</sub> and a color C = (C<sup>R</sup>, C<sup>G</sup>, C<sup>B</sup>) and draws the outline of the window f<sub>I</sub> over image I using color C (as in the examples above).
3) Using the qsort function in the stdlib.h library, write a function that sorts a D array of detections in the descending order of the detection correlations.
4) Write a function that implements the non-maximum elimination algorithm.
5) Write a program that performs the following operations: 
- encrypt a BMP color image and save the encrypted image to the external memory (both image paths and the text file containing the secret key will be read from the keyboard or from a text file);
- decrypt an encrypted BMP color image and save the decrypted image to external memory (both image paths and the text file containing the secret key will be read from the keyboard or from a text file);
- displays the χ<sup>2</sup> test values ​ for the initial image and the encrypted image, on each color channel.
- runs the template matching operation for a BMP color image and a collection of BMP color templates. Always use a threshold pχ<sub>2</sub> = 0.5 regardless of the template chosen. Gather all the resulting detections for each template in a single one-dimensional array D. The image paths and BMP templates will be read from the keyboard or from a text file.
- run the non-maximum elimination function on the D array and draw the remaining detections in the image using a specific color for each template.

When drawing the appropriate windows, use the following colors:
- For digit 0 - red color: (255, 0, 0)
- For digit 1 - yellow: (255, 255, 0)
- For digit 2 - green color: (0, 255, 0)
- For digit 3 - cyan color: (0, 255, 255)
- For digit 4 - magenta color: (255, 0, 255)
- For digit 5 - blue color: (0, 0, 255)
- For digit 6 - silver color: (192,192, 192)
- For digit 7 - blue color: (255, 140, 0)
- For digit 8 - magenta color: (128, 0, 128)
- For digit 9 - blue color: (128, 0, 0)



