#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) // iterate through each pixel with nested for loops
    {
        for (int j = 0; j < width; j++)
        {
            double tot;
            double avg;

            double red = image[i][j].rgbtRed;
            double green = image[i][j].rgbtGreen;
            double blue = image[i][j].rgbtBlue;

            tot = red + green + blue;

            avg = tot / 3.00; // find average of all values in RGBTRIPLE struct


            // set each RGBT value in image equal to the average
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = round(avg);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++) // loop through image
        {
            // create variables to store old RGB values in image

            int old_red = image[i][j].rgbtRed;
            int old_green = image[i][j].rgbtGreen;
            int old_blue = image[i][j].rgbtBlue;

            int sep_red = round((0.393 * old_red) + (0.769 * old_green) + (0.189 * old_blue));
            int sep_green = round((0.349 * old_red) + (0.686 * old_green) + (0.168 * old_blue));
            int sep_blue = round((0.272 * old_red) + (0.534 * old_green) + (0.131 * old_blue));

            // set each pixel in image equal to sepia function result

            if (sep_red > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = sep_red;
            }

            if (sep_green > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = sep_green;
            }

            if (sep_blue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = sep_blue;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp; // create temporary RGBTRIPLE struct to store pixel

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++) // iterate through each row, but only half of columns (reflect around midpoint at width / 2)
        {
           temp = image[i][j];
           image[i][j] = image[i][width - (j + 1)];
           image[i][width - (j + 1)] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float avg_red;
    float avg_green;
    float avg_blue;

    RGBTRIPLE copy[height][width]; // create a RGBTRIPLE struct to store each processed pixel

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++) // iterate through each pixel
        {

            // using conditional statements, identify the location of the pixel (edge, corner, middle), and process
            // find average of each pixel, plus the pixels within one row/ column, then set the original pixel equal to average
            // store info in the temporary RGBTRIPLE struct


            // first, check corner and edge cases at i = 0 and j = 0
            if (i == 0 && j == 0)
            {
                avg_red = (image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 4.0;
                avg_green = (image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 4.0;
                avg_blue = (image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 4.0;



                copy[i][j].rgbtRed = round(avg_red);
                copy[i][j].rgbtGreen = round(avg_green);
                copy[i][j].rgbtBlue = round(avg_blue);

            }

            if ((i == 0) && (j != 0 && j != width - 1))
            {
                avg_red = (image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed +
                    image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 6.0;

                avg_green = (image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen +
                    image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 6.0;

                avg_blue = (image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue +
                    image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 6.0;

                copy[i][j].rgbtRed = round(avg_red);
                copy[i][j].rgbtGreen = round(avg_green);
                copy[i][j].rgbtBlue = round(avg_blue);
            }

            if ((i == 0) && (j == width - 1))
            {
                avg_red = (image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed) / 4.0;
                avg_green = (image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / 4.0;
                avg_blue = (image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / 4.0;

                copy[i][j].rgbtRed = round(avg_red);
                copy[i][j].rgbtGreen = round(avg_green);
                copy[i][j].rgbtBlue = round(avg_blue);
            }


            if ((i != 0 && i != height - 1) && (j == 0))
            {
                avg_red = (image[i - 1][j].rgbtRed + image[i][j].rgbtRed + image[i + 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed +
                    image[i][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed) / 6.0;

                avg_green = (image[i - 1][j].rgbtGreen + image[i][j].rgbtGreen + image[i + 1][j].rgbtGreen +
                    image[i - 1][j + 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 6.0;

                avg_blue = (image[i - 1][j].rgbtBlue + image[i][j].rgbtBlue + image[i + 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue +
                    image[i][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 6.0;

                copy[i][j].rgbtRed = round(avg_red);
                copy[i][j].rgbtGreen = round(avg_green);
                copy[i][j].rgbtBlue = round(avg_blue);
            }


            // check case where pixel is in the middle
            if ((i != 0 && i != height - 1) && (j != 0 && j != width - 1))
            {
                avg_red = (image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j - 1].rgbtRed +
                    image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed +
                        image[i + 1][j + 1].rgbtRed) / 9.0;

                avg_green = (image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen +
                    image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen +
                        image[i + 1][j + 1].rgbtGreen) / 9.0;

                avg_blue = (image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue +
                    image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue +
                        image[i + 1][j + 1].rgbtBlue) / 9.0;

                copy[i][j].rgbtRed = round(avg_red);
                copy[i][j].rgbtGreen = round(avg_green);
                copy[i][j].rgbtBlue = round(avg_blue);
            }


            // check cases on corner and edge where i = height - 1 and j = width - 1
            if ((i != 0 && i != height - 1) && (j == width - 1))
            {
                avg_red = (image[i - 1][j].rgbtRed + image[i][j].rgbtRed + image[i + 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed +
                    image[i][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed) / 6.0;

                avg_green = (image[i - 1][j].rgbtGreen + image[i][j].rgbtGreen + image[i + 1][j].rgbtGreen +
                    image[i - 1][j - 1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / 6.0;

                avg_blue = (image[i - 1][j].rgbtBlue + image[i][j].rgbtBlue + image[i + 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue +
                    image[i][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / 6.0;

                copy[i][j].rgbtRed = round(avg_red);
                copy[i][j].rgbtGreen = round(avg_green);
                copy[i][j].rgbtBlue = round(avg_blue);
            }

            if ((i == height - 1) && (j == 0))
            {
                avg_red = (image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed) / 4.0;
                avg_green = (image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / 4.0;
                avg_blue = (image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue) / 4.0;

                copy[i][j].rgbtRed = round(avg_red);
                copy[i][j].rgbtGreen = round(avg_green);
                copy[i][j].rgbtBlue = round(avg_blue);
            }

            if ((i == height - 1) && (j != 0 && j != width - 1))
            {
                avg_red = (image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j - 1].rgbtRed +
                    image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed) / 6.0;

                avg_green = (image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen +
                    image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / 6.0;

                avg_blue = (image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue +
                    image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue) / 6.0;

                copy[i][j].rgbtRed = round(avg_red);
                copy[i][j].rgbtGreen = round(avg_green);
                copy[i][j].rgbtBlue = round(avg_blue);
            }

            if ((i == height - 1) && (j == width - 1))
            {
                avg_red = (image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed) / 4.0;
                avg_green = (image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen) / 4.0;
                avg_blue = (image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue) / 4.0;

                copy[i][j].rgbtRed = round(avg_red);
                copy[i][j].rgbtGreen = round(avg_green);
                copy[i][j].rgbtBlue = round(avg_blue);
            }
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++) // iterate through each pixel in image a second time
        {
            //set each pixel in image equal to the pixel stored in the temporary RGBTRIPLE struct

            image[i][j].rgbtRed = copy[i][j].rgbtRed;
            image[i][j].rgbtGreen = copy[i][j].rgbtGreen;
            image[i][j].rgbtBlue = copy[i][j].rgbtBlue;
        }
    }

    return;
}