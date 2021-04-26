#include "helpers.h"
#include <stdio.h>
#include <math.h>


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) 
    {
        for (int j = 0; j < width; j++) 
        {
            // Calculates the average and inserts it into every color
            int avg = round((image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3.0);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) 
    {
        for (int j = 0; j < width; j++) 
        {
            int orgRed = image[i][j].rgbtRed;
            int orgGreen = image[i][j].rgbtGreen;
            int orgBlue = image[i][j].rgbtBlue;

            // Finds the sepia value for every color
            int sepiaRed = round(0.393 * orgRed + 0.769 * orgGreen + 0.189 * orgBlue);
            int sepiaGreen = round(0.349 * orgRed +  0.686 * orgGreen + 0.168 * orgBlue);
            int sepiaBlue = round(0.272 * orgRed + 0.534 * orgGreen + 0.131 * orgBlue);

            image[i][j].rgbtBlue = sepiaBlue > 255 ? 255 : sepiaBlue;
            image[i][j].rgbtRed = sepiaRed > 255 ? 255 : sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen > 255 ? 255 : sepiaGreen;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Makes a copy to refer to
    for (int i = 0; i < height; i++) 
    {
        RGBTRIPLE row[width];
        for (int j = 0; j < width; j++) 
        {
            row[j] = image[i][j];
        }
        // Gets the opposite pixel for mirroring
        for (int k = 0; k < width; k++) 
        {
            image[i][k] = row[width - 1 - k];
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++) 
    {
        for (int j = 0; j < width; j++) 
        {
            copy[i][j] = image[i][j];
        }
    }

    // Select Row
    for (int i = 0; i < height; i++) 
    {
        // Select Pixel
        for (int j = 0; j < width; j++) 
        {
            // We create variables to store the pixel sums
            int blue = 0;
            int red = 0;
            int green = 0;
            // The counter keeps track of how many pixel values were added
            int count = 0;
            // Now we iterate over the 9 pixels that surround each pixel and add their values
            // The first value is to the left (-1) and up (-1)
            
            // Looping over rows -1 to +1
            for (int k = -1; k < 2; k++) 
            {
                // Looping over columns -1 to +1
                for (int l = -1; l < 2; l++) 
                {
                    if (i + k < 0 || i + k + 1 > height || j + l < 0 || j + l + 1 > width) 
                    {
                        continue;
                    }

                    blue += copy[i + k][j + l].rgbtBlue;
                    red += copy[i + k][j + l].rgbtRed;
                    green += copy[i + k][j + l].rgbtGreen;
                    count++;
                }
            }

            image[i][j].rgbtBlue = round(blue / (float) count);
            image[i][j].rgbtRed = round(red / (float) count);
            image[i][j].rgbtGreen = round(green / (float) count);
        }
    }

    return;
}
