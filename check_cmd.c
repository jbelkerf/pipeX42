/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 18:20:33 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/01/03 21:31:32 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "./libft/libft.h"

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
	char	*path;
	char	**paths;
	int		i;
	int		fd;

	i = 0;
	paths = ft_split(cmd, ' ');
	cmd = paths[0];
	paths = extract_pathvariable(envp);
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
