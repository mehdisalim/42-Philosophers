#include <stdlib.h>
#include <stdio.h>

void func(char *str)
{
    int i = -1;
    while (++i > -1)
    {
        printf("%d\n", i);
        str[i] = 'a';
    }
}

int main()
{
    char *str = malloc(1);
    str[0] = 'a';
    func(str);
    // char *str2 = malloc(1);
    // puts(str2);
    while (1);
}