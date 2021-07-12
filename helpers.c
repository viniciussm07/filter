#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

// Average
int average(float sum, float n)
{
    sum = sum / n;
    sum = round(sum);
    return sum;
}

// Calculate each pixel for edges
RGBTRIPLE edges_calc(int height, int width, int a, int b, RGBTRIPLE tmp[height + 2][width + 2])
{
    // 3x3 grids for the Sobel operator
    int X[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Y[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // weighted sums
    float gxr, gyr, gxg, gyg, gxb, gyb;

    // sobel operator results
    float gr, gg, gb;

    // red
    gxr = (tmp[a - 1][b - 1].rgbtRed * X[0][0]) + (tmp[a - 1][b].rgbtRed * X[0][1]) + (tmp[a - 1][b + 1].rgbtRed * X[0][2]) +
          (tmp[a][b - 1].rgbtRed * X[1][0]) + (tmp[a][b].rgbtRed * X[1][1]) + (tmp[a][b + 1].rgbtRed * X[1][2]) +
          (tmp[a + 1][b - 1].rgbtRed * X[2][0]) + (tmp[a + 1][b].rgbtRed * X[2][1]) + (tmp[a + 1][b + 1].rgbtRed * X[2][2]);
    gyr = (tmp[a - 1][b - 1].rgbtRed * Y[0][0]) + (tmp[a - 1][b].rgbtRed * Y[0][1]) + (tmp[a - 1][b + 1].rgbtRed * Y[0][2]) +
          (tmp[a][b - 1].rgbtRed * Y[1][0]) + (tmp[a][b].rgbtRed * Y[1][1]) + (tmp[a][b + 1].rgbtRed * Y[1][2]) +
          (tmp[a + 1][b - 1].rgbtRed * Y[2][0]) + (tmp[a + 1][b].rgbtRed * Y[2][1]) + (tmp[a + 1][b + 1].rgbtRed * Y[2][2]);

    gr = sqrt((gxr * gxr) + (gyr * gyr));
    gr = round(gr);

    // green
    gxg = (tmp[a - 1][b - 1].rgbtGreen * X[0][0]) + (tmp[a - 1][b].rgbtGreen * X[0][1]) + (tmp[a - 1][b + 1].rgbtGreen * X[0][2]) +
          (tmp[a][b - 1].rgbtGreen * X[1][0]) + (tmp[a][b].rgbtGreen * X[1][1]) + (tmp[a][b + 1].rgbtGreen * X[1][2]) +
          (tmp[a + 1][b - 1].rgbtGreen * X[2][0]) + (tmp[a + 1][b].rgbtGreen * X[2][1]) + (tmp[a + 1][b + 1].rgbtGreen * X[2][2]);
    gyg = (tmp[a - 1][b - 1].rgbtGreen * Y[0][0]) + (tmp[a - 1][b].rgbtGreen * Y[0][1]) + (tmp[a - 1][b + 1].rgbtGreen * Y[0][2]) +
          (tmp[a][b - 1].rgbtGreen * Y[1][0]) + (tmp[a][b].rgbtGreen * Y[1][1]) + (tmp[a][b + 1].rgbtGreen * Y[1][2]) +
          (tmp[a + 1][b - 1].rgbtGreen * Y[2][0]) + (tmp[a + 1][b].rgbtGreen * Y[2][1]) + (tmp[a + 1][b + 1].rgbtGreen * Y[2][2]);

    gg = sqrt((gxg * gxg) + (gyg * gyg));
    gg = round(gg);

    // blue
    gxb = (tmp[a - 1][b - 1].rgbtBlue * X[0][0]) + (tmp[a - 1][b].rgbtBlue * X[0][1]) + (tmp[a - 1][b + 1].rgbtBlue * X[0][2]) +
          (tmp[a][b - 1].rgbtBlue * X[1][0]) + (tmp[a][b].rgbtBlue * X[1][1]) + (tmp[a][b + 1].rgbtBlue * X[1][2]) +
          (tmp[a + 1][b - 1].rgbtBlue * X[2][0]) + (tmp[a + 1][b].rgbtBlue * X[2][1]) + (tmp[a + 1][b + 1].rgbtBlue * X[2][2]);
    gyb = (tmp[a - 1][b - 1].rgbtBlue * Y[0][0]) + (tmp[a - 1][b].rgbtBlue * Y[0][1]) + (tmp[a - 1][b + 1].rgbtBlue * Y[0][2]) +
          (tmp[a][b - 1].rgbtBlue * Y[1][0]) + (tmp[a][b].rgbtBlue * Y[1][1]) + (tmp[a][b + 1].rgbtBlue * Y[1][2]) +
          (tmp[a + 1][b - 1].rgbtBlue * Y[2][0]) + (tmp[a + 1][b].rgbtBlue * Y[2][1]) + (tmp[a + 1][b + 1].rgbtBlue * Y[2][2]);

    gb = sqrt((gxb * gxb) + (gyb * gyb));
    gb = round(gb);

    // array of results
    int E[3] = {gr, gg, gb};
    for (int i = 0; i < 3; i++)
    {
        // condition to be a pixel
        if (E[i] > 255)
        {
            E[i] = 255;
        }
    }

    // return value
    RGBTRIPLE e;

    e.rgbtRed = E[0];
    e.rgbtGreen = E[1];
    e.rgbtBlue = E[2];
    return e;
}


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // color value of each pixel
    int r, g, b;

    // average
    float a;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            r = image[i][j].rgbtRed;
            g = image[i][j].rgbtGreen;
            b = image[i][j].rgbtBlue;

            a = r + g + b;

            a = average(a, 3.0);

            image[i][j].rgbtBlue = a;
            image[i][j].rgbtGreen = a;
            image[i][j].rgbtRed = a;

        }
    }
    return;
}


// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // auxiliary pixel
    RGBTRIPLE aux;

    int j;
    int k;

    for (int i = 0; i < height; i++)
    {
        for (j = 0, k = width - 1; j < width / 2; j++, k--)
        {
            aux = image[i][j];
            image[i][j] = image[i][k];
            image[i][k] = aux;
        }
    }
    return;
}


// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // sum of the color values of each pixel
    int r, g, b;

    // average of each color
    int ar, ag, ab;

    // auxiliary array
    RGBTRIPLE tmp[height][width];

    // copy array image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmp[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // up corner
            if ((i - 1) < 0)
            {
                // left up corner
                if ((j - 1) < 0)
                {
                    r = tmp[i][j].rgbtRed + tmp[i][j + 1].rgbtRed + tmp[i + 1][j].rgbtRed + tmp[i + 1][j + 1].rgbtRed;
                    g = tmp[i][j].rgbtGreen + tmp[i][j + 1].rgbtGreen + tmp[i + 1][j].rgbtGreen + tmp[i + 1][j + 1].rgbtGreen;
                    b = tmp[i][j].rgbtBlue + tmp[i][j + 1].rgbtBlue + tmp[i + 1][j].rgbtBlue + tmp[i + 1][j + 1].rgbtBlue;

                    ar = average(r, 4);
                    ag = average(g, 4);
                    ab = average(b, 4);

                    image[i][j].rgbtRed = ar;
                    image[i][j].rgbtGreen = ag;
                    image[i][j].rgbtBlue = ab;

                    continue;
                }

                // right up corner
                else if ((j + 1) == width)
                {
                    r = tmp[i][j].rgbtRed + tmp[i][j - 1].rgbtRed + tmp[i + 1][j].rgbtRed + tmp[i + 1][j - 1].rgbtRed;
                    g = tmp[i][j].rgbtGreen + tmp[i][j - 1].rgbtGreen + tmp[i + 1][j].rgbtGreen + tmp[i + 1][j - 1].rgbtGreen;
                    b = tmp[i][j].rgbtBlue + tmp[i][j - 1].rgbtBlue + tmp[i + 1][j].rgbtBlue + tmp[i + 1][j - 1].rgbtBlue;

                    ar = average(r, 4);
                    ag = average(g, 4);
                    ab = average(b, 4);

                    image[i][j].rgbtRed = ar;
                    image[i][j].rgbtGreen = ag;
                    image[i][j].rgbtBlue = ab;

                    continue;
                }

                // ordinary up corner
                else
                {
                    r = tmp[i][j - 1].rgbtRed + tmp[i][j].rgbtRed + tmp[i][j + 1].rgbtRed + tmp[i + 1][j - 1].rgbtRed +
                        tmp[i + 1][j].rgbtRed + tmp[i + 1][j + 1].rgbtRed;
                    g = tmp[i][j - 1].rgbtGreen + tmp[i][j].rgbtGreen + tmp[i][j + 1].rgbtGreen + tmp[i + 1][j - 1].rgbtGreen +
                        tmp[i + 1][j].rgbtGreen + tmp[i + 1][j + 1].rgbtGreen;
                    b = tmp[i][j - 1].rgbtBlue + tmp[i][j].rgbtBlue + tmp[i][j + 1].rgbtBlue + tmp[i + 1][j - 1].rgbtBlue +
                        tmp[i + 1][j].rgbtBlue + tmp[i + 1][j + 1].rgbtBlue;

                    ar = average(r, 6);
                    ag = average(g, 6);
                    ab = average(b, 6);

                    image[i][j].rgbtRed = ar;
                    image[i][j].rgbtGreen = ag;
                    image[i][j].rgbtBlue = ab;

                    continue;
                }
            }

            // left corner
            if ((j == 0) && (i > 0))
            {
                // left bottom corner
                if ((i + 1) == height)
                {
                    r = tmp[i][j].rgbtRed + tmp[i][j + 1].rgbtRed + tmp[i - 1][j].rgbtRed + tmp[i - 1][j + 1].rgbtRed;
                    g = tmp[i][j].rgbtGreen + tmp[i][j + 1].rgbtGreen + tmp[i - 1][j].rgbtGreen + tmp[i - 1][j + 1].rgbtGreen;
                    b = tmp[i][j].rgbtBlue + tmp[i][j + 1].rgbtBlue + tmp[i - 1][j].rgbtBlue + tmp[i - 1][j + 1].rgbtBlue;

                    ar = average(r, 4);
                    ag = average(g, 4);
                    ab = average(b, 4);

                    image[i][j].rgbtRed = ar;
                    image[i][j].rgbtGreen = ag;
                    image[i][j].rgbtBlue = ab;

                    continue;
                }
                // ordinary left corner
                else
                {
                    r = tmp[i - 1][j].rgbtRed + tmp[i - 1][j + 1].rgbtRed + tmp[i][j].rgbtRed + tmp[i][j + 1].rgbtRed +
                        tmp[i + 1][j].rgbtRed + tmp[i + 1][j + 1].rgbtRed;
                    g = tmp[i - 1][j].rgbtGreen + tmp[i - 1][j + 1].rgbtGreen + tmp[i][j].rgbtGreen + tmp[i][j + 1].rgbtGreen +
                        tmp[i + 1][j].rgbtGreen + tmp[i + 1][j + 1].rgbtGreen;
                    b = tmp[i - 1][j].rgbtBlue + tmp[i - 1][j + 1].rgbtBlue + tmp[i][j].rgbtBlue + tmp[i][j + 1].rgbtBlue +
                        tmp[i + 1][j].rgbtBlue + tmp[i + 1][j + 1].rgbtBlue;

                    ar = average(r, 6);
                    ag = average(g, 6);
                    ab = average(b, 6);

                    image[i][j].rgbtRed = ar;
                    image[i][j].rgbtGreen = ag;
                    image[i][j].rgbtBlue = ab;

                    continue;
                }
            }
            // right corner
            if ((j == (width - 1)) && (i > 0))
            {
                // right bottom corner
                if ((i + 1) == height)
                {
                    r = tmp[i - 1][j - 1].rgbtRed + tmp[i - 1][j].rgbtRed + tmp[i][j - 1].rgbtRed + tmp[i][j].rgbtRed;
                    g = tmp[i - 1][j - 1].rgbtGreen + tmp[i - 1][j].rgbtGreen + tmp[i][j - 1].rgbtGreen + tmp[i][j].rgbtGreen;
                    b = tmp[i - 1][j - 1].rgbtBlue + tmp[i - 1][j].rgbtBlue + tmp[i][j - 1].rgbtBlue + tmp[i][j].rgbtBlue;

                    ar = average(r, 4);
                    ag = average(g, 4);
                    ab = average(b, 4);

                    image[i][j].rgbtRed = ar;
                    image[i][j].rgbtGreen = ag;
                    image[i][j].rgbtBlue = ab;
                    continue;
                }
                // ordinary right corner
                else
                {
                    r = tmp[i - 1][j - 1].rgbtRed + tmp[i - 1][j].rgbtRed + tmp[i][j - 1].rgbtRed + tmp[i][j].rgbtRed +
                        tmp[i + 1][j - 1].rgbtRed + tmp[i + 1][j].rgbtRed;
                    g = tmp[i - 1][j - 1].rgbtGreen + tmp[i - 1][j].rgbtGreen + tmp[i][j - 1].rgbtGreen +
                        tmp[i][j].rgbtGreen + tmp[i + 1][j - 1].rgbtGreen + tmp[i + 1][j].rgbtGreen;
                    b = tmp[i - 1][j - 1].rgbtBlue + tmp[i - 1][j].rgbtBlue + tmp[i][j - 1].rgbtBlue + tmp[i][j].rgbtBlue +
                        tmp[i + 1][j - 1].rgbtBlue + tmp[i + 1][j].rgbtBlue;

                    ar = average(r, 6);
                    ag = average(g, 6);
                    ab = average(b, 6);

                    image[i][j].rgbtRed = ar;
                    image[i][j].rgbtGreen = ag;
                    image[i][j].rgbtBlue = ab;

                    continue;
                }
            }

            // bottom corner
            if (((i + 1) == height) && (j > 0) && ((j + 1) < width))
            {
                r = tmp[i - 1][j - 1].rgbtRed + tmp[i - 1][j].rgbtRed + tmp[i - 1][j + 1].rgbtRed + tmp[i][j - 1].rgbtRed +
                    tmp[i][j].rgbtRed + tmp[i][j + 1].rgbtRed;
                g = tmp[i - 1][j - 1].rgbtGreen + tmp[i - 1][j].rgbtGreen + tmp[i - 1][j + 1].rgbtGreen +
                    tmp[i][j - 1].rgbtGreen + tmp[i][j].rgbtGreen + tmp[i][j + 1].rgbtGreen;
                b = tmp[i - 1][j - 1].rgbtBlue + tmp[i - 1][j].rgbtBlue + tmp[i - 1][j + 1].rgbtBlue +
                    tmp[i][j - 1].rgbtBlue + tmp[i][j].rgbtBlue + tmp[i][j + 1].rgbtBlue;

                ar = average(r, 6);
                ag = average(g, 6);
                ab = average(b, 6);

                image[i][j].rgbtRed = ar;
                image[i][j].rgbtGreen = ag;
                image[i][j].rgbtBlue = ab;

                continue;
            }

            // Ordinary case
            if ((j > 0) && (j < width - 1) && (i > 0) && (i < height - 1))
            {
                r = tmp[i - 1][j - 1].rgbtRed + tmp[i - 1][j].rgbtRed + tmp[i - 1][j + 1].rgbtRed + tmp[i][j - 1].rgbtRed +
                    tmp[i][j].rgbtRed + tmp[i][j + 1].rgbtRed + tmp[i + 1][j - 1].rgbtRed + tmp[i + 1][j].rgbtRed +
                    tmp[i + 1][j + 1].rgbtRed;
                g = tmp[i - 1][j - 1].rgbtGreen + tmp[i - 1][j].rgbtGreen + tmp[i - 1][j + 1].rgbtGreen +
                    tmp[i][j - 1].rgbtGreen + tmp[i][j].rgbtGreen + tmp[i][j + 1].rgbtGreen + tmp[i + 1][j - 1].rgbtGreen +
                    tmp[i + 1][j].rgbtGreen + tmp[i + 1][j + 1].rgbtGreen;
                b = tmp[i - 1][j - 1].rgbtBlue + tmp[i - 1][j].rgbtBlue + tmp[i - 1][j + 1].rgbtBlue +
                    tmp[i][j - 1].rgbtBlue + tmp[i][j].rgbtBlue + tmp[i][j + 1].rgbtBlue + tmp[i + 1][j - 1].rgbtBlue +
                    tmp[i + 1][j].rgbtBlue + tmp[i + 1][j + 1].rgbtBlue;

                ar = average(r, 9);
                ag = average(g, 9);
                ab = average(b, 9);

                image[i][j].rgbtRed = ar;
                image[i][j].rgbtGreen = ag;
                image[i][j].rgbtBlue = ab;
            }
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // auxiliary array
    RGBTRIPLE tmp[height + 2][width + 2];

    // edges pixels
    RGBTRIPLE edge;

    // top and bottom edge of the image
    for (int j = 0; j < width + 2; j++)
    {
        tmp[0][j].rgbtRed = 0;
        tmp[0][j].rgbtGreen = 0;
        tmp[0][j].rgbtBlue = 0;

        tmp[height + 1][j].rgbtRed = 0;
        tmp[height + 1][j].rgbtGreen = 0;
        tmp[height + 1][j].rgbtBlue = 0;
    }

    // right and left edge of the image
    for (int i = 0; i < height + 2; i++)
    {
        tmp[i][0].rgbtRed = 0;
        tmp[i][0].rgbtGreen = 0;
        tmp[i][0].rgbtBlue = 0;

        tmp[i][width + 1].rgbtRed = 0;
        tmp[i][width + 1].rgbtGreen = 0;
        tmp[i][width + 1].rgbtBlue = 0;
    }

    // copy array image
    int i, j, k, l;
    for (i = 1, k = 0; i < height + 1; i++, k++)
    {
        for (j = 1, l = 0; j < width + 1; j++, l++)
        {
            tmp[i][j] = image[k][l];
        }
    }

    // putting the edges
    for (i = 1, k = 0; i < height + 1; i++, k++)
    {
        for (j = 1, l = 0; j < width + 1; j++, l++)
        {
            edge = edges_calc(height, width, i, j, tmp);
            image[k][l].rgbtRed = edge.rgbtRed;
            image[k][l].rgbtGreen = edge.rgbtGreen;
            image[k][l].rgbtBlue = edge.rgbtBlue;
        }
    }
    return;
}
