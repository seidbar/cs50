#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


const int BLOCK_SIZE = 512;
int main(int argc, char *argv[])
{
    // User should give exactly one argument
    if (argc != 2)
    {
        printf("Usage: ./recover input\n");
        return 1;
    }

    // Prints an error message if the file is empty
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Define Block-Size = 512 Bytes, set the img property to NULL, 
    // instantiate a counter for the enumeration 
    // and a placeholder for a filename
    uint8_t block[BLOCK_SIZE];
    FILE *img = NULL;
    int i = 0;
    char filename[8] = "";

    // This loop reads in 512 blocks at a time and checks their properties
    // This assumes a FAT file system
    while (fread(block, 1, BLOCK_SIZE, input))
    {
        // If the beginning of the block fits the .jpeg criteria, we will start to recover that file
        if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] & 0xf0) == 0xe0)
        {
            if (img)
            {
                fclose(img);
                i++;
            }
            // Changes the filename to an appropriate number
            sprintf(filename, "%03i.jpg", i);
            img = fopen(filename, "w");
            fwrite(block, BLOCK_SIZE, 1, img);
        }
        else if (img) 
        {
            fwrite(block, BLOCK_SIZE, 1, img);
        }
    }
    fclose(img);
    fclose(input);
    return 0;
}
