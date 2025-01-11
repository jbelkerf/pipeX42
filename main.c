#include <stdlib.h>

int main()
{
  char *str = malloc(4 * sizeof(char));
  str = malloc(5 * sizeof(char));
  system("leaks a.out");
}
