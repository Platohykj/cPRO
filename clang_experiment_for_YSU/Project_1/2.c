#include <stdio.h>
int main() {
    int a;
    scanf("%d",&a);
    int b[3];
    b[0] = a/100;
    b[1] = (a-b[0]*100)/10;
    b[2] = (a-b[0]*100-b[1]*10);
    for (int i = 0; i < 3; i++) {
        b[i] = (b[i]+6)%10;
    }
    int temp;
    temp = b[0];
    b[0] = b[2];
    b[2] = temp;
    for (int j = 0; j < 3; j++) {
        printf("%d",b[j]);
    }
    return 0;
}