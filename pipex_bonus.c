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
    printf("\nparent dkhal cmd: %d\n", cmd_numb);
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
    printf("\nmiddle dkhal cmd: %d\n", pip->cmd_number);
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
    printf("\nchilde dkhal cmd: %d\n", cmd_numb);
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
    int pid;
    int i = 1;

    while (pip->cmd_number >= 1)
    {
        pid = fork();
        if (pid == 0)
        {
            if (i == 1)
            {
                exec_child(pip->argv, pip->envp, pip->pipfd[i - 1], i );
            }
            else if (i < pip->argc - 3)
            {
                pip->pip_read = i - 2;
                pip->pip_write = i - 1;
                pip->cmd_number = i;
                exec_middle(pip);
            }
            else if (i == pip->argc - 3)
            {
                exec_parent(pip->argv, pip->envp, pip->pipfd[i - 1], i);
            }
        }
        else if (pid > 0)
        {
            pip->cmd_number--;
            i++;
        }
    }
}

int main(int argc, char *argv[], char *envp[])
{
    int pid;
    t_pipe  *pip;
    int     **pipefd;
    int i = 0;

    pipefd = malloc((argc - 2) * sizeof(int *));
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
    i = 0;
    while (i < pip->cmd_number)
    {
        pipe(pip->pipfd[i]);
        i++;
    }
   // if (!ft_strncmp(argv[1], "here_doc", 8))
       // here_docit(argc, argv, envp);
       pipeit(pip);   
}
