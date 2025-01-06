#include "./libft/libft.h"
#include "header_bonus.h"

typedef struct ap{
    int infd;
    int outfd;
    int argc;
    char **argv;
    char **envp;
    int cmd_numb;
}   t_pip;

int exec_mid(t_pip *pip)
{
    int i = 0;
    int pid;
    int pipfd[2];

    while (pip->cmd_numb < pip->argc - 3)
    {
        pipe(pipfd);
        pid = fork();
        if (pid == 0)
        {
            dup2(pipfd[1], STDOUT_FILENO);
            close(pipfd[0]);
            execve(check_cmd(pip->argv[pip->cmd_numb + 1], pip->envp), ft_split(pip->argv[pip->cmd_numb + 1], ' '), pip->envp);
        }
        else if (pid > 0)
        {
            dup2(pipfd[0], STDIN_FILENO);
            close(pipfd[1]);
            pip->cmd_numb++;
        }
    }
    dup2(pip->outfd, STDOUT_FILENO);
    pid = fork();
    if (pid == 0)
        execve(check_cmd(pip->argv[pip->cmd_numb + 1], pip->envp), ft_split(pip->argv[pip->cmd_numb + 1], ' '), pip->envp);
    else
        return 0;
}

int pip_it(t_pip *pip)
{
    int pipfd[2];
    int pid;

    dup2(pip->infd, STDIN_FILENO);
    pipe(pipfd);
    dup2(pipfd[1], STDOUT_FILENO);
    pid = fork();
    if (pid == 0)
    {
        close(pipfd[0]);
        execve(check_cmd(pip->argv[2], pip->envp), ft_split(pip->argv[2], ' '), pip->envp);
    }
    else if (pid > 0)
    {
        dup2(pipfd[0], STDIN_FILENO);
        close(pipfd[1]);
        pip->cmd_numb++;
        exec_mid(pip);
    }
}
int main(int argc, char **argv, char **envp)
{
    int infd;
    int outfd;
    t_pip pip;

    pip.argc = argc;
    pip.argv = argv;
    pip.cmd_numb = 1;
    pip.envp = envp;
    pip.infd = open(argv[1], O_RDONLY, 0777);
    pip.outfd = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0777);
    pip_it(&pip);

    return 0;
}