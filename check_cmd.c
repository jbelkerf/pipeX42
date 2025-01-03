#include "header.h"

char *check_cmd(char *cmd, char **envp)
{
	char *path;
	char **paths;
	int i = 0;
	int fd;

	paths = ft_split(cmd, ' ');
	cmd = paths[0];
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
	return ("mabghash");
}