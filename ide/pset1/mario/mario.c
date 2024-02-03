#include <cs50.h>
#include <stdio.h>

// Bricks function declaration
void bricks(int n, char c);


// Main C function
int main(void)
{

    // Declares variable height and initializes it to zero
    int height = 0;

    // Prompts for height until it is a positive integer
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // Prints the actual bricks
    for (int i = 1; i < height + 1; i++)
    {
        bricks(height - i, ' ');
        bricks(i, '#');
        printf("  ");
        bricks(i, '#');
        printf("\n");
    }


}

// Bricks function definition
void bricks(int n, char c)
{
    // Loops n times
    for (int i = 0; i < n; i++)
    {

        // Outputs c char n times
        printf("%c", c);

    }
}

