#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif

int my_strlen(char *s)
{
    int i = 0;
    while (s[++i]);
    return i;
}

char    *my_strchr(char *str, char c)
{
    int i = -1;
    while (str[++i])
        if (str[i] == c)
            return (str + i);
    return (0);
}

char    *my_strdup(char *s)
{
    char *dest = malloc(my_strlen(s) + 1);
    int i = -1;
    while(s[++i])
        dest[i] = s[i];
    dest[i] = 0;
    return (dest);
}

char *my_strjoin(char *s1, char *s2)
{
    if (!s1 || !*s1)
        return (my_strdup(s2));
    if (!s2 || !*s2)
        return (s1);
    char *dest = malloc(my_strlen(s1) + my_strlen(s2) + 1);
    int i = -1;
    while (s1[++i])
        dest[i] = s1[i];
    while (*s2)
        dest[i++] = *s2++;
    dest[i] = 0;
    free(s1);
    return (dest);
}

char    *my_substr(char *str, int start, int len)
{
    if (!str || !*str || len <= 0 || my_strlen(str) < start)
        return 0;
    if (my_strlen(str) <= len)
        return (my_strdup(str));
    char *dest = malloc(len + 1);
    int i = start;
    int j = 0;
    while (str[i] && i < len)
        dest[j++] = str[i++];
    dest[j] = 0;
    free(str);
    return (dest);
}

char    *get_line(char *str, char *line)
{
    if (!line)
    {
        // free(str);
        return (0);
    }
    return (my_substr(str, 0, line - str + 1));
}

char    *get_next_line(int fd)
{
    char buffer[BUFFER_SIZE + 1];
    static char *string;
    int reader = 1;

    while (reader)
    {
        reader = read(fd, buffer, BUFFER_SIZE);
        if (reader < 1)
            break;
        buffer[reader] = 0;
        string = my_strjoin(string, buffer);
        if (my_strchr(buffer, '\n'))
            break ;
    }
    if (!string)
        return (0);
    char *l = my_strchr(string, '\n');
    char *line = get_line(string, l);
    if (!line)
        return (string);
    // free(string);
    string = my_strdup(l + 1);
    return (line);
}

int main()
{
    int fd = open("get_next_line.c", O_RDONLY);
    char *line = get_next_line(fd);
    while (line) {
    line = get_next_line(fd);
    printf("%s", line);
    }
}