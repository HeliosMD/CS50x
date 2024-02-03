#include <cs50.h>
#include <stdio.h>

int count_digits(long n);
int extract_digit(long n, int d);

int main(void)
{
    // Declare and initialize required variables
    int sum_pairs = 0;
    int sum_total = 0;

    // Acquire the card's number
    long number = get_long("Number: ");

    // Calculate number of digits
    int digits = count_digits(number);

    // Calculate pairs checksum
    for (int i = 2; i < digits + 1; i += 2)
    {
        int quant = extract_digit(number, i) * 2;
        for (int j = 1; j < count_digits(quant) + 1; j++)
        {
            sum_pairs = sum_pairs + extract_digit(quant, j);
        }
    }

    // Calculate total checksum
    sum_total = sum_pairs;

    for (int i = 1; i < digits + 1; i += 2)
    {
        sum_total = sum_total + extract_digit(number, i);
    }

    // Validate checksum
    if (extract_digit(sum_total, 1) == 0)
    {
        if (count_digits(number) == 15 && extract_digit(number, 15) == 3 &&
            (extract_digit(number, 14) == 4 || extract_digit(number, 14) == 7))
        {
            printf("AMEX\n");
        }
        else if (count_digits(number) == 16 && extract_digit(number, 16) == 5 &&
                 (extract_digit(number, 15) >= 1 && extract_digit(number, 15) <= 5))
        {
            printf("MASTERCARD\n");
        }
        else if ((count_digits(number) == 13 && extract_digit(number, 13) == 4) ||
                 (count_digits(number) == 16 && extract_digit(number, 16) == 4))
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

int count_digits(long n)
{
    // Declare variables needed
    int digit = 0;
    int digits = 0;

    // Get digit by digit until n = 0
    do
    {
        // Get the last digit
        digit = n % 10;

        // Remove the last digit from number
        n = (n - digit) / 10;

        // Increase number of digits to count
        digits++;

    }
    while (n > 0);
    return digits;
}

int extract_digit(long n, int d)
{
    int digit = 0;
    int digits = 0;
    do
    {
        // Get the last digit
        digit = n % 10;

        // Remove the last digit from number
        n = (n - digit) / 10;

        // Increase number of digits to count
        digits++;

    }
    while (digits < d);
    return digit;
}
