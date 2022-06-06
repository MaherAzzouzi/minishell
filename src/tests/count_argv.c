#include <stdio.h>

int main(int argc, char **argv)
{
    int i = 0;
    while(argv[i])
    {
        printf("%s\n", argv[i]);
        i++;
    }
}