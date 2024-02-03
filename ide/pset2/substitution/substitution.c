// Load required libraries
#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Declare prototypes
bool validate_special(string s);
bool validate_repeat(string s);
string cipher(string text, string key);

// Main function handles the error code
int main(int argc, string argv[])
{
    string key = "";
    if (argc < 2 || argc > 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (argc == 2)
    {
        int v = 0;
        key = argv[1];

        // Validate the key
        if (strlen(key) == 26)
        {
            if (validate_special(key))
            {
                if (validate_repeat(key))
                {
                    // Cipher the plain text with the key
                    string text = get_string("plaintext:  ");
                    printf("ciphertext: %s\n", cipher(text, key));
                    return 0;
                }
                else
                {
                    printf("Key must not repeat any character.\n");
                    return 1;
                }
            }
            else
            {
                printf("Key must not contain special characters.\n");
                return 1;
            }
        }
        else
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
    }
}

bool validate_special(string s)
{
    // Check there are no special characters
    for (int i = 0; i < 26; i++)
    {
        s[i] = toupper(s[i]);
        if (!((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')))
        {
            return 0;
        }
    }
    return 1;
}

bool validate_repeat(string s)
{
    // Check if any character is repeated
    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            // Checks key against itself
            /* printf("%c = %c? (%i = %i?)\n", s[i], s[j], i, j); */
            if ((s[i] == s[j]) && (i != j))
            {
                // Do not validate if any character is repeated
                return 0;
            }
        }
    }
    // If no character repeats just validate
    return 1;
}

string cipher(string text, string key)
{
    string output = text;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] >= 'a' && text[i] <= 'z')
        {
            char k = text[i];
            output[i] = tolower(key[(int)k - 97]);
        }
        else if (text[i] >= 'A' && text[i] <= 'Z')
        {
            char k = text[i];
            output[i] = key[(int)k - 65];
        }
        else
        {
            output[i] = text[i];
        }
    }
    return output;
}
