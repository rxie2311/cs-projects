/* Reverses a series of numbers */
 
#include <stdio.h>
 
#define N 10

// Macro trick for sizeof command to determine array length
#define SIZE ((int) (sizeof(a) / sizeof(a[0])))
 
int main(void)
{

    int a[N], i;

    printf("Enter %d numbers: ", N);
    // Replace N with SIZE macro
    for (i = 0; i < SIZE; i++)
        scanf("%d", &a[i]);
    
    printf("In reverse order:");
    // Replace N with SIZE macro
    for (i = SIZE - 1; i >= 0; i--)
        printf(" %d", a[i]);
    printf("\n");
    
    return 0;

}