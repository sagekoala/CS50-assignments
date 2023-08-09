#include "helpers.h"
#include <math.h>
#include <stdio.h>

int calculate_red(int sepiaRed);
int calculate_green(int sepiaGreen);
int calculate_blue(int sepiaBlue);
int height_boundary_low(int i);
int height_boundary_upper(int i, int height);
int width_boundary_low(int j);
int width_boundary_upper(int j, int width);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Grayscale should take an image as input and create a black and white version as output
    // Note, can achieve this by making the RGB values equal (plan is to take average of the GBR values provided (in order to stay within the current brightness lever), and then set all BGR values to  that value)
    int average = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            average = round((float) ((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0));
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    /*
    sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
    sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
    sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue
    */

    int sepiaRed, sepiaGreen, sepiaBlue, originalRed, originalGreen, originalBlue = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            originalRed = image[i][j].rgbtRed;
            originalGreen = image[i][j].rgbtGreen;
            originalBlue = image[i][j].rgbtBlue;
            sepiaRed = round((float) 0.393 * originalRed + 0.769 * originalGreen + 0.189 * originalBlue);
            sepiaGreen = round((float) 0.349 * originalRed + 0.686 * originalGreen + 0.168 * originalBlue);
            sepiaBlue = round((float) 0.272 * originalRed + 0.534 * originalGreen + 0.131 * originalBlue);
            image[i][j].rgbtRed = calculate_red(sepiaRed);
            image[i][j].rgbtGreen = calculate_green(sepiaGreen);
            image[i][j].rgbtBlue = calculate_blue(sepiaBlue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Need to swap value at a given width index with the index at the opposite end of the row
    int temp_red, temp_green, temp_blue;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            {
                temp_red = image[i][j].rgbtRed;
                temp_green = image[i][j].rgbtGreen;
                temp_blue = image[i][j].rgbtBlue;
                image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
                image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
                image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
                image[i][width - j - 1].rgbtRed = temp_red;
                image[i][width - j - 1].rgbtGreen = temp_green;
                image[i][width - j - 1].rgbtBlue = temp_blue;
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Making a copy of the 2-d image array to read from
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    long sum_red = 0, sum_green = 0, sum_blue = 0;
    int ticker = 0, helow = 0, heup = 0, wilow = 0, wiup = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            helow = height_boundary_low(i);
            heup = height_boundary_upper(i, height);
            wilow = width_boundary_low(j);
            wiup = width_boundary_upper(j, width);

            for (int k = helow; k <= heup; k++)
            {
                for (int r = wilow; r <= wiup; r++)
                {
                        sum_red += copy[k][r].rgbtRed;
                        sum_green += copy[k][r].rgbtGreen;
                        sum_blue += copy[k][r].rgbtBlue;
                        ticker += 1;
                }
            }
            image[i][j].rgbtRed = (int) round((float) sum_red / ticker);
            image[i][j].rgbtGreen = (int) round((float) sum_green / ticker);
            image[i][j].rgbtBlue = (int) round((float) sum_blue / ticker);
            ticker = 0;
            sum_red = 0;
            sum_green = 0;
            sum_blue = 0;
        }
    }

    return;
}

int calculate_red(int sepiaRed)
{
    if (sepiaRed <= 255)
    {
        return sepiaRed;
    }
    else
    {
        return 255;
    }
}

int calculate_green(int sepiaGreen)
{
    if (sepiaGreen <= 255)
    {
        return sepiaGreen;
    }
    else
    {
        return 255;
    }
}

int calculate_blue(int sepiaBlue)
{
    if (sepiaBlue <= 255)
    {
        return sepiaBlue;
    }
    else
    {
        return 255;
    }
}

int height_boundary_low(int i)
{
    //
    if (i - 1 < 0)
    {
        return 0;
    }
    else
    {
        return i - 1;
    }
}
int height_boundary_upper(int i, int height)
{
    //
    if (i + 1 > height - 1)
    {
        return height - 1;
    }
    else
    {
        return i + 1;
    }
}
int width_boundary_low(int j)
{
    //
    if (j - 1 < 0)
    {
        return 0;
    }
    else
    {
        return j - 1;
    }
}
int width_boundary_upper(int j, int width)
{
    //
    if (j + 1 > width - 1)
    {
        return width - 1;
    }
    else
    {
        return j + 1;
    }
}
