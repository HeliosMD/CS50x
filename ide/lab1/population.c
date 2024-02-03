#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int start_size = 0;
    int end_size = 0;
    int years = 0;

    // TODO: Prompt for start size

    do
    {
        start_size = get_int("Start size: ");
    }
    while (start_size < 9);

    // TODO: Prompt for end size

    do
    {
        end_size = get_int("End size: ");
    }
    while (end_size < start_size);

    // TODO: Calculate number of years until we reach threshold

    int total_size = start_size;
    for (years = 0; total_size < end_size; years++)
    {
        float annual_increment = (float) total_size / (float) 3 ;
        float annual_decrement = (float) total_size / (float) 4;
        int total_increment = (int) annual_increment - (int) annual_decrement;

        total_size += total_increment; // * total_size;
    }
    printf("Years: %i\n", years);

}
