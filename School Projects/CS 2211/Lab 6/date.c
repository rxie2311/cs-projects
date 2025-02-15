#include <stdio.h>

// FUNCTIONS
// Returns the day of the year based on user input (Day 1-366)
int day_of_year(int month, int day, int year)
{
    // Variable
    int sum = 0;

    // Adding to variable
    // JAN
    if(month == 1) {
        sum = sum + day;
    
    // FEB
    } else if(month == 2) {
        // If year is divisible by 400 or divisible by 4 and not 100
        if(year%400 == 0 || (year%4 == 0 && year%100 != 0)) {
            // 29 days max in Feb
            sum = sum + 31 + day;
        } else {
            // 28 days max in Feb
            sum = sum + 31 + day;
        }

    // MAR
    } else if(month == 3) {
        // Leap year check
        if(year%400 == 0 || (year%4 == 0 && year%100 != 0)) {
            sum = sum + 31 + 29 + day;
        } else {
            sum = sum + 31 + 28 + day;
        }

    // APR
    } else if(month == 4) {
        // Leap year check
        if(year%400 == 0 || (year%4 == 0 && year%100 != 0)) {
            sum = sum + 31 + 29 + 31 + day;
        } else {
            sum = sum + 31 + 28 + 31 + day;
        }

    // MAY
    } else if(month == 5) {
        // Leap year check
        if(year%400 == 0 || (year%4 == 0 && year%100 != 0)) {
            sum = sum + 31 + 29 + 31 + 30 + day;
        } else {
            sum = sum + 31 + 28 + 31 + 30 + day;
        }

    // JUN
    } else if(month == 6) {
        // Leap year check
        if(year%400 == 0 || (year%4 == 0 && year%100 != 0)) {
            sum = sum + 31 + 29 + 31 + 30 + 31 + day;
        } else {
            sum = sum + 31 + 28 + 31 + 30 + 31 + day;
        }

    // JUL
    } else if(month == 7) {
        // Leap year check
        if(year%400 == 0 || (year%4 == 0 && year%100 != 0)) {
            sum = sum + 31 + 29 + 31 + 30 + 31 + 30 + day;
        } else {
            sum = sum + 31 + 28 + 31 + 30 + 31 + 30 + day;
        }

    // AUG
    } else if(month == 8) {
        // Leap year check
        if(year%400 == 0 || (year%4 == 0 && year%100 != 0)) {
            sum = sum + 31 + 29 + 31 + 30 + 31 + 30 + 31 + day;
        } else {
            sum = sum + 31 + 28 + 31 + 30 + 31 + 30 + 31 + day;
        }

    // SEP
    } else if(month == 9) {
        // Leap year check
        if(year%400 == 0 || (year%4 == 0 && year%100 != 0)) {
            sum = sum + 31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + day;
        } else {
            sum = sum + 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + day;
        }

    // OCT
    } else if(month == 10) {
        // Leap year check
        if(year%400 == 0 || (year%4 == 0 && year%100 != 0)) {
            sum = sum + 31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + day;
        } else {
            sum = sum + 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + day;
        }

    // NOV
    } else if(month == 11) {
        // Leap year check
        if(year%400 == 0 || (year%4 == 0 && year%100 != 0)) {
            sum = sum + 31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + day;
        } else {
            sum = sum + 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + day;
        }

    // DEC
    } else if(month == 12) {
        // Leap year check
        if(year%400 == 0 || (year%4 == 0 && year%100 != 0)) {
            sum = sum + 31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30 + day;
        } else {
            sum = sum + 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30 + day;
        }
    }

    // Returns the date
    return sum;
}

// MAIN METHOD
int main()
{

    // Variables
    int m, d, y;

    printf("Enter a date (MM/DD/YYYY): ");
    scanf("%d/%d/%d", &m, &d, &y);

    int date = day_of_year(m, d, y);
    printf("The day of the year is Day %d", date);

}