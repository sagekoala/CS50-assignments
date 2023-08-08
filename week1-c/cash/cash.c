#include <cs50.h>
#include <stdio.h>

// I think the modulus operator is necessary for this assignment. The modulus operator cannot
// be applied to floating point numbers and therefore we must use integers throughout


int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Ask how many cents the customer is owed
    int cents = get_cents();

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("%i\n", coins);
}

int get_cents(void)
{
    int cents = 0;
    do
    {
        cents = get_int("How many cents are owed? ");
    }
    while (cents < 0);

    if (cents > 0.00 && cents < 1.00)
    {
        return cents *= 100;
    }
    else
    {
        return cents;
    }
}

int calculate_quarters(int cents)
{
    // Calculation for quarters
    int quarters =  cents / 25;
    if (cents < 25)
    {
        return quarters = 0;
    }
    else
    {
        return quarters;
    }
}

int calculate_dimes(int cents)
{
    // Calculation for dimes
    int dimes = cents / 10;
    if (cents < 10)
    {
        return dimes = 0;
    }
    else
    {
        return dimes;
    }
}

int calculate_nickels(int cents)
{
    // Calculation for nickels
    int nickels = cents / 5;
    if (cents < 5)
    {
        return 0;
    }
    else
    {
        return nickels;
    }
}

int calculate_pennies(int cents)
{
    // Calculation for pennies
    int pennies = cents / 1;
    if (cents < 1)
    {
        return 0;
    }
    else
    {
        return pennies;
    }
}
