#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Defines BYTE data type
typedef uint8_t BYTE;

// Declares calc_id function prototype
char *calc_id(BYTE files);

int main(int argc, char *argv[])
{
    // Declares needed variables
    BYTE files = 0;
    BYTE is_jpg = 0;
    BYTE buffer[512];
    FILE *input = NULL;
    FILE *output = NULL;
    char *file_id = NULL;

    // Validates invocation arguments
    if (argc == 2)
    {
        input = fopen(argv[1], "r");
    }
    else if (argc > 2 || argc < 2)
    {
        printf("Usage: ./recover card.raw\n");
        return 1;
    }

    // Return error if input file cannot be read
    if (input == NULL)
    {
        printf("Image file could not be read.\n");
        return 1;
    }

    // Read the file a block a time and copying it into jpeg file
    while (fread(&buffer, sizeof(BYTE), 512, input))
    {
        // Reads block header
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3] >= 0xe0 && buffer[3] <= 0xef)
        {
            // Closes actual file and increase the number of files
            if (output != NULL)
            {
                fclose(output);
                files++;
            }

            // Keeps track if is a jpg block
            is_jpg = 1;

            // Calculates file identifier
            file_id = calc_id(files);

            // Opens new file with the same output pointer with a different name
            output = fopen(file_id, "w");

            // Writes the block to the new file
            fwrite(&buffer, sizeof(BYTE), 512, output);
        }
        else if (is_jpg == 1)
        {
            // Keeps writing to the file while block follows a jpeg block
            fwrite(&buffer, sizeof(BYTE), 512, output);
        }
        else
        {
            // If block is headerless or has a header different than jpeg just skip and keep track of it
            is_jpg = 0;
        }
    }

    // Close all open files
    fclose(input);
    fclose(output);
}

// Calculates file ID by setting files number to a string with .jpg extension
char *calc_id(BYTE files)
{
    // Allocates memory for the string output
    char *out = malloc(8);

    // Fills the string output with the proper content
    out[0] = '0';
    out[1] = (char) round((files - (files % 10)) / 10) + 48;
    out[2] = (char)(files % 10) + 48;
    out[3] = '.';
    out[4] = 'j';
    out[5] = 'p';
    out[6] = 'g';
    out[7] = '\0';
    return out;
}