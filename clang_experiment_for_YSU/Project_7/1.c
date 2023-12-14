#include <stdio.h>
#define MAX 100
char * star1(char * star, const char * star2)
{

    char * temp;
    temp = star;
    while (*temp != '\0')
        temp++;
    while ((*temp++ = *star2++) != '\0')
        continue;
    return star;
}
char * s_gets(char * star, int n)
{
    char * ret_val;
    int i = 0;
    ret_val = fgets(star, n, stdin);
    if (ret_val)
    {
        while (star[i] != '\n' && star[i] != '\0')
            i++;
        if (star[i] == '\n')
            star[i] = '\0';
        else
            while (getchar() != '\n')
                continue;
    }
    return ret_val;
}
int  main(){
    char star[MAX];
    char star2[MAX];
    s_gets(star, MAX);
    s_gets(star2, MAX);
    puts(star1(star, star2));
    return 0;
}
