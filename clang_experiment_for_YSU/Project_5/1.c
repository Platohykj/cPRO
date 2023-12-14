#include <stdio.h>
#include <math.h>
int func(int a){
    int b = a - sin(a) - cos(a);
    return b;
}
int  main(){
    int max = 0;
    for (int i = 1; i < 21; ++i) {
        int b = func(i);
        if(b > max){
            max = b;
        }
    }
    printf("%d", max);
    return 0;
}