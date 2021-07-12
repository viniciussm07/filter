#include "bmp.h"

// Average
int average(float sum, float n);

// calculate each pixel for edges
RGBTRIPLE edges_calc(int height, int width, int a, int b, RGBTRIPLE tmp[height + 2][width + 2]);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]);

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]);

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width]);

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]);

