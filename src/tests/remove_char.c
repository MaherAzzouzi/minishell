#include <stdio.h>
#include <string.h>
char * remove_char(char *p, char c)
{
    int i;
    int j;

    i = 0;
    while (p[i])
    {
        if (p[i] == c)
        {
            j = i + 1;
            while (p[i] != 0)
            {
                p[i] = p[j];
                i++;
                j++;
            }
            p[i] = 0;
            i = -1;
        }
        i++;
    }
    return p;
}

int main()
{
    char *p = remove_char(strdup("wabaabaabbabbaabbaababababbaabaz"), 'a');
    printf("%s\n", p);
}