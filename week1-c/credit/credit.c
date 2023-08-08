#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

string validateCard(long number);
string checkSum(long ccnumber);

int main(void)
{

    // Get CC number
    long ccnumber;
    do
    {
        ccnumber = get_long("Please enter the credit card number: ");
    }
    while (ccnumber < 0);

    string validity = "VALID";
    string invalidity = "INVALID";
    string control_check = checkSum(ccnumber);

    if (strcmp(control_check, validity) == 0)
    {
        string validation = validateCard(ccnumber);
        printf("%s\n", validation);
    }
    else
    {
        printf("INVALID\n");
    }
}


// Validate if VALID card number
// If valid, state card type
// Paramaters:
// AMEX = 15-digit; MASTERCARD = 16-digit; VISA = 13- and 16-digit numbers
// AMEX starts with 34 or 37; MASTERCARD starts [51:55]; VISA starts 4-.
string validateCard(long number)
{

    if ((number / (100000000000000)) >= 51 && (number / (100000000000000)) <= 55)
    {
        return "MASTERCARD";
    }
    else if ((number / 1000000000000000) == 4 || (number / 1000000000000) == 4)
    {
        return "VISA";
    }
    else if ((number / (10000000000000)) == 34 || (number / (10000000000000)) == 37)
    {
        return "AMEX";
    }
    else
    {
        return "INVALID";
    }

}


// Create a checksum function to get the digits and perform the checksum
string checkSum(long ccnumber)
{
    // Loop to obtain the last digit of the creditcard number, dividing by 10 to reduce the numner by one decimal place,
    // and then obtaining the last digit again in the updated loop cycle
    int last_digit;
    long number = ccnumber;
    for (int i = 1; i < 17; i++)
    {
        last_digit = number % 10;
        number = (number / 10);
    }

    // Variables used in calculations:
    // Rules being followed
    // Multiply every other digit by 2, starting with the number’s second-to-last digit, and then add those products’ digits together.
    // Add the sum to the sum of the digits that weren’t multiplied by 2.
    // If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to 0), the number is valid!

    int times_one;
    int sum_double = 0;
    int sum_single = 0;
    int times_two;
    long number_double = ccnumber;
    int last_digit_double;

    // Looping 1 to 17 to cover 16 elements, initializing i to 1 because the nested conditional is doing an even odd test.
    for (int i = 1; i < 17; i++)
    {
        last_digit_double = number_double % 10;
        number_double = (number_double / 10);

        // If odd, collect last digit, else, collect the (last digit * 2)
        // Setting this up to double every other number in the CC numner starting with the penultimate numner
        // When initialized to 1, the pensultimate would begin at i = 2 - an even number
        if (i % 2 != 0)
        {
            times_two = last_digit_double;
            sum_double += 0;
            sum_single += times_two;
        }
        else
        {

            // The conditional below is to determine if one of the doubled values is a two digit number, split that number into
            // two separate digits and then add the digits. Ex - doubling 7 would give 14, the conditional would split 14 to 1 and 4,
            // summing them to equal 5.
            times_two = last_digit_double * 2;
            if (times_two >= 10)
            {
                times_two = ((last_digit_double * 2) % 10) + floor((last_digit_double * 2) / 10);
            }
            else
            {
                times_two = times_two + 0;
            }

            sum_double += times_two;
            sum_single += 0;
        }
    }

    // String congrol is going to hold either "VALID" or "INVALID"
    // The string value is being returned to an if else condition written in main(). In short, if the rules of the program are satisfied
    // by the calculations above and immediately below, the program will return "VALID" to that conditional and then determine which
    // card type the number corresponds to.
    string control;
    int total = sum_single + sum_double;


    // Conditional stating if remainder when divided by 10 is 0, do this else. Remainder of 0 is the solution to the problem statement
    // described above
    if (total % 10 == 0)
    {
        control = "VALID";
    }
    else
    {
        control = "INVALID";
    }
    return control;
}


