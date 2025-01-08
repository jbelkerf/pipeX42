#include "./libft/libft.h"
#include "./get_the_next_line/get_next_line.h"
#include "header.h"

void print_prompt(void)
{
    write(1, "pipe here_doc> ", 15);
}

int pip_it1(t_pip *pip)
{
    int pipfd[2];
    int fd1;
    int fd2;
    int pid;

    fd1 = open("read_in_line", O_RDONLY, 0777);
    fd2 = open(pip->argv[5], O_WRONLY | O_APPEND | O_CREAT, 0777);
    pipe(pipfd);
    pid = fork();
    if (pid == 0)
    {
        dup2(pipfd[1], STDOUT_FILENO);
        dup2(fd1, STDIN_FILENO);
        close(pipfd[0]);
        close(pipfd[1]);
        execve(check_cmd(pip->argv[3], pip->envp), ft_split(pip->argv[3], ' '), pip->envp);
    }
    else if (pid > 0)
    {
        unlink("read_in_line");
        dup2(pipfd[0], STDIN_FILENO);
        dup2(fd2, STDOUT_FILENO);
        close(pipfd[1]);
        close(pipfd[0]);
        execve(check_cmd(pip->argv[4], pip->envp), ft_split(pip->argv[4], ' '), pip->envp);
    }
}

void clear_delemeter(t_pip *pip)
{
    int fd1;
    int fd2;
    char *str;

    fd1 = open("read_line", O_RDONLY, 0777);
    fd2 = open ("read_in_line", O_WRONLY | O_CREAT | O_TRUNC, 0777);
    while (1)
    {
        str = get_next_line(fd1);
        if (str)
        {
            str[ft_strlen(str) - 1] = 0;
            if (!ft_strcmp(str, pip->argv[2]))
                break;
            else
            {
                str[ft_strlen(str)] = '\n';
                write(fd2, str, ft_strlen(str));
            }
        }
        else
            break;     
    }
    unlink("read_line");
}

void here_doc_it(t_pip *pip)
{
    int fd1;
    int fd2;
    char *str;
    char c;
    int i = 0;

    fd1 = open("read_line", O_WRONLY | O_TRUNC | O_CREAT , 0777);
    fd2 = open("read_line", O_RDONLY  , 0777);
    print_prompt();
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
                break;
            }
             print_prompt();
        }
    }
    clear_delemeter(pip);
}
