#include <stdio.h>
#include <string.h>

int is_all_asterisks(char *p)
{
    int i;

    i = 0;
    while (p[i] && p[i] == '*')
        i++;
    if (p[i] == 0)
        return 1;
    else
        return 0;
}

int skip_wildcards(char *p)
{
    int i;

    i = 0;
    while (p[i] && p[i] == '*')
        i++;
    return i;
}

int go_to(char *s, char *pattern)
{
    // This should go to the last occurence
    int i;
    int len;
    char c;
    int count;

    c = *pattern;

    // Should count how many I should get from the end!
    len = strlen(pattern);
    i = len-1;
    count = 1;
    while (&pattern[i] != pattern)
    {
        if (pattern[i] == c)
            count++;
        i--;
    }

    i = 0;
    // should be changed to ft_strlen
    len = strlen(s);
    i = len-1;
    while (count--)
    {
        while (&s[i] != s && s[i] != c)
        {
            i--;
        }
        if (&s[i] == s)
            return -1;
        i--;
    }
    return i + 1;
}
int is_matching(char *s, char *pattern)
{
    int i;
    int j;
    char c;

    i = 0;
    j = 0;

    if (is_all_asterisks(pattern))
    // it match is all are asterisks.
        return 1;
    else
    {
        while (1)
        {
            if (s[j] == 0 && pattern[i] == 0)
                return 1;
            while (s[j] && pattern[i] && s[j] == pattern[i] && pattern[i] != '*')
            {
                j++;
                i++;
            }
            if (s[j] == 0)
                return 1;
            else if (is_all_asterisks(&pattern[i]))
                return 1;
            else if (pattern[i] == '*')
            {
                i += skip_wildcards(&pattern[i]);
                j += go_to(&s[j], &pattern[i]);
                i++;
                j++;
                if (j == -1)
                    return 0;
            }
            else
                return 0;
        }
    }

}

int main()
{
    printf("%d\n", is_matching("baaabab", "b*a***bab"));
}