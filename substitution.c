#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

int cipher_text(string input, string cipher);
int validate_key(string key);

int main(int argc, string argv[])
{
    // Only accepts one single string as arguments
    if (argc == 2)
    {
        int return_code = validate_key(argv[1]);
        if (return_code == 0) 
        {
            // Get input sentence from user
            string text = get_string("plaintext: ");
            int output = cipher_text(text, argv[1]);
            return output;
        }

        // If the key is invalid the return_code is returned
        return return_code;
    }

    // If the amount of arguments is incorrect, the user is reminded of the right usage
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
}


int validate_key(string key)
{
    // String has to contain 26 characters
    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else 
    {
        // Checksum checks if every letter is contained exactly once
        int checksum = 0;
        for (int i = 0; i < strlen(key); i++) 
        {
            if (isalpha(key[i])) 
            {
                int letter = toupper(key[i]);
                checksum += letter;
            }
            else 
            {
                printf("Key must only contain letters.\n");
                return 1;
            }
        }
        // If the checksum is correct, we can roll
        if (checksum == 2015) 
        {
            return 0;
        } 
        else 
        {
            printf("Key must contain every letter exactly once.\n");
            return 1;
        }
    }
}


int cipher_text(string input, string cipher)
{
    printf("ciphertext: ");
    for (int i = 0; i < strlen(input); i++) 
    {
        int letter = input[i];
        // Only changes letters and leaves the rest like the input
        if (letter < 'A' || (letter > 'Z' && letter < 'a') || letter > 'z')
        {
            printf("%c", input[i]);
        }
        // Checks if it is a capitalized letter
        else if (letter < 'a')
        {
            printf("%c", toupper(cipher[input[i] - 65]));
        }
        // Otherwise it must be a small letter.
        else
        {
            printf("%c", tolower(cipher[input[i] - 97]));
        }
    }
    printf("\n");
    return 0;
};
