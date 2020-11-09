#include <stdio.h>
#include "myfun.h"
 
int main()
{
    int a,b;
    int sum;
    float avg;
     
    printf("Enter first number: ");
    scanf("%d",&a);
    printf("Enter second number: ");
    scanf("%d",&b);
     
    /*calling sumOfNumbers()*/
    sum=sumOfNumbers(a,b);
     
    /*calling avgOfNumbers()*/
    avg=avgOfNumbers(a,b);
     
    printf("Sum: %d \nAverage: %f\n",sum,avg);
 
    return 0;
}