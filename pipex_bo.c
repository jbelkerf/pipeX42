#include "./libft/libft.h"
#include "./get_the_next_line/get_next_line.h"
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
void here_doc_it(t_pip *pip)
{
    int fd1;
    int fd2;
    char *str;
    char c;

    fd1 = open("read_in_file", O_WRONLY | O_TRUNC | O_CREAT , 0777);
    fd2 = open("read_in_file", O_RDONLY  , 0777);
    while (1)
    {
        read(0, &c, 1);
        write(fd1, &c, 1);
        if (c == '\n')
        {
            c = 0;
            str = get_next_line(fd2);
            str[ft_strlen(str) - 1] = 0;

            if (!ft_strcmp(str, pip->argv[2]))
            {
                close(fd1);
                return;
                break;
            }
        }
    }
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
        return (exec_mid(pip));
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
    if (!ft_strcmp(argv[1], "here_doc"))
        here_doc_it(&pip);
    else
    {
        pip.infd = open(argv[1], O_RDONLY, 0777);
        pip.outfd = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0777);
        pip_it(&pip);
    }
    return 0;
}
