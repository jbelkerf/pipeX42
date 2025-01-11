/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ner-roui <ner-roui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 18:20:33 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/01/11 22:08:48 by ner-roui         ###   ########.fr       */
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

void	command_not_found(char *cmd)
{
	ft_putstr_fd("JBash: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	//free(cmd);
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

char	*extract_pathvariable(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp("PATH", envp[i], 4))
			return (*(envp + i ) + 5);
		i++;
	}
	
	return (NULL);
}

char	*check_cmd(char *cmd, char **envp)
{
	char	**paths;
	int		i;
	int		fd;
	char	*pcmd;
	char	*tmp;

	i = -1;
	paths = ft_split(cmd, ' ');
	pcmd = ft_strdup(paths[0]);
	cmd = pcmd;
	//free_array(paths);
	tmp = extract_pathvariable(envp);
	if (tmp == NULL)
		return NULL;
	paths = ft_split2(tmp , ':');
	while (paths[++i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], cmd);
		//free(tmp);
		fd = access(paths[i], X_OK);
		if (fd != -1)
			return (paths[i]);
	}
	//free_array(paths);
	return (command_not_found(pcmd), NULL);
}
