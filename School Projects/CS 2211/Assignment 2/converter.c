#include <stdio.h>

/*
Name: Converter
Description: A program that converts a user inputted number between two units of measure.
Author: Raymond Xie
Student No: 251275727
*/ 

int main()
{

    // Variables
    int userNum;
    double conversion;
    double result;
    char charInput;

    // Variable to check if the user exits or not
    int exit = 0;

    // Will terminate the program when the user enters 5
    while(exit != 1) 
    {
        // Asking user for input
        printf("\nEnter an integer between 1-5: ");
        scanf("%d", &userNum);

        // Setting limits on integers (If user enters integer that is not 1-5)
        if(userNum > 5 || userNum < 1) {
            while(userNum > 5 || userNum < 1) {
                printf("\nEnter an integer between 1-5: ");
                scanf("%d", &userNum);
            }
        }

        // Cases
        if(userNum == 1) {
            // Asking user for input
            printf("\nEnter a conversion (K = kilograms -> pounds, P = pounds -> kilograms): ");
            scanf(" %c", &charInput);

            // Prevents user from inputting invalid input
            while(charInput != 'k' && charInput != 'K' && charInput != 'p' && charInput != 'P') {
                // Asking user for input
                printf("\nEnter a conversion (K = kilograms -> pounds, P = pounds -> kilograms): ");
                scanf(" %c", &charInput);

            }

            // If statements
            if(charInput == 'k' || charInput == 'K') {
                // Asking user for input
                printf("\nEnter the kg you want converted into lbs: ");
                scanf(" %lf", &conversion);
                    
                // Converting kg -> lbs
                result = conversion * 2.20462;
                printf("\nYour conversion is %5f lbs\n", result);

            } else if(charInput == 'p' || charInput == 'P') {
                // Asking user for input
                printf("\nEnter the lbs you want converted into kg: ");
                scanf(" %lf", &conversion);
                    
                // Converting lbs -> kg
                result = conversion / 2.20462;
                printf("\nYour conversion is %5f kg\n", result);

            }

        } else if(userNum == 2) {
            // Asking user for input
            printf("\nEnter a conversion (H = hectares -> acres, A = acres -> hectares): ");
            scanf(" %c", &charInput);

            // Prevents user from inputting invalid input
            while(charInput != 'h' && charInput != 'H' && charInput != 'a' && charInput && 'A') {
                // Asking user for input
                printf("\nEnter a conversion (H = hectares -> acres, A = acres -> hectares): ");
                scanf(" %c", &charInput);

            }

            // If statements
            if(charInput == 'h' || charInput == 'H') {
                // Asking user for input
                printf("\nEnter the hectares you want converted into acres: ");
                scanf(" %lf", &conversion);
                    
                // Converting hectares -> acres
                result = conversion * 2.47105;
                printf("\nYour conversion is %5f acres\n", result);

            } else if(charInput == 'a' || charInput == 'A') {
                // Asking user for input
                printf("\nEnter the acres you want converted into hectares: ");
                scanf(" %lf", &conversion);
                    
                // Converting acres -> hectares
                result = conversion / 2.47105;
                printf("\nYour conversion is %5f hectares\n", result);

            }
            
        } else if(userNum == 3) {
            // Asking user for input
            printf("\nEnter a conversion (L = liters -> gallons, G = gallons -> liters): ");
            scanf(" %c", &charInput);

            // Prevents user from inputting invalid input
            while(charInput != 'l' && charInput != 'L' && charInput != 'g' && charInput != 'G') {
                // Asking user for input
                printf("\nEnter a conversion (L = liters -> gallons, G = gallons -> liters): ");
                scanf(" %c", &charInput);

            }

            // If statements
            if(charInput == 'l' || charInput == 'L') {
                // Asking user for input
                printf("\nEnter the L you want converted into gallons: ");
                scanf(" %lf", &conversion);
                    
                // Converting liters -> gallons
                result = conversion * 0.264172;
                printf("\nYour conversion is %6f gallons\n", result);

            } else if(charInput == 'g' || charInput == 'G') {
                // Asking user for input
                printf("\nEnter the gallons you want converted into L: ");
                scanf(" %lf", &conversion);
                    
                // Converting gallons -> liters
                result = conversion / 0.264172;
                printf("\nYour conversion is %6f L\n", result);

            }

        } else if(userNum == 4) {
            // Asking user for input
            printf("\nEnter a conversion (K = kilometer -> mile, M = mile -> kilometer): ");
            scanf(" %c", &charInput);

            // Prevents user from inputting invalid input
            while(charInput != 'k' && charInput != 'K' && charInput != 'm' && charInput != 'M') {
                // Asking user for input
                printf("\nEnter a conversion (K = kilometer -> mile, M = mile -> kilometer): ");
                scanf(" %c", &charInput);

            }

            // If statements
            if(charInput == 'k' || charInput == 'K') {
                // Asking user for input
                printf("\nEnter the km you want converted into mi: ");
                scanf(" %lf", &conversion);
                    
                // Converting km -> mi
                result = conversion * 0.621371;
                printf("\nYour conversion is %6f mi\n", result);

            } else if(charInput == 'm' || charInput == 'M') {
                // Asking user for input
                printf("\nEnter the mi you want converted into km: ");
                scanf(" %lf", &conversion);
                    
                // Converting mi -> km
                result = conversion / 0.621371;
                printf("\nYour conversion is %6f km\n", result);

            }

        } else {
            // Turns exit into 1, exiting out of the while loop
            exit++;
        }
    
    }

}