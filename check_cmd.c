/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 18:20:33 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/01/10 20:35:37 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	error(char *str)
{
	perror("JBash");
	ft_putendl_fd(str, 2);
	exit(EXIT_FAILURE);
}

void	free_array(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		free(str[i]);
		i++;
	}
}

char	**extract_pathvariable(char **envp)
{
	char	*path_var;
	char	**paths;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp("PATH", envp[i], 4))
			path_var = envp[i];
		i++;
	}
	path_var = path_var +5;
	paths = ft_split2(path_var, ':');
	return (paths);
}

char	*check_cmd(char *cmd, char **envp)
{
	char	**paths;
	int		i;
	int		fd;
	char	*pcmd;
	char	*tmp;

	i = 0;
	paths = ft_split(cmd, ' ');
	pcmd = ft_strdup(paths[0]);
	cmd = pcmd;
	free_array(paths);
	paths = extract_pathvariable(envp);
	while (paths[i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], cmd);
		free(tmp);
		fd = access(paths[i], X_OK);
		if (fd != -1)
			return (paths[i]);
		i++;
	}
	return (pcmd);
}
