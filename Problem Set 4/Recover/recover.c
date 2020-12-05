
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image");
    }

    // Open the file
    FILE *file = fopen(argv[1], "r");

    //Check to be sure file is not null
    if (file == NULL)
    {
        return 1;
    }

    // Counter to track number of JPEGs found
    int img_count = 0;

    // Buffer for files to be read into
    BYTE buffer[512];

    //Variable to store JPEG file names
    char filename[8];

    // Pointer to files to write to
    FILE *img = NULL;

    // Bool variable to determine if file is already open
    bool open_file = false;


    // while loop to read through each 512 byte chunk of data in the card
    while (fread(buffer, 512, 1, file) == 1)
    {

        // Check for signature of JPEG file
        if (buffer[0] == 0xff && buffer[1]== 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {

            // If/ else statement to check for open files
            if (open_file == false)
            {
                sprintf(filename, "%03i.jpg", img_count); // Create a new file name
                img_count++; // Update the image counter
                img = fopen(filename, "w"); // Set img pointer to open file
                open_file = true; // Set bool value to true, indicating a file is now open
                fwrite(buffer, 512, 1, img); // Begin writing to the file
            }

            // If a file is, indeed, already open
            else
            {
                fclose(img); // Close the current open file, then initiate a new file.

                sprintf(filename, "%03i.jpg", img_count);
                img_count++;
                img = fopen(filename, "w");
                fwrite(buffer, 512, 1, img);
            }
        }

        // If signature not found
        else
        {

            // Check if file is open. If so, continue writing to open file
            if (open_file == true)
            {
                fwrite(buffer, 512, 1, img);
            }

            // If no file is open, no JPEG has been found. Keep reading card for JPEGs
            else if (open_file == false)
            {
                continue;
            }
        }
    }
    fclose(img);
    fclose(file);
    return 0;
}