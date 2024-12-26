#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*re;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	re = (char *)malloc((strlen(s1) + strlen(s2) + 1) * sizeof(char));
	if (re == NULL)
		return (NULL);
	strlcpy(re, s1, strlen(s1) + 1);
	strlcat(re, s2, strlen(s1) + strlen(s2) + 1);
	return (re);
}

char *check_cmd(char *cmd)
{
	char *path[] = {"/bin/", "/sbin/", "/usr/bin/", NULL};
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
	int fd2;
	char *cmd1;
	char *cmd2;
	char *arg1[] = {argv[2], argv[1], NULL};
	char *arg2[] = {argv[3], argv[4], NULL};
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
	cmd1 = check_cmd(argv[2]);
	cmd2 = check_cmd(argv[3]);
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
		execve(cmd1, arg1, NULL);
	else
		execve(cmd2, arg2, NULL);
	return (0);
}
