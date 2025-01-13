/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 18:20:33 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/01/13 10:15:57 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	error(char *str)
{
	ft_putstr_fd("JBash: ", 2);
	ft_putstr_fd(str, 2);
	perror(" ");
	exit(EXIT_FAILURE);
}

void	error_cmd(char *str)
{
	ft_putstr_fd("JBash: ", 2);
	ft_putstr_fd(str, 2);
	perror(" ");
	free(str);
	exit(EXIT_FAILURE);
}

void	command_not_found(char *cmd)
{
	ft_putstr_fd("JBash: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	free(cmd);
	exit(127);
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
	free(str);
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
		{
			path_var = *(envp + i ) + 5;
			paths = ft_split2(path_var, ':');
			return (paths);
		}
		i++;
	}
	return (NULL);
}

char	*check_cmd(char *cmd, char **envp)
{
	char	**paths;
	int		i;
	char	*pcmd;
	char	*tmp;

	i = 0;
	if (access(cmd, X_OK) != -1)
		return (cmd);
	paths = ft_split(cmd, ' ');
	pcmd = ft_strdup(paths[0]);
	cmd = pcmd;
	free_array(paths);
	paths = extract_pathvariable(envp);
	while (paths && paths[i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], cmd);
		free(tmp);
		if (access(paths[i], X_OK) != -1)
			return (paths[i]);
		i++;
	}
	return (free_array(paths), NULL);
}
