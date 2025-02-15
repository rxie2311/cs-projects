#include <stdio.h>

int main()
{
    // Variables
    int dMorning, aMorning, hour, min, dHour, aHour, dMin, aMin;

    // Exit variable
    int exit = 0;

    // Arrays
    int departures[] = {8, 9, 11, 12, 14, 15, 19, 21};
    int departuresTwelve[] = {8, 9, 11, 12, 2, 3, 7, 9};
    int departureMin[] = {60, 43, 19, 47, 60, 45, 60, 45};

    int arrivals[] = {10, 11, 13, 15, 16, 17, 21, 23};
    int arrivalMin[] = {16, 52, 31, 60, 8, 55, 20, 58};

    // While loop that repeats asking until the user stops
    while(exit != 1) {

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

        // Results
        int resultNum;
        // Setting closestHour and closestMin to a high number so it updates
        int closestHour = 1000;
        int closestMin = 1000;

        // For loop to loop through all departure times to find the closest departure time
        for(int i=0; i < 8; i++) {
            // If the flight is before the hour submitted
            if((departures[i] - hour) < 0) {
                // Checking if the positive version of the difference is less than closest hour
                if(-1*(departures[i] - hour) < closestHour) {
                    // Saves index i for reference
                    resultNum = i;
                    // Saves closestHour as difference between departure hour and hour
                    closestHour = -1*(departures[i] - hour);
                    // Seeing if the difference is negative
                    if((departureMin[i] - min) < 0) {
                        // Saves closest min as postive difference
                        closestMin = -1*(departureMin[i] - min);
                    } else {
                        // Saves the difference if already postive
                        closestMin = departureMin[i] - min;
                    }

                // If the differences are the same
                } else if(-1*(departures[i] - hour) == closestHour) {
                    // Checks for difference between minutes
                    if((departureMin[i] - min) < 0) {
                        if(-1*(departureMin[i] - min) < closestMin) {
                            // Saves variables
                            closestHour = -1*(departures[i] - hour);
                            closestMin = -1*(departureMin[i] - min);
                            resultNum = i;
                        }
                    } else {
                        if((departureMin[i] - min) < closestMin) {
                            closestHour = departures[i] - hour;
                            closestMin = departureMin[i] - min;
                            resultNum = i;
                        }
                    }
                }

            } else {
                // Checking if the positive version of the difference is less than closest hour
                if((departures[i] - hour) < closestHour) {
                    // Saves index i for reference
                    resultNum = i;
                    // Saves closestHour as difference between departure hour and hour
                    closestHour = departures[i] - hour;
                    // Seeing if the difference is negative
                    if((departureMin[i] - min) < 0) {
                        // Saves closest min as postive difference
                        closestMin = -1*(departureMin[i] - min);
                    } else {
                        // Saves the difference if already postive
                        closestMin = departureMin[i] - min;
                    }
                    

                // If the differences are the same
                } else if((departures[i] - hour) == closestHour) {
                    // Checks for difference between minutes
                    if((departureMin[i] - min) < 0) {
                        if(-1*(departureMin[i] - min) < closestMin) {
                            // Saves variables
                            closestHour = -1*(departures[i] - hour);
                            closestMin = -1*(departureMin[i] - min);
                            resultNum = i;
                        }
                    } else {
                        if((departureMin[i] - min) < closestMin) {
                            closestHour = departures[i] - hour;
                            closestMin = departureMin[i] - min;
                            resultNum = i;
                        }
                    }
                }
            }

        }

        // Checking for a.m or p.m for departures
        if(departures[resultNum] >= 12) {
            // Morning = 1: Means 24h time is p.m
            dMorning = 1;
            // Cuts down hour if hour is above 12 to convert to 12h time
            if (departures[resultNum] > 12) {
                // Converting and saving 24h time in 12h time in a temp variable
                dHour = departures[resultNum] - 12;
            }

            // If the mins is 60, change to 0
            if(departureMin[resultNum] == 60) {
                dMin = 0;
            } else {
                dMin = departureMin[resultNum];
            }

        } else if(departures[resultNum] == 0) {
            // Morning = 2: Means 12:xx a.m, convert 00:xx into 12:xx a.m
            dMorning = 2;
            // Converting and saving 24h time in 12h time in a temp variable
            dHour = departures[resultNum] + 12;

            // If the mins is 60, change to 0
            if(departureMin[resultNum] == 60) {
                dMin = 0;
            } else {
                dMin = departureMin[resultNum];
            }

        } else {
            // Morning = 0: Means a.m, no conversion necessary
            dMorning = 0;
            // Converting and saving 24h time in 12h time in a temp variable
            dHour = departures[resultNum];

            // If the mins is 60, change to 0
            if(departureMin[resultNum] == 60) {
                dMin = 0;
            } else {
                dMin = departureMin[resultNum];
            }
        }

        // Checking for a.m or p.m for arrivals
        if(arrivals[resultNum] >= 12) {
            // Morning = 1: Means 24h time is p.m
            aMorning = 1;
            // Cuts down hour if hour is above 12 to convert to 12h time
            if (arrivals[resultNum] > 12) {
                // Converting and saving 24h time in 12h time in a temp variable
                aHour = arrivals[resultNum] - 12;
            }

            // If the mins is 60, change to 0
            if(arrivalMin[resultNum] == 60) {
                aMin = 0;
            } else {
                aMin = arrivalMin[resultNum];
            }

        } else if(arrivals[resultNum] == 0) {
            // Morning = 2: Means 12:xx a.m, convert 00:xx into 12:xx a.m
            aMorning = 2;
            // Converting and saving 24h time in 12h time in a temp variable
            aHour = arrivals[resultNum] + 12;

            // If the mins is 60, change to 0
            if(arrivalMin[resultNum] == 60) {
                aMin = 0;
            } else {
                aMin = arrivalMin[resultNum];
            }

        } else {
            // Morning = 0: Means a.m, no conversion necessary
            aMorning = 0;
            // Converting and saving 24h time in 12h time in a temp variable
            aHour = arrivals[resultNum];

            // If the mins is 60, change to 0
            if(arrivalMin[resultNum] == 60) {
                aMin = 0;
            } else {
                aMin = arrivalMin[resultNum];
            }
        }

        // Printing out results
        // If 24h is in a.m
        if (dMorning == 2) {
            // a.m
            if(aMorning == 2) {
                printf("Closest departure time is %02d:%02d a.m., arriving at %02d:%02d a.m.\n", dHour, dMin, aHour, arrivalMin[resultNum]);

            // 00:xx
            } else if(aMorning == 0) {
                printf("Closest departure time is %02d:%02d a.m., arriving at %02d:%02d a.m.\n", dHour, dMin, aHour, arrivalMin[resultNum]);
            
            // p.m
            } else if(aMorning == 1) {
                printf("Closest departure time is %02d:%02d a.m., arriving at %02d:%02d p.m.\n", dHour, dMin, aHour, arrivalMin[resultNum]);
            }
            

        // If 24h is at 00:xx
        } else if(dMorning == 0) {
            // a.m
            if(aMorning == 2) {
                printf("Closest departure time is %02d:%02d a.m., arriving at %02d:%02d a.m.\n", dHour, dMin, aHour, aMin);

            // 00:xx
            } else if(aMorning == 0) {
                printf("Closest departure time is %02d:%02d a.m., arriving at %02d:%02d a.m.\n", dHour, dMin, aHour, aMin);
            
            // p.m
            } else if(aMorning == 1) {
                printf("Closest departure time is %02d:%02d a.m., arriving at %02d:%02d p.m.\n", dHour, dMin, aHour, aMin);
            }
        
        // If 24h is in p.m
        } else if (dMorning == 1) {
            // a.m
            if(aMorning == 2) {
                printf("Closest departure time is %02d:%02d p.m., arriving at %02d:%02d a.m.\n", departuresTwelve[resultNum], dMin, aHour, aMin);

            // 00:xx
            } else if(aMorning == 0) {
                printf("Closest departure time is %02d:%02d p.m., arriving at %02d:%02d a.m.\n", departuresTwelve[resultNum], dMin, aHour, aMin);
            
            // p.m
            } else if(aMorning == 1) {
                printf("Closest departure time is %02d:%02d p.m., arriving at %02d:%02d p.m.\n", departuresTwelve[resultNum], dMin, aHour, aMin);
            }
        }

        // Asks if user wishes to quit or not
        int userNum;
        printf("Enter 1 to continue or 0 to quit: ");
        scanf("%d", &userNum);

        // Loop to prevent user from entering option
        if(userNum < 0 || userNum > 1) {
            while(userNum < 0 || userNum > 1) {
                printf("Enter 1 to continue or 0 to quit: ");
                scanf("%d", &userNum);
            }
        }
        
        // Exits out if it determins the user entered 0
        if(userNum == 0) {
            exit++;
        }

    }

}