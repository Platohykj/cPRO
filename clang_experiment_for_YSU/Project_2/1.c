#include <stdio.h>
int  main(){
    char b[3];
    scanf("%s",b);
    if(b[0]==b[2]){
        printf("YES");
    }
        else{
            printf("NO");
        }
    return 0;
}