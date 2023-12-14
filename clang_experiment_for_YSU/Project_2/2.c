#include <stdio.h>
double fact(int a);
double b;
double fact(int a){
    switch (a) {
        case 1:
            b = 0.5;
            break;
        case 2:
            b = 1.5;
            break;
        case 3:
            b = 2.5;
            break;
        case 4:
            b = 3.5;
            break;
        default:
            printf("Error!"
                   "Please enter a number between 1 and 4.");
            scanf("%d",&a);
            fact(a);
    }
    return b;
}
int  main(){
    printf("Car is 1.\n"
           "Bus is 2.\n"
           "Small Truck is 3.\n"
           "Large Truck is 4.\n"
           "Please enter a number:");
    int a;
    scanf("%d",&a);
    fact(a);
    printf("Please enter the distance:");
    double c;
    scanf("%lf",&c);
    printf("The cost is %lf",c*b);
    return 0;
}