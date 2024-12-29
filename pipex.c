#include "header.h"

char *check_cmd(char *cmd, char **envp)
{
	char *path;
	char **paths;
	int i = 0;
	int fd;

	while (envp[i])
	{
		if (!ft_strncmp("PATH", envp[i], 4))
			path = envp[i];
		i++;
	}
	path = path +5;
	i = 0;
	paths = ft_split2(path, ':');
	while (paths[i])
	{
		paths[i] = ft_strjoin(paths[i], cmd);
		fd = access(paths[i], X_OK);
		if (fd != -1)
			return (paths[i]);
		i++;
	}
	return (NULL);
}

int main(int argc, char *argv[], char *envp[])
{
	int fd1;
	int fd2;
	int pipefd[2];
	char str[1024];
	char *cmd1;
	char *cmd2;
	char **arg1 = ft_split(argv[2], ' ');
	char **arg2 = ft_split(argv[3], ' ');
	int pid;

	if (argc != 5)
	{

		printf("too much or too few args");
		return (1);
	}
	pipe(pipefd);
	fd1 = access(argv[1], F_OK);
	fd2 = access(argv[4], F_OK);
	if (fd1 == -1 || fd2 == -1)
	{
		printf("%d\n",errno);
		perror("Error :");
		return (2);
	}
	cmd1 = check_cmd(arg1[0], envp);
	cmd2 = check_cmd(arg2[0], envp);
	if (!cmd1 || !cmd2)
	{
		printf("invalid command\n");
		return 3;
	}
	pid = fork();
	if (pid < 0)
	{
		perror("Fork failed");
	}
	else if (pid == 0)
	{
		fd1 = open(argv[1], O_RDONLY);
		dup2(fd1 , 0);
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		close(fd1);
		execve(cmd1, arg1, NULL);
	}
	else
	{
		fd2 = open(argv[4], O_TRUNC | O_WRONLY);
		dup2(fd2, 1);
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		close(fd2);
		execve(cmd2, arg2, NULL);
	}
	return (0);
}
