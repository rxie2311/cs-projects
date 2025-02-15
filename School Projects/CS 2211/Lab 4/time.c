#include <stdio.h>

int main()
{
    // Variables
    int morning, hour, min;

    // User input
    printf("Enter a 24-hour time (Please enter 00:00 for 12 a.m): ");
    scanf("%02d:%02d", &hour, &min);

    // Loop to prevent user from entering invalid time
    if(hour > 23 || min > 59) {
        while(hour > 23 || min > 59) {
            printf("Enter a 24-hour time (Please enter 00:00 for 12 a.m): ");
            scanf("%02d:%02d", &hour, &min);
        }
    }

    // Checking for a.m or p.m
    if(hour >= 12) {
        // Morning = 1: Means 24h time is p.m
        morning = 1;
        // Cuts down hour if hour is above 12 to convert to 12h time
        if (hour > 12) {
            hour -= 12;
        }

    } else if(hour == 0) {
        // Morning = 2: Means 12:xx a.m, convert 00:xx into 12:xx a.m
        morning = 2;
        hour = hour + 12;

    } else {
        // Morning = 0: Means 24h time is a.m, no conversion necessary
        morning = 0;
    }

    // Results
    // If 24h is in a.m
    if (morning == 2) {
        printf("%02d:%02d a.m.\n", hour, min);

    // If 24h is at 00:xx
    } else if(morning == 0) {
        printf("%02d:%02d a.m.\n", hour, min);
    
    // If 24h is in p.m
    } else if (morning == 1) {
        printf("%02d:%02d p.m.\n", hour, min);
    }

}