// Include necessary libraries
#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Declare prototypes
int count_letters(string text);
int count_sentences(string text);
int count_words(string text);

// Main function
int main(void)
{
    // Get text to evaluate
    string text = get_string("Text: ");

    // Calculate needed variables
    int letters = count_letters(text);
    int sentences = count_sentences(text);
    int words = count_words(text);
    float l = ((float) letters / (float) words) * 100.0;
    float s = ((float) sentences / (float) words) * 100.0;
    float index = 0.0588 * l - 0.296 * s - 15.8;

    // Output result to the screen
    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %0.0f\n", index);
    }
}


int count_letters(string text)
{
    // Declare & initialize
    int letters = 0;

    // Count each letter
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        char c = text[i];
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        {
            letters++;
        }
    }

    // Return results
    return letters;
}

int count_sentences(string text)
{
    // Declare & initialize
    int sentences = 0;

    // Count each sentence
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        char c = text[i];
        if (c == '.' || c == '!' || c == '?')
        {
            sentences++;
        }
    }

    // Return results
    return sentences;
}

int count_words(string text)
{
    // Declare & initialize
    int words = 0;

    // Count each word
    for (int i = 0, n = strlen(text) + 1; i < n; i++)
    {
        char c = text[i];
        if (c == ' ' || c == '\0')
        {
            words++;
        }
    }

    // Return result
    return words;
}

