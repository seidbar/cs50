#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompts the user for a starter size
    int start;
    do 
    {
        start = get_int("What is the population size?\n");
    }
    while (start < 9);


    // Prompts the user for an end size
    int end = 0;
    do 
    {
        end = get_int("What is the desired population size?\n");
    }
    while (end < start);

    // Calculates the number of years to reach the desired population size
    int population = start;
    int years = 0;
    while (population < end) 
    {
        population = population + population / 3 - population / 4;
        years++;
    };

    // Prints the number of years needed
    printf("Years: %i", years);
}
