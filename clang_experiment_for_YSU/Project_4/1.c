#include <stdio.h>
int func(int a) {
    if (a >= 4)
        return 4;
    else
        return a;
}
int  main(){
    int a = 21;
    int b[21][2];
    int sum = 0;
    int round = 0;
    printf("Please enter a number from 1 to 4:\n");
    for (int i = 0;sum <= 21; ++i) {

        scanf("%d", &b[i][0]);
        if (b[i][0] > func(a - sum) || b[i][0] < 1)
        {
            printf("Please enter a number from 1 to %d:\n", func(a - sum));
            scanf("%d", &b[i][0]);
        }
        if(b[i][0] <= func(a - sum) || b[i][0] >= 1)
        {
            sum += b[i][0];
            b[i][1] = 5 - b[i][0];
            sum += b[i][1];
            round++;
            printf("The computer entered %d\n", b[i][1]);
            printf("The sum is %d\n", sum);
            printf("The remaining number is %d\n", a - sum);
            printf("Please enter a number from 1 to %d:\n", func(a - sum));

            }if(a - sum <= 4){
            scanf("%d", &b[i][0]);
            sum += b[i][0];
            b[i][1] = 0;
            sum += b[i][1];
            round++;
            if(a - sum == 0){
                printf("You lose!\n");
                break;
            }
        }

    }
    printf("Game over!\n");
    printf("The following is the game process:\n");
    for (int j = 0; j < round - 1; ++j) {
        printf("The %dth round: You entered %d, the computer entered %d\n", j + 1, b[j][0], b[j][1]);
    }
    return 0;
}