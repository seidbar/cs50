#include <stdio.h>
#include <cs50.h>

// Prints a pyramid
int main(void)
{
    // Prompts the user for a credit card number input
    long number = get_long_long("Credit Card Number: ");
    bool checksum = false;
    int sum = 0;
    int first = 0;
    int length = 0;

    // Loop to check each number
    do
    {
        // Finds the last digit of the number
        int sub = number % 10;

        // if it is every other digit, the digit gets multiplied by two
        if (checksum)
        {
            sub *= 2;

            // if the double of the digit makes two digits, they will be added
            if (sub > 9)
            {
                sum += sub % 10;
                sub /= 10;
                sum += sub % 10;
            }
            else
            {
                sum += sub;
            }
        }
        // all other numebrs are just added to the sum
        else
        {
            sum += sub;
        };

        // Checks for the first digit
        if (number < 100 && number > 10)
        {
            first = number;
        };

        number /= 10;
        checksum = !checksum;
        length++;
    }
    while (1 < number);

    // Checks if the card is valid, then which type it is.
    if (sum % 10 == 0)
    {
        if ((first == 34 || first == 37) && length == 15)
        {
            printf("AMEX\n");
        }
        else if (first > 50 && first < 56 && length == 16)
        {
            printf("MASTERCARD\n");
        }
        else if ((first / 10 == 4 && length == 13) || (first / 10 == 4 && length == 16))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}
