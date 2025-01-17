/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:02:34 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/01/16 16:51:25 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	free_and_true(char *str)
{
	free(str);
	str = NULL;
	return (1);
}

void	error(char *str)
{
	ft_putstr_fd("JBash: ", 2);
	ft_putstr_fd(str, 2);
	perror(" ");
	exit(EXIT_FAILURE);
}

void	execute_the_child(int *pipfd, t_pip *pip)
{
	char	**argm;
	char	*cmd;
	close(pipfd[0]);
	cmd = check_cmd(pip->argv[pip->cmd_start + pip->cmd_numb], pip->envp);
	argm = ft_split3(pip->argv[pip->cmd_start + pip->cmd_numb], "\" \t\'");
	if (argm && cmd == NULL )
	{
		if (argm[0] == NULL)
			cmd = ft_strdup("");
		else
			cmd = ft_strdup(argm[0]);
	}
	execve_2(cmd, argm, pip->envp);
	free_array(argm);
	error_cmd(cmd);
}

void	close_2(int fd1, int fd2)
{
	close(fd1);
	close(fd2);
}

int	is_set(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}
