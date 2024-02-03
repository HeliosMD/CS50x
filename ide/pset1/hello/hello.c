#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Declares name variable as string
    string name = get_string("What's your name?\n");

    // Greets person with name
    printf("Hello, %s\n", name);

}
