#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

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
	char *path[] = {"/bin/", "/sbin/", NULL};
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

int main()
{
	char *path_cmd = check_cmd("ls");
	char *arg[] = {"ls", NULL};
	printf("%s\n", path_cmd);
	execve(path_cmd, arg, NULL);
	return (0);
}