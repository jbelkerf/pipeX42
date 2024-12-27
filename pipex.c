#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "libft/libft.h"
#include <fcntl.h>

char *check_cmd(char *cmd)
{
	char *path[] = {"/bin/", "/sbin/", "/usr/bin/", "/usr/sbin/", "/usr/local/bin/",NULL};
	int i = 0;
	int fd;

	while (path[i])
	{
		path[i] = ft_strjoin(path[i], cmd);
		i++;
	}
	i = 0;
	while (path[i])
	{
		fd = access(path[i], X_OK);
		if (fd != -1)
			return (path[i]);
		i++;
	}
	return (NULL);
}

int main(int argc, char *argv[])
{
	int fd1;
	char str[1024];
	int fd2;
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
	fd1 = access(argv[1], F_OK);
	fd2 = access(argv[4], F_OK);
	if (fd1 == -1 || fd2 == -1)
	{
		printf("%d\n",errno);
		perror("Error :");
		return (2);
	}
	cmd1 = check_cmd(arg1[0]);
	cmd2 = check_cmd(arg2[0]);
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
		close(fd1);
		execve(cmd1, arg1, NULL);
	}
	else
	{
		fd2 = open(argv[4], O_WRONLY);
		dup2(fd2, 1);
		close(fd2);
		execve(cmd2, arg2, NULL);
	}
	return (0);
}
