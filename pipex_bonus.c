#include "header_bonus.h"
#include "./libft/libft.h"

void error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

void exec_parent(char *argv[], char *envp[], int *pipefd, int cmd_numb)
{
	char	*cmd;
	int		fd;

	cmd = check_cmd(argv[cmd_numb + 1], envp);
	
	close(pipefd[1]);
	fd = open(argv[cmd_numb + 2], O_TRUNC | O_WRONLY | O_CREAT, 0777);
	if (fd == -1)
		error();
	dup2(fd, STDOUT_FILENO);
	//close(fd);
	dup2(pipefd[0], STDIN_FILENO);
	execve(cmd, ft_split(argv[cmd_numb + 1], ' '), envp);
	error();
}

void exec_middle(t_pipe *pip)
{
    char    *cmd;

    cmd = check_cmd(pip->argv[pip->cmd_number + 1], pip->envp);
    close(pip->pipfd[pip->pip_read][1]);
    close(pip->pipfd[pip->pip_write][0]);
    dup2(pip->pipfd[pip->pip_read][0], STDIN_FILENO);
    dup2(pip->pipfd[pip->pip_write][1], STDOUT_FILENO);
    execve(cmd, ft_split(pip->argv[pip->cmd_number + 1], ' '), pip->envp);
    error();
}

void exec_child(char *argv[], char *envp[], int *pipefd, int cmd_numb)
{
	char	*cmd;
	int		fd;
	cmd = check_cmd(argv[cmd_numb + 1], envp);
	
		
        close(pipefd[0]);
		fd = open(argv[1], O_RDONLY, 0777);
		if (fd == -1)
			error();
		dup2(fd, STDIN_FILENO);
		//close(fd);
		dup2(pipefd[1], STDOUT_FILENO);
	execve(cmd, ft_split(argv[cmd_numb + 1], ' '), envp);
	error();
}

void pipeit(t_pipe *pip)
{
   printf("%s\n",pip->argv[pip->cmd_number + 1]);
    int pid;
    if (pip->cmd_number > 1)
    {
        pipe(pip->pipfd[pip->pip_write - 1]);
        pip->pip_read = pip->pip_read - 1;
        pid = fork();
        if (pid == 0)
        {
            pip->cmd_number = pip->cmd_number - 1;
            pip->pip_write = pip->pip_read;
            pipeit(pip);
        }
        else if (pid > 0)
        {
            waitpid(pid, NULL, 0);
            exec_middle(pip);
        }
        else
            error();
    }
    else if (pip->cmd_number == 1)
    {
        exec_child(pip->argv, pip->envp, pip->pipfd[pip->pip_write], pip->cmd_number);
        error();
    }
}

int main(int argc, char *argv[], char *envp[])
{
    int pid;
    t_pipe  *pip;
    int     **pipefd;
    int i = 0;

    pipefd = malloc((argc - 3) * sizeof(int *));
    while (i < argc - 3)
    {
        pipefd[i] = malloc(2 * sizeof(int));
        i++;
    }
    pip = malloc(sizeof(t_pipe));
    pip->pipfd = pipefd;
    pip->argv = argv;
    pip->argc = argc;
    pip->envp = envp;
    pip->cmd_number = argc - 3;
   // if (!ft_strncmp(argv[1], "here_doc", 8))
       // here_docit(argc, argv, envp);
        pipe(pip->pipfd[pip->cmd_number - 2]);
        pid = fork();
        if (pid == 0)
        {
            pip->pip_write = pip->cmd_number - 2;
            pip->cmd_number = pip->cmd_number - 1;
            pipeit(pip);
        }
        else if (pid > 0)
        {
            waitpid(pid, NULL, 0);
            exec_parent(pip->argv, pip->envp, pip->pipfd[pip->cmd_number - 2], pip->cmd_number);
        }   
}
