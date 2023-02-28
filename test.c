#include <stdlib.h>

int main()
{
    char *str = malloc(10);
    // str++;
    free(str);
}