#include <stdio.h>
int fanc(int a){
    if(a%2==0)
        a=a/2;
    else
        a=3*a+1;
    if(a==1)
        return 1;
    else
        return fanc(a);
}
int  main(){
    int a;
    scanf("%d", &a);
    if(fanc(a)==1)
        printf("RIGHT");
    else
        printf("WRONG");
    return 0;
}