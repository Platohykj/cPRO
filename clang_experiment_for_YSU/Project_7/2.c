#include <stdio.h>
#define MAX 100
char * s_gets(char * star, int n);
char * s_switch(char * star);
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
char * s_switch(char * star)
{
    int i = 0;
    while (star[i] != '\0')
    {
        if (star[i] >= 'a' && star[i] <= 'z')
            star[i] = star[i] - 31;
        else if (star[i] >= 'A' && star[i] <= 'Z')
            star[i] = star[i] + 31;
        i++;
    }
    return star;
}
//转换为大写并向后移动一个字符后输出
int  main(){
    char star[MAX];
    s_gets(star, MAX);
    puts(s_switch(star));
    return 0;
}
