typedef struct main
{
    char *argv;
    char *p;
    /* data */
} t_shit;

// void func(t_shit *p)
// {
//     printf("%c  %d \n", p->v, p->k);
//     p->k = 4;
// }
int main(int argc, char *argv[])
{
  t_shit p;
//   p.v = 6;
//   p.k = 3;
//   func(&p);
//   printf("%c  %d \n", p.v, p.k);
  printf("%d", sizeof(t_shit));
}