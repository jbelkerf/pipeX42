#include "get_next_line.h"

void    ft_putstr(char *str)
{
    int i;

    if (str == NULL)
        ft_putstr("ghjk");
    i = 0;
    while (str[i])
    {
        write(1, &str[i], 1);
        i++;
    }
}
#include <fcntl.h>
#include <stdio.h>
int main()
{
    int fd1, fd2;
    //int j = 0;
   // char *str;
    //int c;
    
    fd1 = open("file.txt", O_RDONLY);
    fd2 = open("file.txt", O_RDONLY);

   printf("%s",get_next_line(fd1));
   printf("%s",get_next_line(fd2));
   printf("%s",get_next_line(fd1));
   printf("%s",get_next_line(fd2));
   printf("%s",get_next_line(fd2));
   printf("%s",get_next_line(fd2));
   printf("%s",get_next_line(fd2));
   printf("%s",get_next_line(fd2));
   printf("%s",get_next_line(fd1));
   printf("%s",get_next_line(fd1));
   printf("%s",get_next_line(fd1));
   printf("%s",get_next_line(fd1));
   printf("%s",get_next_line(fd1));
   printf("%s",get_next_line(fd2));

}
