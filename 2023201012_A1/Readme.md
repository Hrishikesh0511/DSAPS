# Seam Carving Implementation
## code in 2023201012_A1_Q3.cpp
## Overview

Seam carving is a content-aware image resizing technique used to adjust the size of an image by removing or adding seams. This method preserves important content in the image, minimizing distortion compared to traditional resizing techniques.

## Example Images

### Original Image

This is the original image before applying seam carving:

![Original image](sample_input/sample1.jpeg)


### Resized Image

This is the image after applying seam carving:

![Resized Image](sample_input/surfer-resized.jpg)

## Installation of open cv

https://www.geeksforgeeks.org/how-to-install-opencv-in-c-on-linux/

## Running the file 

> g++ 2023201011_A2_Q3.cpp pkg-config --cflags --libs opencv4
> ./a.out 

## References

    Avidan, S., & Shamir, A. (2007). Seam Carving for Content-Aware Image Resizing. ACM Transactions on Graphics (TOG), 26(3), 10.
