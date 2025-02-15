#include <stdio.h>

/*
Name: IntToEnglish
Description: A program that takes a user inputted number between 1-999 and outputs the number in English.
Author: Raymond Xie
Student No: 251275727
*/ 

int main()
{
    
    // Variables
    int userNum;
    int first;
    int second;

    // Text arrays for reference
    char* ones[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    char* tens[] = {"teen", "twenty-", "thirty-", "fourty-", "fifty-", "sixty-", "seventy-", "eighty-", "ninety-"};
    char* hundreds[] = {"one hundred and ", "two hundred and ", "three hundred and ", "four hundred and ", "five hundred and ", "six hundred and ", "seven hundred and ", "eight hundred and ", "nine hundred and "};
    char* divisibleByTen[] = {"ten", "twenty", "thirty", "fourty", "fifty", "sixty", "seventy", "eighty", "ninety"};

    // Check if the user exited
    int exit = 0;

    // While loop until user enters 0
    while(exit != 1)
    {
        // Asking user for input
        printf("\nPlease enter a value (1-999, 0 to quit): ");
        scanf("%d", &userNum);

        // If num is 1-9
        if(userNum < 10 && userNum > 0) {
            switch(userNum) 
            {
                case 1:
                    printf("You entered the number %s\n", ones[0]);
                    break;
                case 2:
                    printf("You entered the number %s\n", ones[1]);
                    break;
                case 3:
                    printf("You entered the number %s\n", ones[2]);
                    break;
                case 4:
                    printf("You entered the number %s\n", ones[3]);
                    break;
                case 5:
                    printf("You entered the number %s\n", ones[4]);
                    break;
                case 6:
                    printf("You entered the number %s\n", ones[5]);
                    break;
                case 7:
                    printf("You entered the number %s\n", ones[6]);
                    break;
                case 8:
                    printf("You entered the number %s\n", ones[7]);
                    break;
                case 9:
                    printf("You entered the number %s\n", ones[8]);
                    break;
            }

        // If num is between 10-99
        } else if(userNum >= 10 && userNum <= 99) {

            // Set user int into variable to find first digit
            first = userNum;
            // Finding first digit of int
            while(first >= 10) {
                first = first / 10;
            }

            // 10 - 19
            if(first == 1) {
                // For loop to cycle through all ones digits
                for(int i=0; i<9; i++) {
                    if(userNum % 10 == 0) {
                        printf("You entered the number ten\n");
                        break;
                    } else if(userNum % 10 == 1) {
                        printf("You entered the number eleven\n");
                        break;
                    } else if(userNum % 10 == 2) {
                        printf("You entered the number twelve\n");
                        break;
                    } else if(userNum % 10 == 3) {
                        printf("You entered the number thirteen\n");
                        break;
                    } else if(userNum % 10 == 5) {
                        printf("You entered the number fifteen\n");
                        break;
                    } else if(userNum % 10 == 8) {
                        printf("You entered the number eighteen\n");
                        break;
                    } else if(userNum % 10 == i+1) {
                        printf("You entered the number %s%s\n", ones[i], tens[0]);
                        break;
                    }
                }

            // 20 - 29
            } else if(first == 2) {
                // For loop to cycle through all ones digits
                for(int i=0; i<9; i++) {
                    if(userNum % 20 == 0) {
                        printf("You entered the number twenty\n");
                        break;
                    } else if(userNum % 20 == i+1) {
                        printf("You entered the number %s%s\n", tens[1], ones[i]);
                        break;
                    }
                }

            // 30 - 39
            } else if(first == 3) {
                // For loop to cycle through all ones digits
                for(int i=0; i<9; i++) {
                    if(userNum % 30 == 0) {
                        printf("You entered the number thirty\n");
                        break;
                    } else if(userNum % 30 == i+1) {
                        printf("You entered the number %s%s\n", tens[2], ones[i]);
                        break;
                    }
                }

            // 40 - 49
            } else if(first == 4) {
                // For loop to cycle through all ones digits
                for(int i=0; i<9; i++) {
                    if(userNum % 40 == 0) {
                        printf("You entered the number fourty\n");
                        break;
                    } else if(userNum % 40 == i+1) {
                        printf("You entered the number %s%s\n", tens[3], ones[i]);
                        break;
                    }
                }

            // 50 - 59
            } else if(first == 5) {
                // For loop to cycle through all ones digits
                for(int i=0; i<9; i++) {
                    if(userNum % 50 == 0) {
                        printf("You entered the number fifty\n");
                        break;
                    } else if(userNum % 50 == i+1) {
                        printf("You entered the number %s%s\n", tens[4], ones[i]);
                        break;
                    }
                }

            // 60 - 69
            } else if(first == 6) {
                // For loop to cycle through all ones digits
                for(int i=0; i<9; i++) {
                    if(userNum % 60 == 0) {
                        printf("You entered the number sixty\n");
                        break;
                    } else if(userNum % 60 == i+1) {
                        printf("You entered the number %s%s\n", tens[5], ones[i]);
                        break;
                    }
                }

            // 70 - 79
            } else if(first == 7) {
                // For loop to cycle through all ones digits
                for(int i=0; i<9; i++) {
                    if(userNum % 70 == 0) {
                        printf("You entered the number seventy\n");
                        break;
                    } else if(userNum % 70 == i+1) {
                        printf("You entered the number %s%s\n", tens[6], ones[i]);
                        break;
                    }
                }

            // 80 - 89
            } else if(first == 8) {
                // For loop to cycle through all ones digits
                for(int i=0; i<9; i++) {
                    if(userNum % 80 == 0) {
                        printf("You entered the number eighty\n");
                        break;
                    } else if(userNum % 80 == i+1) {
                        printf("You entered the number %s%s\n", tens[7], ones[i]);
                        break;
                    }
                }

            // 90 - 99
            } else if(first == 9) {
                // For loop to cycle through all ones digits
                for(int i=0; i<9; i++) {
                    if(userNum % 90 == 0) {
                        printf("You entered the number ninety\n");
                        break;
                    } else if(userNum % 90 == i+1) {
                        printf("You entered the number %s%s\n", tens[8], ones[i]);
                        break;
                    }
                }
            }

        // If num is between 100-999
        } else if(userNum >= 100 && userNum <= 999) {

            // Set user int into variable to find first digit
            first = userNum;
            // Finding first digit of int
            while(first >= 100) {
                first = first / 10;
            }

            // 100 - 199
            if(first >= 10 && first <= 19) {
                
                // Find second digit of int
                second = first % 10;

                // 100 - 109
                if(second == 0) {
                    // For loop to cycle through all ones digits
                    for(int i=0; i<9; i++) {
                        if(userNum % 100 == 0) {
                            printf("You entered the number one hundred\n");
                            break;
                        } else if(userNum % 100 == i+1) {
                            printf("You entered the number %s%s\n", hundreds[0], ones[i]);
                            break;
                        }
                    }

                // 110 - 119
                } else if(second == 1) {
                    // For loop to cycle through all ones digits
                    for(int i=0; i<9; i++) {
                        if(userNum % 110 == 0) {
                            printf("You entered the number one hundred and ten\n");
                            break;
                        } else if(userNum % 110 == 1) {
                            printf("You entered the number %seleven\n", hundreds[0]);
                            break;
                        } else if(userNum % 110 == 2) {
                            printf("You entered the number %stwelve\n", hundreds[0]);
                            break;
                        } else if(userNum % 110 == 3) {
                            printf("You entered the number %sthirteen\n", hundreds[0]);
                            break;
                        } else if(userNum % 110 == 5) {
                            printf("You entered the number %sfifteen\n", hundreds[0]);
                            break;
                        } else if(userNum % 110 == 8) {
                            printf("You entered the number %seighteen\n", hundreds[0]);
                            break;
                        } else if(userNum % 110 == i+1) {
                            printf("You entered the number %s%s%s\n", hundreds[0], ones[i], tens[0]);
                            break;
                        }
                    }

                // 120 - 199
                } else if(second >= 2 && second <= 9) {

                    // Tens
                    switch(userNum) 
                    {
                        case 120:
                            printf("You entered the number %s%s\n", hundreds[0], divisibleByTen[1]);
                            break;
                        case 130:
                            printf("You entered the number %s%s\n", hundreds[0], divisibleByTen[2]);
                            break;
                        case 140:
                            printf("You entered the number %s%s\n", hundreds[0], divisibleByTen[3]);
                            break;
                        case 150:
                            printf("You entered the number %s%s\n", hundreds[0], divisibleByTen[4]);
                            break;
                        case 160:
                            printf("You entered the number %s%s\n", hundreds[0], divisibleByTen[5]);
                            break;
                        case 170:
                            printf("You entered the number %s%s\n", hundreds[0], divisibleByTen[6]);
                            break;
                        case 180:
                            printf("You entered the number %s%s\n", hundreds[0], divisibleByTen[7]);
                            break;
                        case 190:
                            printf("You entered the number %s%s\n", hundreds[0], divisibleByTen[8]);
                            break;
                    }

                    // Loop to determine the rest of the numbers
                    for(int i=1; i<9; i++) {

                        for(int j=0; j<9; j++) {
                            // Variable to track which tens digit the number is on
                            int sum = 100 + ((i+1)*10);

                            if(userNum % sum == j+1) {
                                printf("You entered the number %s%s%s\n", hundreds[0], tens[i], ones[j]);
                                break;
                            }
                        }
                    }

                }

            // 200 - 299
            } else if(first >= 20 && first <= 29) {
                
                // Find second digit of int
                second = first % 10;

                // 200 - 209
                if(second == 0) {
                    // For loop to cycle through all ones digits
                    for(int i=0; i<9; i++) {
                        if(userNum % 200 == 0) {
                            printf("You entered the number two hundred\n");
                            break;
                        } else if(userNum % 200 == i+1) {
                            printf("You entered the number %s%s\n", hundreds[1], ones[i]);
                            break;
                        }
                    }

                // 210 - 219
                } else if(second == 1) {
                    // For loop to cycle through all ones digits
                    for(int i=0; i<9; i++) {
                        if(userNum % 210 == 0) {
                            printf("You entered the number two hundred and ten\n");
                            break;
                        } else if(userNum % 210 == 1) {
                            printf("You entered the number %seleven\n", hundreds[1]);
                            break;
                        } else if(userNum % 210 == 2) {
                            printf("You entered the number %stwelve\n", hundreds[1]);
                            break;
                        } else if(userNum % 210 == 3) {
                            printf("You entered the number %sthirteen\n", hundreds[1]);
                            break;
                        } else if(userNum % 210 == 5) {
                            printf("You entered the number %sfifteen\n", hundreds[1]);
                            break;
                        } else if(userNum % 210 == 8) {
                            printf("You entered the number %seighteen\n", hundreds[1]);
                            break;
                        } else if(userNum % 210 == i+1) {
                            printf("You entered the number %s%s%s\n", hundreds[1], ones[i], tens[0]);
                            break;
                        }
                    }

                // 220 - 299
                } else if(second >= 2 && second <= 9) {

                    // Tens
                    switch(userNum) 
                    {
                        case 220:
                            printf("You entered the number %s%s\n", hundreds[1], divisibleByTen[1]);
                            break;
                        case 230:
                            printf("You entered the number %s%s\n", hundreds[1], divisibleByTen[2]);
                            break;
                        case 240:
                            printf("You entered the number %s%s\n", hundreds[1], divisibleByTen[3]);
                            break;
                        case 250:
                            printf("You entered the number %s%s\n", hundreds[1], divisibleByTen[4]);
                            break;
                        case 260:
                            printf("You entered the number %s%s\n", hundreds[1], divisibleByTen[5]);
                            break;
                        case 270:
                            printf("You entered the number %s%s\n", hundreds[1], divisibleByTen[6]);
                            break;
                        case 280:
                            printf("You entered the number %s%s\n", hundreds[1], divisibleByTen[7]);
                            break;
                        case 290:
                            printf("You entered the number %s%s\n", hundreds[1], divisibleByTen[8]);
                            break;
                    }

                    // Loop to determine the rest of the numbers
                    for(int i=1; i<9; i++) {

                        for(int j=0; j<9; j++) {
                            // Variable to track which tens digit the number is on
                            int sum = 200 + ((i+1)*10);

                            if(userNum % sum == j+1) {
                                printf("You entered the number %s%s%s\n", hundreds[1], tens[i], ones[j]);
                                break;
                            }
                        }
                    }
                }

            // 300 - 399
            } else if(first >= 30 && first <= 39) {
                
                // Find second digit of int
                second = first % 10;

                // 300 - 309
                if(second == 0) {
                    // For loop to cycle through all ones digits
                    for(int i=0; i<9; i++) {
                        if(userNum % 300 == 0) {
                            printf("You entered the number three hundred\n");
                            break;
                        } else if(userNum % 300 == i+1) {
                            printf("You entered the number %s%s\n", hundreds[2], ones[i]);
                            break;
                        }
                    }

                // 310 - 319
                } else if(second == 1) {
                    // For loop to cycle through all ones digits
                    for(int i=0; i<9; i++) {
                        if(userNum % 310 == 0) {
                            printf("You entered the number three hundred and ten\n");
                            break;
                        } else if(userNum % 310 == 1) {
                            printf("You entered the number %seleven\n", hundreds[2]);
                            break;
                        } else if(userNum % 310 == 2) {
                            printf("You entered the number %stwelve\n", hundreds[2]);
                            break;
                        } else if(userNum % 310 == 3) {
                            printf("You entered the number %sthirteen\n", hundreds[2]);
                            break;
                        } else if(userNum % 310 == 5) {
                            printf("You entered the number %sfifteen\n", hundreds[2]);
                            break;
                        } else if(userNum % 310 == 8) {
                            printf("You entered the number %seighteen\n", hundreds[2]);
                            break;
                        } else if(userNum % 310 == i+1) {
                            printf("You entered the number %s%s%s\n", hundreds[2], ones[i], tens[0]);
                            break;
                        }
                    }

                // 320 - 399
                } else if(second >= 2 && second <= 9) {

                    // Tens
                    switch(userNum) 
                    {
                        case 320:
                            printf("You entered the number %s%s\n", hundreds[2], divisibleByTen[1]);
                            break;
                        case 330:
                            printf("You entered the number %s%s\n", hundreds[2], divisibleByTen[2]);
                            break;
                        case 340:
                            printf("You entered the number %s%s\n", hundreds[2], divisibleByTen[3]);
                            break;
                        case 350:
                            printf("You entered the number %s%s\n", hundreds[2], divisibleByTen[4]);
                            break;
                        case 360:
                            printf("You entered the number %s%s\n", hundreds[2], divisibleByTen[5]);
                            break;
                        case 370:
                            printf("You entered the number %s%s\n", hundreds[2], divisibleByTen[6]);
                            break;
                        case 380:
                            printf("You entered the number %s%s\n", hundreds[2], divisibleByTen[7]);
                            break;
                        case 390:
                            printf("You entered the number %s%s\n", hundreds[2], divisibleByTen[8]);
                            break;
                    }

                    // Loop to determine the rest of the numbers
                    for(int i=1; i<9; i++) {

                        for(int j=0; j<9; j++) {
                            // Variable to track which tens digit the number is on
                            int sum = 300 + ((i+1)*10);

                            if(userNum % sum == j+1) {
                                printf("You entered the number %s%s%s\n", hundreds[2], tens[i], ones[j]);
                                break;
                            }
                        }
                    }
                }

            // 400 - 499
            } else if(first >= 40 && first <= 49) {
                
                // Find second digit of int
                second = first % 10;

                // 200 - 209
                if(second == 0) {
                    // For loop to cycle through all ones digits
                    for(int i=0; i<9; i++) {
                        if(userNum % 400 == 0) {
                            printf("You entered the number four hundred\n");
                            break;
                        } else if(userNum % 400 == i+1) {
                            printf("You entered the number %s%s\n", hundreds[3], ones[i]);
                            break;
                        }
                    }

                // 410 - 419
                } else if(second == 1) {
                    // For loop to cycle through all ones digits
                    for(int i=0; i<9; i++) {
                        if(userNum % 410 == 0) {
                            printf("You entered the number four hundred and ten\n");
                            break;
                        } else if(userNum % 410 == 1) {
                            printf("You entered the number %seleven\n", hundreds[3]);
                            break;
                        } else if(userNum % 410 == 2) {
                            printf("You entered the number %stwelve\n", hundreds[3]);
                            break;
                        } else if(userNum % 410 == 3) {
                            printf("You entered the number %sthirteen\n", hundreds[3]);
                            break;
                        } else if(userNum % 410 == 5) {
                            printf("You entered the number %sfifteen\n", hundreds[3]);
                            break;
                        } else if(userNum % 410 == 8) {
                            printf("You entered the number %seighteen\n", hundreds[3]);
                            break;
                        } else if(userNum % 410 == i+1) {
                            printf("You entered the number %s%s%s\n", hundreds[3], ones[i], tens[0]);
                            break;
                        }
                    }

                // 420 - 499
                } else if(second >= 2 && second <= 9) {

                    // Tens
                    switch(userNum) 
                    {
                        case 420:
                            printf("You entered the number %s%s\n", hundreds[3], divisibleByTen[1]);
                            break;
                        case 430:
                            printf("You entered the number %s%s\n", hundreds[3], divisibleByTen[2]);
                            break;
                        case 440:
                            printf("You entered the number %s%s\n", hundreds[3], divisibleByTen[3]);
                            break;
                        case 450:
                            printf("You entered the number %s%s\n", hundreds[3], divisibleByTen[4]);
                            break;
                        case 460:
                            printf("You entered the number %s%s\n", hundreds[3], divisibleByTen[5]);
                            break;
                        case 470:
                            printf("You entered the number %s%s\n", hundreds[3], divisibleByTen[6]);
                            break;
                        case 480:
                            printf("You entered the number %s%s\n", hundreds[3], divisibleByTen[7]);
                            break;
                        case 490:
                            printf("You entered the number %s%s\n", hundreds[3], divisibleByTen[8]);
                            break;
                    }

                    // Loop to determine the rest of the numbers
                    for(int i=1; i<9; i++) {

                        for(int j=0; j<9; j++) {
                            // Variable to track which tens digit the number is on
                            int sum = 400 + ((i+1)*10);

                            if(userNum % sum == j+1) {
                                printf("You entered the number %s%s%s\n", hundreds[3], tens[i], ones[j]);
                                break;
                            }
                        }
                    }
                }

            // 500 - 599
            } else if(first >= 50 && first <= 59) {
                
                // Find second digit of int
                second = first % 10;

                // 500 - 509
                if(second == 0) {
                    // For loop to cycle through all ones digits
                    for(int i=0; i<9; i++) {
                        if(userNum % 500 == 0) {
                            printf("You entered the number five hundred\n");
                            break;
                        } else if(userNum % 500 == i+1) {
                            printf("You entered the number %s%s\n", hundreds[4], ones[i]);
                            break;
                        }
                    }

                // 510 - 519
                } else if(second == 1) {
                    // For loop to cycle through all ones digits
                    for(int i=0; i<9; i++) {
                        if(userNum % 510 == 0) {
                            printf("You entered the number five hundred and ten\n");
                            break;
                        } else if(userNum % 510 == 1) {
                            printf("You entered the number %seleven\n", hundreds[4]);
                            break;
                        } else if(userNum % 510 == 2) {
                            printf("You entered the number %stwelve\n", hundreds[4]);
                            break;
                        } else if(userNum % 510 == 3) {
                            printf("You entered the number %sthirteen\n", hundreds[4]);
                            break;
                        } else if(userNum % 510 == 5) {
                            printf("You entered the number %sfifteen\n", hundreds[4]);
                            break;
                        } else if(userNum % 510 == 8) {
                            printf("You entered the number %seighteen\n", hundreds[4]);
                            break;
                        } else if(userNum % 510 == i+1) {
                            printf("You entered the number %s%s%s\n", hundreds[4], ones[i], tens[0]);
                            break;
                        }
                    }

                // 520 - 599
                } else if(second >= 2 && second <= 9) {

                    // Tens
                    switch(userNum) 
                    {
                        case 520:
                            printf("You entered the number %s%s\n", hundreds[4], divisibleByTen[1]);
                            break;
                        case 530:
                            printf("You entered the number %s%s\n", hundreds[4], divisibleByTen[2]);
                            break;
                        case 540:
                            printf("You entered the number %s%s\n", hundreds[4], divisibleByTen[3]);
                            break;
                        case 550:
                            printf("You entered the number %s%s\n", hundreds[4], divisibleByTen[4]);
                            break;
                        case 560:
                            printf("You entered the number %s%s\n", hundreds[4], divisibleByTen[5]);
                            break;
                        case 570:
                            printf("You entered the number %s%s\n", hundreds[4], divisibleByTen[6]);
                            break;
                        case 580:
                            printf("You entered the number %s%s\n", hundreds[4], divisibleByTen[7]);
                            break;
                        case 590:
                            printf("You entered the number %s%s\n", hundreds[4], divisibleByTen[8]);
                            break;
                    }

                    // Loop to determine the rest of the numbers
                    for(int i=1; i<9; i++) {

                        for(int j=0; j<9; j++) {
                            // Variable to track which tens digit the number is on
                            int sum = 500 + ((i+1)*10);

                            if(userNum % sum == j+1) {
                                printf("You entered the number %s%s%s\n", hundreds[4], tens[i], ones[j]);
                                break;
                            }
                        }
                    }
                }

            // 600 - 699
            } else if(first >= 60 && first <= 69) {
                
                // Find second digit of int
                second = first % 10;

                // 600 - 609
                if(second == 0) {
                    // For loop to cycle through all ones digits
                    for(int i=0; i<9; i++) {
                        if(userNum % 600 == 0) {
                            printf("You entered the number six hundred\n");
                            break;
                        } else if(userNum % 600 == i+1) {
                            printf("You entered the number %s%s\n", hundreds[5], ones[i]);
                            break;
                        }
                    }

                // 610 - 619
                } else if(second == 1) {
                    // For loop to cycle through all ones digits
                    for(int i=0; i<9; i++) {
                        if(userNum % 610 == 0) {
                            printf("You entered the number six hundred and ten\n");
                            break;
                        } else if(userNum % 610 == 1) {
                            printf("You entered the number %seleven\n", hundreds[5]);
                            break;
                        } else if(userNum % 610 == 2) {
                            printf("You entered the number %stwelve\n", hundreds[5]);
                            break;
                        } else if(userNum % 610 == 3) {
                            printf("You entered the number %sthirteen\n", hundreds[5]);
                            break;
                        } else if(userNum % 610 == 5) {
                            printf("You entered the number %sfifteen\n", hundreds[5]);
                            break;
                        } else if(userNum % 610 == 8) {
                            printf("You entered the number %seighteen\n", hundreds[5]);
                            break;
                        } else if(userNum % 610 == i+1) {
                            printf("You entered the number %s%s%s\n", hundreds[5], ones[i], tens[0]);
                            break;
                        }
                    }

                // 620 - 699
                } else if(second >= 2 && second <= 9) {

                    // Tens
                    switch(userNum) 
                    {
                        case 620:
                            printf("You entered the number %s%s\n", hundreds[5], divisibleByTen[1]);
                            break;
                        case 630:
                            printf("You entered the number %s%s\n", hundreds[5], divisibleByTen[2]);
                            break;
                        case 640:
                            printf("You entered the number %s%s\n", hundreds[5], divisibleByTen[3]);
                            break;
                        case 650:
                            printf("You entered the number %s%s\n", hundreds[5], divisibleByTen[4]);
                            break;
                        case 660:
                            printf("You entered the number %s%s\n", hundreds[5], divisibleByTen[5]);
                            break;
                        case 670:
                            printf("You entered the number %s%s\n", hundreds[5], divisibleByTen[6]);
                            break;
                        case 680:
                            printf("You entered the number %s%s\n", hundreds[5], divisibleByTen[7]);
                            break;
                        case 690:
                            printf("You entered the number %s%s\n", hundreds[5], divisibleByTen[8]);
                            break;
                    }

                    // Loop to determine the rest of the numbers
                    for(int i=1; i<9; i++) {

                        for(int j=0; j<9; j++) {
                            // Variable to track which tens digit the number is on
                            int sum = 600 + ((i+1)*10);

                            if(userNum % sum == j+1) {
                                printf("You entered the number %s%s%s\n", hundreds[5], tens[i], ones[j]);
                                break;
                            }
                        }
                    }
                }

            // 700 - 799
            } else if(first >= 70 && first <= 79) {
                
                // Find second digit of int
                second = first % 10;

                // 700 - 709
                if(second == 0) {
                    // For loop to cycle through all ones digits
                    for(int i=0; i<9; i++) {
                        if(userNum % 700 == 0) {
                            printf("You entered the number seven hundred\n");
                            break;
                        } else if(userNum % 700 == i+1) {
                            printf("You entered the number %s%s\n", hundreds[6], ones[i]);
                            break;
                        }
                    }

                // 710 - 719
                } else if(second == 1) {
                    // For loop to cycle through all ones digits
                    for(int i=0; i<9; i++) {
                        if(userNum % 710 == 0) {
                            printf("You entered the number seven hundred and ten\n");
                            break;
                        } else if(userNum % 710 == 1) {
                            printf("You entered the number %seleven\n", hundreds[6]);
                            break;
                        } else if(userNum % 710 == 2) {
                            printf("You entered the number %stwelve\n", hundreds[6]);
                            break;
                        } else if(userNum % 710 == 3) {
                            printf("You entered the number %sthirteen\n", hundreds[6]);
                            break;
                        } else if(userNum % 710 == 5) {
                            printf("You entered the number %sfifteen\n", hundreds[6]);
                            break;
                        } else if(userNum % 710 == 8) {
                            printf("You entered the number %seighteen\n", hundreds[6]);
                            break;
                        } else if(userNum % 710 == i+1) {
                            printf("You entered the number %s%s%s\n", hundreds[6], ones[i], tens[0]);
                            break;
                        }
                    }

                // 720 - 799
                } else if(second >= 2 && second <= 9) {

                    // Tens
                    switch(userNum) 
                    {
                        case 720:
                            printf("You entered the number %s%s\n", hundreds[6], divisibleByTen[1]);
                            break;
                        case 730:
                            printf("You entered the number %s%s\n", hundreds[6], divisibleByTen[2]);
                            break;
                        case 740:
                            printf("You entered the number %s%s\n", hundreds[6], divisibleByTen[3]);
                            break;
                        case 750:
                            printf("You entered the number %s%s\n", hundreds[6], divisibleByTen[4]);
                            break;
                        case 760:
                            printf("You entered the number %s%s\n", hundreds[6], divisibleByTen[5]);
                            break;
                        case 770:
                            printf("You entered the number %s%s\n", hundreds[6], divisibleByTen[6]);
                            break;
                        case 780:
                            printf("You entered the number %s%s\n", hundreds[6], divisibleByTen[7]);
                            break;
                        case 790:
                            printf("You entered the number %s%s\n", hundreds[6], divisibleByTen[8]);
                            break;
                    }

                    // Loop to determine the rest of the numbers
                    for(int i=1; i<9; i++) {

                        for(int j=0; j<9; j++) {
                            // Variable to track which tens digit the number is on
                            int sum = 700 + ((i+1)*10);

                            if(userNum % sum == j+1) {
                                printf("You entered the number %s%s%s\n", hundreds[6], tens[i], ones[j]);
                                break;
                            }
                        }
                    }
                }

            // 800 - 899
            } else if(first >= 80 && first <= 89) {
                
                // Find second digit of int
                second = first % 10;

                // 800 - 809
                if(second == 0) {
                    // For loop to cycle through all ones digits
                    for(int i=0; i<9; i++) {
                        if(userNum % 800 == 0) {
                            printf("You entered the number eight hundred\n");
                            break;
                        } else if(userNum % 800 == i+1) {
                            printf("You entered the number %s%s\n", hundreds[7], ones[i]);
                            break;
                        }
                    }

                // 810 - 819
                } else if(second == 1) {
                    // For loop to cycle through all ones digits
                    for(int i=0; i<9; i++) {
                        if(userNum % 810 == 0) {
                            printf("You entered the number eight hundred and ten\n");
                            break;
                        } else if(userNum % 810 == 1) {
                            printf("You entered the number %seleven\n", hundreds[7]);
                            break;
                        } else if(userNum % 810 == 2) {
                            printf("You entered the number %stwelve\n", hundreds[7]);
                            break;
                        } else if(userNum % 810 == 3) {
                            printf("You entered the number %sthirteen\n", hundreds[7]);
                            break;
                        } else if(userNum % 810 == 5) {
                            printf("You entered the number %sfifteen\n", hundreds[7]);
                            break;
                        } else if(userNum % 810 == 8) {
                            printf("You entered the number %seighteen\n", hundreds[7]);
                            break;
                        } else if(userNum % 810 == i+1) {
                            printf("You entered the number %s%s%s\n", hundreds[7], ones[i], tens[0]);
                            break;
                        }
                    }

                // 820 - 899
                } else if(second >= 2 && second <= 9) {

                    // Tens
                    switch(userNum) 
                    {
                        case 820:
                            printf("You entered the number %s%s\n", hundreds[7], divisibleByTen[1]);
                            break;
                        case 830:
                            printf("You entered the number %s%s\n", hundreds[7], divisibleByTen[2]);
                            break;
                        case 840:
                            printf("You entered the number %s%s\n", hundreds[7], divisibleByTen[3]);
                            break;
                        case 850:
                            printf("You entered the number %s%s\n", hundreds[7], divisibleByTen[4]);
                            break;
                        case 860:
                            printf("You entered the number %s%s\n", hundreds[7], divisibleByTen[5]);
                            break;
                        case 870:
                            printf("You entered the number %s%s\n", hundreds[7], divisibleByTen[6]);
                            break;
                        case 880:
                            printf("You entered the number %s%s\n", hundreds[7], divisibleByTen[7]);
                            break;
                        case 890:
                            printf("You entered the number %s%s\n", hundreds[7], divisibleByTen[8]);
                            break;
                    }

                    // Loop to determine the rest of the numbers
                    for(int i=1; i<9; i++) {

                        for(int j=0; j<9; j++) {
                            // Variable to track which tens digit the number is on
                            int sum = 800 + ((i+1)*10);

                            if(userNum % sum == j+1) {
                                printf("You entered the number %s%s%s\n", hundreds[7], tens[i], ones[j]);
                                break;
                            }
                        }
                    }
                }

            // 900 - 999
            } else if(first >= 90 && first <= 99) {
                
                // Find second digit of int
                second = first % 10;

                // 900 - 909
                if(second == 0) {
                    // For loop to cycle through all ones digits
                    for(int i=0; i<9; i++) {
                        if(userNum % 900 == 0) {
                            printf("You entered the number nine hundred\n");
                            break;
                        } else if(userNum % 900 == i+1) {
                            printf("You entered the number %s%s\n", hundreds[8], ones[i]);
                            break;
                        }
                    }

                // 910 - 919
                } else if(second == 1) {
                    // For loop to cycle through all ones digits
                    for(int i=0; i<9; i++) {
                        if(userNum % 910 == 0) {
                            printf("You entered the number nine hundred and ten\n");
                            break;
                        } else if(userNum % 910 == 1) {
                            printf("You entered the number %seleven\n", hundreds[8]);
                            break;
                        } else if(userNum % 910 == 2) {
                            printf("You entered the number %stwelve\n", hundreds[8]);
                            break;
                        } else if(userNum % 910 == 3) {
                            printf("You entered the number %sthirteen\n", hundreds[8]);
                            break;
                        } else if(userNum % 910 == 5) {
                            printf("You entered the number %sfifteen\n", hundreds[8]);
                            break;
                        } else if(userNum % 910 == 8) {
                            printf("You entered the number %seighteen\n", hundreds[8]);
                            break;
                        } else if(userNum % 910 == i+1) {
                            printf("You entered the number %s%s%s\n", hundreds[8], ones[i], tens[0]);
                            break;
                        }
                    }

                // 920 - 999
                } else if(second >= 2 && second <= 9) {

                    // Tens
                    switch(userNum) 
                    {
                        case 920:
                            printf("You entered the number %s%s\n", hundreds[8], divisibleByTen[1]);
                            break;
                        case 930:
                            printf("You entered the number %s%s\n", hundreds[8], divisibleByTen[2]);
                            break;
                        case 940:
                            printf("You entered the number %s%s\n", hundreds[8], divisibleByTen[3]);
                            break;
                        case 950:
                            printf("You entered the number %s%s\n", hundreds[8], divisibleByTen[4]);
                            break;
                        case 960:
                            printf("You entered the number %s%s\n", hundreds[8], divisibleByTen[5]);
                            break;
                        case 970:
                            printf("You entered the number %s%s\n", hundreds[8], divisibleByTen[6]);
                            break;
                        case 980:
                            printf("You entered the number %s%s\n", hundreds[8], divisibleByTen[7]);
                            break;
                        case 990:
                            printf("You entered the number %s%s\n", hundreds[8], divisibleByTen[8]);
                            break;
                    }

                    // Loop to determine the rest of the numbers
                    for(int i=1; i<9; i++) {

                        for(int j=0; j<9; j++) {
                            // Variable to track which tens digit the number is on
                            int sum = 900 + ((i+1)*10);

                            if(userNum % sum == j+1) {
                                printf("You entered the number %s%s%s\n", hundreds[8], tens[i], ones[j]);
                                break;
                            }
                        }
                    }
                }

            }
     
        // User enters 0
        } else if(userNum == 0) {
            // User decides to quit
            exit++;
        }

    }

}