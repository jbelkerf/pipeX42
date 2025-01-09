#include "./libft/libft.h"
#include "./get_the_next_line/get_next_line.h"
#include "header.h"


int exec_mid(t_pip *pip)
{
    int i = 0;
    int pid;
    int pipfd[2];

    while (pip->cmd_numb < pip->cmd_total)
    {
        pipe(pipfd);
        pid = fork();
        if (pid == 0)
        {
            dup2(pipfd[1], STDOUT_FILENO);
            close(pipfd[0]);
            execve(check_cmd(pip->argv[pip->cmd_start + pip->cmd_numb], pip->envp), ft_split(pip->argv[pip->cmd_start + pip->cmd_numb], ' '), pip->envp);
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
        execve(check_cmd(pip->argv[pip->cmd_start + pip->cmd_numb], pip->envp), ft_split(pip->argv[pip->cmd_start + pip->cmd_numb], ' '), pip->envp);
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
        execve(check_cmd(pip->argv[pip->cmd_start + pip->cmd_numb], pip->envp), ft_split(pip->argv[pip->cmd_start + pip->cmd_numb], ' '), pip->envp);
    }
    else if (pid > 0)
    {
        dup2(pipfd[0], STDIN_FILENO);
        close(pipfd[1]);
        pip->cmd_numb++;
        return (exec_mid(pip));
    }
}


int main(int argc, char **argv, char **envp)
{
    int infd;
    int outfd;
    t_pip pip;
    int i;

    pip.argc = argc;
    pip.argv = argv;
    pip.cmd_numb = 1;
    pip.envp = envp;
    if (argc < 5)
    {
        ft_putstr_fd("Error: not enough arguments\n", 2);
        return 1;
    }
    pip.outfd = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0777);
    if (!ft_strcmp(argv[1], "here_doc"))
    {
        here_doc_it(&pip);
        pip.infd = open("read_in_line", O_RDONLY, 0777);
        pip.cmd_total = argc - 4;
        pip.cmd_start = 2;
        i = pip_it(&pip);
        unlink("read_in_line");
    }
    else
    {
        pip.cmd_total = argc - 3;
        pip.infd = open(argv[1], O_RDONLY, 0777);
        pip.cmd_start = 1;
        i = pip_it(&pip);
    }
    return i;
}
