/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 18:20:33 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/01/16 15:44:07 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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
	while (envp && envp[i])
	{
		if (!ft_strncmp("PATH=", envp[i], 5))
		{
			path_var = (*(envp + i) + 5);
			paths = ft_split2(path_var, ':');
			return (paths);
		}
		i++;
	}
	return (NULL);
}

char	*check_cmd(char *cmd, char **envp, int i)
{
	char	**paths;
	char	*pcmd;
	char	*tmp;

	paths = ft_split3(cmd, "\'\" \t");
	if (paths == NULL || paths[0] == NULL)
		return (free(paths), NULL);
	if (access(paths[0], X_OK) != -1)
		return (tmp = ft_strdup(paths[0]), free_array(paths), tmp);
	pcmd = ft_strdup(paths[0]);
	cmd = pcmd;
	free_array(paths);
	paths = extract_pathvariable(envp);
	while (paths && paths[++i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], cmd);
		free(tmp);
		if (access(paths[i], X_OK) != -1)
			return (tmp = ft_strdup(paths[i]), free_array(paths), tmp);
	}
	if (paths == NULL)
		return (free(cmd), NULL);
	return (command_not_found(pcmd), NULL);
}
