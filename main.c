#include <stdio.h>
#include "header.h"

int main()
{
    char **str = ft_split3("awk '{hy} {hy}'", "' ");
    int i = 0;
    while (str[i])
    {
        printf("->> %s\n", str[i]);
        i++;
    }
    return 0;
}