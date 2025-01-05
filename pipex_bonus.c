#include "header_bonus.h"
#include "./libft/libft.h"

void error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

void exec_parent(t_pipe *pip)
{
	char	*cmd;
	int		fd;
    printf("\nparent dkhal cmd: %d\n", pip->cmd_number);
    printf("pipe %d %d\n", pip->pipfd[pip->pip_read][0], pip->pipfd[pip->pip_read][1]);
    write(1,"NN", 2);
	cmd = check_cmd(pip->argv[pip->cmd_number + 1], pip->envp);
	printf("%s\n", cmd);
	close(pip->pipfd[pip->pip_read][1]);
	fd = open(pip->argv[pip->argc - 1], O_TRUNC | O_WRONLY | O_CREAT, 0777);
	if (fd == -1)
		error();
	dup2(fd, STDOUT_FILENO);
	//close(fd);
	dup2(pip->pipfd[pip->pip_read][0], STDIN_FILENO);
	execve(cmd, ft_split(pip->argv[pip->cmd_number + 1], ' '), pip->envp);
	error();
}

void exec_middle(t_pipe *pip)
{
    char    *cmd;

    printf("\nmiddle dkhal cmd: %d\n", pip->cmd_number);
    printf("pipe read %d %d\n", pip->pipfd[pip->pip_read][0], pip->pipfd[pip->pip_read][1]);
    printf("pipe write %d %d\n", pip->pipfd[pip->pip_write][0], pip->pipfd[pip->pip_write][1]);
    
    cmd = check_cmd(pip->argv[pip->cmd_number + 1], pip->envp);
    printf("%s\n", cmd);
    close(pip->pipfd[pip->pip_read][1]);
    close(pip->pipfd[pip->pip_write][0]);
    dup2(pip->pipfd[pip->pip_read][0], STDIN_FILENO);
    dup2(pip->pipfd[pip->pip_write][1], STDOUT_FILENO);
    execve(cmd, ft_split(pip->argv[pip->cmd_number + 1], ' '), pip->envp);
    error();
}

void exec_child(t_pipe *pip)
{
	char	*cmd;
	int		fd;
    printf("\nchilde dkhal cmd: %d\n", pip->cmd_number);
    printf("pipe %d %d\n", pip->pipfd[pip->pip_write][0], pip->pipfd[pip->pip_write][1]);
	cmd = check_cmd(pip->argv[pip->cmd_number + 1], pip->envp);
	printf("%s\n", cmd);
		
        close(pip->pipfd[pip->pip_write][0]);
		fd = open(pip->argv[1], O_RDONLY, 0777);
		if (fd == -1)
			error();
		dup2(fd, STDIN_FILENO);
		//close(fd);
		dup2(pip->pipfd[pip->pip_write][1], STDOUT_FILENO);
	execve(cmd, ft_split(pip->argv[pip->cmd_number + 1], ' '), pip->envp);
	error();
}

void pipeit(t_pipe *pip)
{
    int pid;
    int i = 1;

    while (pip->cmd_number > 0)
    {
        //printf("%d -> %d\n", pip->cmd_number, i);
        pid = fork();
        if (pid == 0)
        {
            if (i == 1)
            {
                pip->cmd_number = i;
                exec_child(pip);
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
                pip->cmd_number = i;
                pip->pip_read = i - 2;
                exec_parent(pip);
            }
        }
        else if (pid > 0)
        {
           //waitpid(pid, NULL, 0);
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
        printf("pipe-%d: %d %d\n", i, pip->pipfd[i][0], pip->pipfd[i][1]);
        i++;
    }
   // if (!ft_strncmp(argv[1], "here_doc", 8))
       // here_docit(argc, argv, envp);
       pipeit(pip);   
}
