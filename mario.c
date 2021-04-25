#include <stdio.h>
#include <cs50.h>

// Prints a pyramid
int main(void)
{
    // Prompts the user for a height input
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);


    for (int i = 0; i < height; i++)
    {
        // This part of the loop handles the first half of the pyramid
        for (int j = height; j > 0; j--)
        {
            if (j <= i + 1)
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }

        // This creates the desired free block in the middle
        printf("  ");

        // This part handles the second half of the pyramid
        for (int k = 0; k < height; k++)
        {
            if (k > i)
            {
                printf("");
            }
            else
            {
                printf("#");
            }
        }
        printf("\n");
    }
}
