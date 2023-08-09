#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BLOCK_SIZE 512
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Make sure there are enough arguments
    if (argc != 2)
    {
        printf("Usage: ./recover image");
        return 1;
    }

    // Open file, initialize character array for filename
    FILE *fptr = fopen(argv[1], "r");
    char filename[8];
    if (fptr == NULL)
    {
        printf("File did not open.");
        return 1;
    }

    // Initialize a buffer
    // fread() returns # of bytes successfully read, if equal to BLOCK_SIZE, it means that the end of the file
    // has not been reached yet so the while loop will continue
    BYTE buffer[BLOCK_SIZE];
    int count = 0;
    FILE *img;
    while (fread(&buffer, 1, BLOCK_SIZE, fptr) == BLOCK_SIZE)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xFF && (buffer[3] & 0xf0) == 0xe0)
        {
            if (count == 0)
            {
                sprintf(filename, "%03i.jpg", count);
                img = fopen(filename, "w");
                fwrite(&buffer, 1, BLOCK_SIZE, img);
                count++;
            }
            else
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", count);
                img = fopen(filename, "w");
                fwrite(&buffer, 1, BLOCK_SIZE, img);
                count++;
            }
        }
        else if (count == 0 || img == NULL)
        {
            continue;
        }
        else
        {
            fwrite(&buffer, 1, BLOCK_SIZE, img);
        }

    }

    // Always close files that you have opened
    fclose(fptr);
    fclose(img);
}