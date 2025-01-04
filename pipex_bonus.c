#include "header_bonus.h"
#include "./libft/libft.h"

void pipeit(int arg, char **argv, char **envp, int i)
{
    
}
int main(int argc, char *argv[], char *envp[])
{
    int i;
    int pipefd[argc - 4][2];

    i = 0;
    if (!ft_strncmp(argv[1], "here_doc", 8))
        here_docit(argc, argv, envp);
    pipeit(argc, argv, envp, i);
}