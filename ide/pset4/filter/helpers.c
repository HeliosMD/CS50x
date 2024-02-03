#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Scans the whole image
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            // Promediates three components to a gray component
            float gray = round((image[y][x].rgbtBlue + image[y][x].rgbtGreen + image[y][x].rgbtRed) / 3.0);

            // Stores gray component into Red, Green and Blue components
            image[y][x].rgbtBlue = gray;
            image[y][x].rgbtGreen = gray;
            image[y][x].rgbtRed = gray;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Allocates enough memory for a temporary row
    RGBTRIPLE tmp_image[width];

    // Scans the whole image
    for (int y = 0; y < height; y++)
    {
        // Scans each row and stores it backwards into a temporary row
        for (int x = 0; x < width; x++)
        {
            // Reflects each pixels in a row to the temporary row
            tmp_image[width - x - 1] = image[y][x];
        }

        for (int x = 0; x < width; x++)
        {
            // Reflects each pixels in a row from the temporary image
            image[y][x] = tmp_image[x];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Declares a temporary image
    RGBTRIPLE tmp_image[height][width];

    // Scans the whole image promediating matricially
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            BYTE c = (y - 1 < 0) * 1 + (x - 1 < 0) * 2 + (y + 1 == height) * 4 + (x + 1 == width) * 8;
            if (c == 3)
            {
                // Top Left corner case
                // Promediates each component with a 2x2 matrix

                float tmp_red = round((image[y][x].rgbtRed + image[y][x + 1].rgbtRed
                                       + image[y + 1][x].rgbtRed + image[y + 1][x + 1].rgbtRed) / 4.0);

                tmp_image[y][x].rgbtRed = tmp_red;

                float tmp_green = round((image[y][x].rgbtGreen + image[y][x + 1].rgbtGreen
                                         + image[y + 1][x].rgbtGreen + image[y + 1][x + 1].rgbtGreen) / 4.0);

                tmp_image[y][x].rgbtGreen = tmp_green;

                float tmp_blue = round((image[y][x].rgbtBlue + image[y][x + 1].rgbtBlue
                                        + image[y + 1][x].rgbtBlue + image[y + 1][x + 1].rgbtBlue) / 4.0);

                tmp_image[y][x].rgbtBlue = tmp_blue;
            }
            if (c == 9)
            {
                // Top Right corner case
                // Promediates each component with a 2x2 matrix

                float tmp_red = round((image[y][x - 1].rgbtRed + image[y][x].rgbtRed
                                       + image[y + 1][x - 1].rgbtRed + image[y + 1][x].rgbtRed) / 4.0);

                tmp_image[y][x].rgbtRed = tmp_red;

                float tmp_green = round((image[y][x - 1].rgbtGreen + image[y][x].rgbtGreen
                                         + image[y + 1][x - 1].rgbtGreen + image[y + 1][x].rgbtGreen) / 4.0);

                tmp_image[y][x].rgbtGreen = tmp_green;

                float tmp_blue = round((image[y][x - 1].rgbtBlue + image[y][x].rgbtBlue
                                        + image[y + 1][x - 1].rgbtBlue + image[y + 1][x].rgbtBlue) / 4.0);

                tmp_image[y][x].rgbtBlue = tmp_blue;
            }
            if (c == 6)
            {
                // Bottom Left corner case
                // Promediates each component with a 2x2 matrix

                float tmp_red = round((image[y - 1][x].rgbtRed + image[y - 1][x + 1].rgbtRed
                                       + image[y][x].rgbtRed + image[y][x + 1].rgbtRed) / 4.0);

                tmp_image[y][x].rgbtRed = tmp_red;

                float tmp_green = round((image[y - 1][x].rgbtGreen + image[y - 1][x + 1].rgbtGreen
                                         + image[y][x].rgbtGreen + image[y][x + 1].rgbtGreen) / 4.0);

                tmp_image[y][x].rgbtGreen = tmp_green;

                float tmp_blue = round((image[y - 1][x].rgbtBlue + image[y - 1][x + 1].rgbtBlue
                                        + image[y][x].rgbtBlue + image[y][x + 1].rgbtBlue) / 4.0);

                tmp_image[y][x].rgbtBlue = tmp_blue;
            }
            if (c == 12)
            {
                // Bottom Right corner case
                // Promediates each component with a 2x2 matrix

                float tmp_red = round((image[y - 1][x - 1].rgbtRed + image[y - 1][x].rgbtRed
                                       + image[y][x - 1].rgbtRed + image[y][x].rgbtRed) / 4.0);

                tmp_image[y][x].rgbtRed = tmp_red;

                float tmp_green = round((image[y - 1][x - 1].rgbtGreen + image[y - 1][x].rgbtGreen
                                         + image[y][x - 1].rgbtGreen + image[y][x].rgbtGreen) / 4.0);

                tmp_image[y][x].rgbtGreen = tmp_green;

                float tmp_blue = round((image[y - 1][x - 1].rgbtBlue + image[y - 1][x].rgbtBlue
                                        + image[y][x - 1].rgbtBlue + image[y][x].rgbtBlue) / 4.0);

                tmp_image[y][x].rgbtBlue = tmp_blue;
            }
            if (c == 1)
            {
                // Top border line case
                // Promediates each component with a 3x2 matrix

                float tmp_red = round((image[y][x - 1].rgbtRed + image[y][x].rgbtRed + image[y][x + 1].rgbtRed
                                       + image[y + 1][x - 1].rgbtRed + image[y + 1][x].rgbtRed + image[y + 1][x + 1].rgbtRed) / 6.0);

                tmp_image[y][x].rgbtRed = tmp_red;

                float tmp_green = round((image[y][x - 1].rgbtGreen + image[y][x].rgbtGreen + image[y][x + 1].rgbtGreen
                                         + image[y + 1][x - 1].rgbtGreen + image[y + 1][x].rgbtGreen + image[y + 1][x + 1].rgbtGreen) / 6.0);

                tmp_image[y][x].rgbtGreen = tmp_green;

                float tmp_blue = round((image[y][x - 1].rgbtBlue + image[y][x].rgbtBlue + image[y][x + 1].rgbtBlue
                                        + image[y + 1][x - 1].rgbtBlue + image[y + 1][x].rgbtBlue + image[y + 1][x + 1].rgbtBlue) / 6.0);

                tmp_image[y][x].rgbtBlue = tmp_blue;
            }
            if (c == 2)
            {
                // Left border line case
                // Promediates each component with a 2x3 matrix

                float tmp_red = round((image[y - 1][x].rgbtRed + image[y - 1][x + 1].rgbtRed
                                       + image[y][x].rgbtRed + image[y][x + 1].rgbtRed
                                       + image[y + 1][x].rgbtRed + image[y + 1][x + 1].rgbtRed) / 6.0);

                tmp_image[y][x].rgbtRed = tmp_red;


                float tmp_green = round((image[y - 1][x].rgbtGreen + image[y - 1][x + 1].rgbtGreen
                                         + image[y][x].rgbtGreen + image[y][x + 1].rgbtGreen
                                         + image[y + 1][x].rgbtGreen + image[y + 1][x + 1].rgbtGreen) / 6.0);

                tmp_image[y][x].rgbtGreen = tmp_green;

                float tmp_blue = round((image[y - 1][x].rgbtBlue + image[y - 1][x + 1].rgbtBlue
                                        + image[y][x].rgbtBlue + image[y][x + 1].rgbtBlue
                                        + image[y + 1][x].rgbtBlue + image[y + 1][x + 1].rgbtBlue) / 6.0);

                tmp_image[y][x].rgbtBlue = tmp_blue;
            }
            if (c == 8)
            {
                // Right border line case
                // Promediates each component with a 2x3 matrix

                float tmp_red = round((image[y - 1][x - 1].rgbtRed + image[y - 1][x].rgbtRed
                                       + image[y][x - 1].rgbtRed + image[y][x].rgbtRed
                                       + image[y + 1][x - 1].rgbtRed + image[y + 1][x].rgbtRed) / 6.0);

                tmp_image[y][x].rgbtRed = tmp_red;

                float tmp_green = round((image[y - 1][x - 1].rgbtGreen + image[y - 1][x].rgbtGreen
                                         + image[y][x - 1].rgbtGreen + image[y][x].rgbtGreen
                                         + image[y + 1][x - 1].rgbtGreen + image[y + 1][x].rgbtGreen) / 6.0);

                tmp_image[y][x].rgbtGreen = tmp_green;

                float tmp_blue = round((image[y - 1][x - 1].rgbtBlue + image[y - 1][x].rgbtBlue
                                        + image[y][x - 1].rgbtBlue + image[y][x].rgbtBlue
                                        + image[y + 1][x - 1].rgbtBlue + image[y + 1][x].rgbtBlue) / 6.0);

                tmp_image[y][x].rgbtBlue = tmp_blue;
            }
            if (c == 4)
            {
                // Bottom border line case
                // Promediates each component with a 3x2 matrix

                float tmp_red = round((image[y - 1][x - 1].rgbtRed + image[y - 1][x].rgbtRed + image[y - 1][x + 1].rgbtRed
                                       + image[y][x - 1].rgbtRed + image[y][x].rgbtRed + image[y][x + 1].rgbtRed) / 6.0);

                tmp_image[y][x].rgbtRed = tmp_red;

                float tmp_green = round((image[y - 1][x - 1].rgbtGreen + image[y - 1][x].rgbtGreen + image[y - 1][x + 1].rgbtGreen
                                         + image[y][x - 1].rgbtGreen + image[y][x].rgbtGreen + image[y][x + 1].rgbtGreen) / 6.0);

                tmp_image[y][x].rgbtGreen = tmp_green;

                float tmp_blue = round((image[y - 1][x - 1].rgbtBlue + image[y - 1][x].rgbtBlue + image[y - 1][x + 1].rgbtBlue
                                        + image[y][x - 1].rgbtBlue + image[y][x].rgbtBlue + image[y][x + 1].rgbtBlue) / 6.0);

                tmp_image[y][x].rgbtBlue = tmp_blue;
            }
            else if (c == 0)
            {
                // Rest of cases
                // Promediates each component with a 3x3 matrix

                float tmp_red = round((image[y - 1][x - 1].rgbtRed + image[y - 1][x].rgbtRed + image[y - 1][x + 1].rgbtRed
                                       + image[y][x - 1].rgbtRed + image[y][x].rgbtRed + image[y][x + 1].rgbtRed
                                       + image[y + 1][x - 1].rgbtRed + image[y + 1][x].rgbtRed + image[y + 1][x + 1].rgbtRed) / 9.0);

                tmp_image[y][x].rgbtRed = tmp_red;

                float tmp_green = round((image[y - 1][x - 1].rgbtGreen + image[y - 1][x].rgbtGreen + image[y - 1][x + 1].rgbtGreen
                                         + image[y][x - 1].rgbtGreen + image[y][x].rgbtGreen + image[y][x + 1].rgbtGreen
                                         + image[y + 1][x - 1].rgbtGreen + image[y + 1][x].rgbtGreen + image[y + 1][x + 1].rgbtGreen) / 9.0);

                tmp_image[y][x].rgbtGreen = tmp_green;

                float tmp_blue = round((image[y - 1][x - 1].rgbtBlue + image[y - 1][x].rgbtBlue + image[y - 1][x + 1].rgbtBlue
                                        + image[y][x - 1].rgbtBlue + image[y][x].rgbtBlue + image[y][x + 1].rgbtBlue
                                        + image[y + 1][x - 1].rgbtBlue + image[y + 1][x].rgbtBlue + image[y + 1][x + 1].rgbtBlue) / 9.0);

                tmp_image[y][x].rgbtBlue = tmp_blue;
            }
        }
    }
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            image[y][x].rgbtRed = tmp_image[y][x].rgbtRed;
            image[y][x].rgbtGreen = tmp_image[y][x].rgbtGreen;
            image[y][x].rgbtBlue = tmp_image[y][x].rgbtBlue;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Declares a temporary image
    RGBTRIPLE tmp_image[height][width];

    float gx_red;
    float gx_green;
    float gx_blue;

    float gy_red;
    float gy_green;
    float gy_blue;

    // Scans the whole image processing matricially

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            BYTE c = (y - 1 < 0) * 1 + (x - 1 < 0) * 2 + (y + 1 == height) * 4 + (x + 1 == width) * 8;
            if (c == 3)
            {
                // Top Left corner case

                // Sums Gx with a 2x2 matrix for each component

                gx_red = round(image[y][x].rgbtRed * 0 + image[y][x + 1].rgbtRed * 2
                               + image[y + 1][x].rgbtRed * 0 + image[y + 1][x + 1].rgbtRed * 1);

                gx_green = round(image[y][x].rgbtGreen * 0 + image[y][x + 1].rgbtGreen * 2
                                 + image[y + 1][x].rgbtGreen * 0 + image[y + 1][x + 1].rgbtGreen * 1);

                gx_blue = round(image[y][x].rgbtBlue * 0 + image[y][x + 1].rgbtBlue * 2
                                + image[y + 1][x].rgbtBlue * 0 + image[y + 1][x + 1].rgbtBlue * 1);

                // Sums Gy with a 2x2 matrix for each component

                gy_red = round(image[y][x].rgbtRed * 0 + image[y][x + 1].rgbtRed * 0
                               + image[y + 1][x].rgbtRed * 2 + image[y + 1][x + 1].rgbtRed * 1);

                gy_green = round(image[y][x].rgbtGreen * 0 + image[y][x + 1].rgbtGreen * 0
                                 + image[y + 1][x].rgbtGreen * 2 + image[y + 1][x + 1].rgbtGreen * 1);

                gy_blue = round(image[y][x].rgbtBlue * 0 + image[y][x + 1].rgbtBlue * 0
                                + image[y + 1][x].rgbtBlue * 2 + image[y + 1][x + 1].rgbtBlue * 1);

            }
            if (c == 9)
            {
                // Top Right corner case
                // Sums Gx with a 2x2 matrix for each component

                gx_red = round(image[y][x - 1].rgbtRed * -2 + image[y][x].rgbtRed * 0
                               + image[y + 1][x - 1].rgbtRed * -1 + image[y + 1][x].rgbtRed * 0);

                gx_green = round(image[y][x - 1].rgbtGreen * -2 + image[y][x].rgbtGreen * 0
                                 + image[y + 1][x - 1].rgbtGreen * -1 + image[y + 1][x].rgbtGreen * 0);

                gx_blue = round(image[y][x - 1].rgbtBlue * -2 + image[y][x].rgbtBlue * 0
                                + image[y + 1][x - 1].rgbtBlue * -1 + image[y + 1][x].rgbtBlue * 0);

                // Sums Gy with a 2x2 matrix for each component

                gy_red = round(image[y][x - 1].rgbtRed * 0 + image[y][x].rgbtRed * 0
                               + image[y + 1][x - 1].rgbtRed * 1 + image[y + 1][x].rgbtRed * 2);

                gy_green = round(image[y][x - 1].rgbtGreen * 0 + image[y][x].rgbtGreen * 0
                                 + image[y + 1][x - 1].rgbtGreen * 1 + image[y + 1][x].rgbtGreen * 2);

                gy_blue = round(image[y][x - 1].rgbtBlue * 0 + image[y][x].rgbtBlue * 0
                                + image[y + 1][x - 1].rgbtBlue * 1 + image[y + 1][x].rgbtBlue * 2);

            }
            if (c == 6)
            {
                // Bottom Left corner case
                // Sums Gx with a 2x2 matrix for each component

                gx_red = round(image[y - 1][x].rgbtRed * 0 + image[y - 1][x + 1].rgbtRed * 1
                               + image[y][x].rgbtRed * 0 + image[y][x + 1].rgbtRed * 2);

                gx_green = round(image[y - 1][x].rgbtGreen * 0 + image[y - 1][x + 1].rgbtGreen * 1
                                 + image[y][x].rgbtGreen * 0 + image[y][x + 1].rgbtGreen * 2);

                gx_blue = round(image[y - 1][x].rgbtBlue * 0 + image[y - 1][x + 1].rgbtBlue * 1
                                + image[y][x].rgbtBlue * 0 + image[y][x + 1].rgbtBlue * 2);

                // Sums Gy with a 2x2 matrix for each component

                gy_red = round(image[y - 1][x].rgbtRed * -2 + image[y - 1][x + 1].rgbtRed * -1
                               + image[y][x].rgbtRed * 0 + image[y][x + 1].rgbtRed * 0);

                gy_green = round(image[y - 1][x].rgbtGreen * -2 + image[y - 1][x + 1].rgbtGreen * -1
                                 + image[y][x].rgbtGreen * 0 + image[y][x + 1].rgbtGreen * 0);

                gy_blue = round(image[y - 1][x].rgbtBlue * -2 + image[y - 1][x + 1].rgbtBlue * -1
                                + image[y][x].rgbtBlue * 0 + image[y][x + 1].rgbtBlue * 0);

            }
            if (c == 12)
            {
                // Bottom Right corner case
                // Sums Gx with a 2x2 matrix for each component

                gx_red = round(image[y - 1][x - 1].rgbtRed * -1 + image[y - 1][x].rgbtRed * 0
                               + image[y][x - 1].rgbtRed * -2 + image[y][x].rgbtRed * 0);

                gx_green = round(image[y - 1][x - 1].rgbtGreen * -1 + image[y - 1][x].rgbtGreen * 0
                                 + image[y][x - 1].rgbtGreen * -2 + image[y][x].rgbtGreen * 0);

                gx_blue = round(image[y - 1][x - 1].rgbtBlue * -1 + image[y - 1][x].rgbtBlue * 0
                                + image[y][x - 1].rgbtBlue * -2 + image[y][x].rgbtBlue * 0);

                // Sums Gy with a 2x2 matrix for each component

                gy_red = round(image[y - 1][x - 1].rgbtRed * -1 + image[y - 1][x].rgbtRed * -2
                               + image[y][x - 1].rgbtRed * 0 + image[y][x].rgbtRed * 0);

                gy_green = round(image[y - 1][x - 1].rgbtGreen * -1 + image[y - 1][x].rgbtGreen * -2
                                 + image[y][x - 1].rgbtGreen * 0 + image[y][x].rgbtGreen * 0);

                gy_blue = round(image[y - 1][x - 1].rgbtBlue * -1 + image[y - 1][x].rgbtBlue * -2
                                + image[y][x - 1].rgbtBlue * 0 + image[y][x].rgbtBlue * 0);

            }
            if (c == 1)
            {
                // Top border line case
                // Sums Gx with a 2x3 matrix for each component

                gx_red = round(image[y][x - 1].rgbtRed * -2 + image[y][x].rgbtRed * 0 + image[y][x + 1].rgbtRed * 2
                               + image[y + 1][x - 1].rgbtRed * -1 + image[y + 1][x].rgbtRed * 0 + image[y + 1][x + 1].rgbtRed * 1);

                gx_green = round(image[y][x - 1].rgbtGreen * -2 + image[y][x].rgbtGreen * 0 + image[y][x + 1].rgbtGreen * 2
                                 + image[y + 1][x - 1].rgbtGreen * -1 + image[y + 1][x].rgbtGreen * 0 + image[y + 1][x + 1].rgbtGreen * 1);

                gx_blue = round(image[y][x - 1].rgbtBlue * -2 + image[y][x].rgbtBlue * 0 + image[y][x + 1].rgbtBlue * 2
                                + image[y + 1][x - 1].rgbtBlue * -1 + image[y + 1][x].rgbtBlue * 0 + image[y + 1][x + 1].rgbtBlue * 1);

                // Sums Gy with a 2x3 matrix for each component

                gy_red = round(image[y][x - 1].rgbtRed * 0 + image[y][x].rgbtRed * 0 + image[y][x + 1].rgbtRed * 0
                               + image[y + 1][x - 1].rgbtRed * 1 + image[y + 1][x].rgbtRed * 2 + image[y + 1][x + 1].rgbtRed * 1);

                gy_green = round(image[y][x - 1].rgbtGreen * 0 + image[y][x].rgbtGreen * 0 + image[y][x + 1].rgbtGreen * 0
                                 + image[y + 1][x - 1].rgbtGreen * 1 + image[y + 1][x].rgbtGreen * 2 + image[y + 1][x + 1].rgbtGreen * 1);

                gy_blue = round(image[y][x - 1].rgbtBlue * 0 + image[y][x].rgbtBlue * 0 + image[y][x + 1].rgbtBlue * 0
                                + image[y + 1][x - 1].rgbtBlue * 1 + image[y + 1][x].rgbtBlue * 2 + image[y + 1][x + 1].rgbtBlue * 1);

            }
            if (c == 2)
            {
                // Left border line case
                // Sums Gx with a 3x2 matrix for each component

                gx_red = round(image[y - 1][x].rgbtRed * 0 + image[y - 1][x + 1].rgbtRed * 1
                               + image[y][x].rgbtRed * 0 + image[y][x + 1].rgbtRed * 2
                               + image[y + 1][x].rgbtRed * 0 + image[y + 1][x + 1].rgbtRed * 1);

                gx_green = round(image[y - 1][x].rgbtGreen * 0 + image[y - 1][x + 1].rgbtGreen * 1
                                 + image[y][x].rgbtGreen * 0 + image[y][x + 1].rgbtGreen * 2
                                 + image[y + 1][x].rgbtGreen * 0 + image[y + 1][x + 1].rgbtGreen * 1);

                gx_blue = round(image[y - 1][x].rgbtBlue * 0 + image[y - 1][x + 1].rgbtBlue * 1
                                + image[y][x].rgbtBlue * 0 + image[y][x + 1].rgbtBlue * 2
                                + image[y + 1][x].rgbtBlue * 0 + image[y + 1][x + 1].rgbtBlue * 1);

                // Sums Gy with a 3x2 matrix for each component

                gy_red = round(image[y - 1][x].rgbtRed * -2 + image[y - 1][x + 1].rgbtRed * -1
                               + image[y][x].rgbtRed * 0 + image[y][x + 1].rgbtRed * 0
                               + image[y + 1][x].rgbtRed * 2 + image[y + 1][x + 1].rgbtRed * 1);

                gy_green = round(image[y - 1][x].rgbtGreen * -2 + image[y - 1][x + 1].rgbtGreen * -1
                                 + image[y][x].rgbtGreen * 0 + image[y][x + 1].rgbtGreen * 0
                                 + image[y + 1][x].rgbtGreen * 2 + image[y + 1][x + 1].rgbtGreen * 1);

                gy_blue = round(image[y - 1][x].rgbtBlue * -2 + image[y - 1][x + 1].rgbtBlue * -1
                                + image[y][x].rgbtBlue * 0 + image[y][x + 1].rgbtBlue * 0
                                + image[y + 1][x].rgbtBlue * 2 + image[y + 1][x + 1].rgbtBlue * 1);

            }
            if (c == 8)
            {
                // Right border line case
                // Sums Gx with a 3x2 matrix for each component

                gx_red = round(image[y - 1][x - 1].rgbtRed * -1 + image[y - 1][x].rgbtRed * 0
                               + image[y][x - 1].rgbtRed * -2 + image[y][x].rgbtRed * 0
                               + image[y + 1][x - 1].rgbtRed * -1 + image[y + 1][x].rgbtRed * 0);

                gx_green = round(image[y - 1][x - 1].rgbtGreen * -1 + image[y - 1][x].rgbtGreen * 0
                                 + image[y][x - 1].rgbtGreen * -2 + image[y][x].rgbtGreen * 0
                                 + image[y + 1][x - 1].rgbtGreen * -1 + image[y + 1][x].rgbtGreen * 0);

                gx_blue = round(image[y - 1][x - 1].rgbtBlue * -1 + image[y - 1][x].rgbtBlue * 0
                                + image[y][x - 1].rgbtBlue * -2 + image[y][x].rgbtBlue * 0
                                + image[y + 1][x - 1].rgbtBlue * -1 + image[y + 1][x].rgbtBlue * 0);

                // Sums Gy with a 3x2 matrix for each component

                gy_red = round(image[y - 1][x - 1].rgbtRed * -1 + image[y - 1][x].rgbtRed * -2
                               + image[y][x - 1].rgbtRed * 0 + image[y][x].rgbtRed * 0
                               + image[y + 1][x - 1].rgbtRed * 1 + image[y + 1][x].rgbtRed * 2);

                gy_green = round(image[y - 1][x - 1].rgbtGreen * -1 + image[y - 1][x].rgbtGreen * -2
                                 + image[y][x - 1].rgbtGreen * 0 + image[y][x].rgbtGreen * 0
                                 + image[y + 1][x - 1].rgbtGreen * 1 + image[y + 1][x].rgbtGreen * 2);

                gy_blue = round(image[y - 1][x - 1].rgbtBlue * -1 + image[y - 1][x].rgbtBlue * -2
                                + image[y][x - 1].rgbtBlue * 0 + image[y][x].rgbtBlue * 0
                                + image[y + 1][x - 1].rgbtBlue * 1 + image[y + 1][x].rgbtBlue * 2);

            }
            if (c == 4)
            {
                // Bottom border line case
                // Sums Gx with a 2x3 matrix for each component

                gx_red = round(image[y - 1][x - 1].rgbtRed * -1 + image[y - 1][x].rgbtRed * 0 + image[y - 1][x + 1].rgbtRed * 1
                               + image[y][x - 1].rgbtRed * -2 + image[y][x].rgbtRed * 0 + image[y][x + 1].rgbtRed * 2);

                gx_green = round(image[y - 1][x - 1].rgbtGreen * -1 + image[y - 1][x].rgbtGreen * 0 + image[y - 1][x + 1].rgbtGreen * 1
                                 + image[y][x - 1].rgbtGreen * -2 + image[y][x].rgbtGreen * 0 + image[y][x + 1].rgbtGreen * 2);

                gx_blue = round(image[y - 1][x - 1].rgbtBlue * -1 + image[y - 1][x].rgbtBlue * 0 + image[y - 1][x + 1].rgbtBlue * 1
                                + image[y][x - 1].rgbtBlue * -2 + image[y][x].rgbtBlue * 0 + image[y][x + 1].rgbtBlue * 2);

                // Sums Gy with a 2x3 matrix for each component

                gy_red = round(image[y - 1][x - 1].rgbtRed * -1 + image[y - 1][x].rgbtRed * -2 + image[y - 1][x + 1].rgbtRed * -1
                               + image[y][x - 1].rgbtRed * 0 + image[y][x].rgbtRed * 0 + image[y][x + 1].rgbtRed * 0);

                gy_green = round(image[y - 1][x - 1].rgbtGreen * -1 + image[y - 1][x].rgbtGreen * -2 + image[y - 1][x + 1].rgbtGreen * -1
                                 + image[y][x - 1].rgbtGreen * 0 + image[y][x].rgbtGreen * 0 + image[y][x + 1].rgbtGreen * 0);

                gy_blue = round(image[y - 1][x - 1].rgbtBlue * -1 + image[y - 1][x].rgbtBlue * -2 + image[y - 1][x + 1].rgbtBlue * -1
                                + image[y][x - 1].rgbtBlue * 0 + image[y][x].rgbtBlue * 0 + image[y][x + 1].rgbtBlue * 0);
            }
            if (c == 0)
            {
                // Sums Gx with a 3x3 matrix for each component

                gx_red = round(image[y - 1][x - 1].rgbtRed * -1 + image[y - 1][x].rgbtRed * 0 + image[y - 1][x + 1].rgbtRed * 1
                               + image[y][x - 1].rgbtRed * -2 + image[y][x].rgbtRed * 0 + image[y][x + 1].rgbtRed * 2
                               + image[y + 1][x - 1].rgbtRed * -1 + image[y + 1][x].rgbtRed * 0 + image[y + 1][x + 1].rgbtRed * 1);

                gx_green = round(image[y - 1][x - 1].rgbtGreen * -1 + image[y - 1][x].rgbtGreen * 0 + image[y - 1][x + 1].rgbtGreen * 1
                                 + image[y][x - 1].rgbtGreen * -2 + image[y][x].rgbtGreen * 0 + image[y][x + 1].rgbtGreen * 2
                                 + image[y + 1][x - 1].rgbtGreen * -1 + image[y + 1][x].rgbtGreen * 0 + image[y + 1][x + 1].rgbtGreen * 1);

                gx_blue = round(image[y - 1][x - 1].rgbtBlue * -1 + image[y - 1][x].rgbtBlue * 0 + image[y - 1][x + 1].rgbtBlue * 1
                                + image[y][x - 1].rgbtBlue * -2 + image[y][x].rgbtBlue * 0 + image[y][x + 1].rgbtBlue * 2
                                + image[y + 1][x - 1].rgbtBlue * -1 + image[y + 1][x].rgbtBlue * 0 + image[y + 1][x + 1].rgbtBlue * 1);

                // Sums Gy with a 3x3 matrix for each component

                gy_red = round(image[y - 1][x - 1].rgbtRed * -1 + image[y - 1][x].rgbtRed * -2 + image[y - 1][x + 1].rgbtRed * -1
                               + image[y][x - 1].rgbtRed * 0 + image[y][x].rgbtRed * 0 + image[y][x + 1].rgbtRed * 0
                               + image[y + 1][x - 1].rgbtRed * 1 + image[y + 1][x].rgbtRed * 2 + image[y + 1][x + 1].rgbtRed * 1);

                gy_green = round(image[y - 1][x - 1].rgbtGreen * -1 + image[y - 1][x].rgbtGreen * -2 + image[y - 1][x + 1].rgbtGreen * -1
                                 + image[y][x - 1].rgbtGreen * 0 + image[y][x].rgbtGreen * 0 + image[y][x + 1].rgbtGreen * 0
                                 + image[y + 1][x - 1].rgbtGreen * 1 + image[y + 1][x].rgbtGreen * 2 + image[y + 1][x + 1].rgbtGreen * 1);

                gy_blue = round(image[y - 1][x - 1].rgbtBlue * -1 + image[y - 1][x].rgbtBlue * -2 + image[y - 1][x + 1].rgbtBlue * -1
                                + image[y][x - 1].rgbtBlue * 0 + image[y][x].rgbtBlue * 0 + image[y][x + 1].rgbtBlue * 0
                                + image[y + 1][x - 1].rgbtBlue * 1 + image[y + 1][x].rgbtBlue * 2 + image[y + 1][x + 1].rgbtBlue * 1);
            }

            // Calculates Sobel operator for each component
            float op_red = round(sqrt(pow(gx_red, 2) + pow(gy_red, 2)));
            float op_green = round(sqrt(pow(gx_green, 2) + pow(gy_green, 2)));
            float op_blue = round(sqrt(pow(gx_blue, 2) + pow(gy_blue, 2)));

            if (op_red > 255)
            {
                op_red = 255;
            }

            if (op_green > 255)
            {
                op_green = 255;
            }

            if (op_blue > 255)
            {
                op_blue = 255;
            }

            tmp_image[y][x].rgbtRed = op_red;
            tmp_image[y][x].rgbtGreen = op_green;
            tmp_image[y][x].rgbtBlue = op_blue;
        }
    }
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            image[y][x].rgbtRed = tmp_image[y][x].rgbtRed;
            image[y][x].rgbtGreen = tmp_image[y][x].rgbtGreen;
            image[y][x].rgbtBlue = tmp_image[y][x].rgbtBlue;
        }
    }
    return;
}
