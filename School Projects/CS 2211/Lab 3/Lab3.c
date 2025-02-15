#include <stdio.h>

int main()
{
    // Calling on Question 1
    Q1();
    // Calling on Question 2
    Q2();
}

// Question 1:
void Q1() 
{

    int num1, num2, num3, num4;

    // User input
    printf("Enter four integers: ");
    scanf("%d %d %d %d", &num1, &num2, &num3, &num4);

    int lowest = num1;
    int highest = num1;

    // Comparisons
    if(num2 < lowest) {
        lowest = num2;
    } else if(num2 > highest) {
        highest = num2;
    }

    if(num3 < lowest) {
        lowest = num3;
    } else if(num3 > highest) {
        highest = num3;
    }

    if(num4 < lowest) {
        lowest = num4;
    } else if(num4 > highest) {
        highest = num4;
    }

    // Print statements
    printf("\nLargest: %d", highest);
    printf("\nSmallest: %d", lowest);

}

// Question 2:
void Q2()
{

    int i;
    int days, startingDay;

    // Asking user for days
    printf("\nEnter number of days in the month: ");
    scanf("%d", &days);
    // Setting limits on days (only 28-31 is valid)
    if(days > 31 || days < 28) {
        while(days > 31 || days < 28) {
            printf("\nEnter number of days in the month: ");
            scanf("%d", &days);
        }
    }

    // Asking user for starting days
    printf("\nEnter the starting day of the week (1=Sun, 7=Sat): ");
    scanf("%d", &startingDay);
    // Setting limits on starting days (only 1-7 is valid)
    if(startingDay > 7 || startingDay < 1) {
        while(startingDay > 7 || startingDay < 1) {
            printf("\nEnter the starting day of the week (1=Sun, 7=Sat): ");
            scanf("%d", &startingDay);
        }
    }

    // For loop to add spaces until the starting day
    for(i=1; i<startingDay; i++) {
        // Space
        printf("   ");
    }

    // For loop to space out the days in the month
    for(i=1; i<=days; i++) {
        // Spaces between days
        printf("%3d", i);
        // New line once the number is divisble by 7 to signify the end of the week
        if((startingDay + i - 1) % 7 == 0) { printf("\n"); }

    }
}