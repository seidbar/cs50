#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

void calculate_score(int sentences, int words, int letters);

int main(void)
{
    // Get input sentence from user
    string text = get_string("Text: ");

    // declares variables for sentences, words and letters
    int sentences = 0;
    int words = 0;
    int letters = 0;

    // Loops over the text and checks what happens
    for (int i = 0; i < strlen(text); i++)
    {
        // Converts to upper to make a better comparison
        int letter = toupper(text[i]);
        if (letter >= 'A' && letter <= 'Z')
        {
            letters++;
        }
        else if (letter == ' ' && toupper(text[i - 1]) >= 'A' && toupper(text[i - 1]) <= 'Z')
        {
            words++;
        }
        else if (letter == ',' && toupper(text[i - 1]) >= 'A' && toupper(text[i - 1]) <= 'Z')
        {
            words++;
        }
        else if (letter == '.' || letter == '!' || letter == '?')
        {
            if (toupper(text[i - 1]) >= 'A' && toupper(text[i - 1]) <= 'Z')
            {
                sentences++;
                words++;
            }
        }
    }
    calculate_score(sentences, words, letters);
}

// Prints the grade
void calculate_score(int sentences, int words, int letters)
{
    //printf("S: %i, W: %i, L: %i", sentences, words, letters);
    // Converts to float
    float words_float = words * 1.0;
    float L = letters / words_float * 100.0;
    float S = sentences / words_float * 100.0;
    //printf("L: %f, S: %f", L, S);
    float grade = 0.0588 * L - 0.296 * S - 15.8;
    int grade_rounded = round(grade);
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade_rounded);
    }
}
