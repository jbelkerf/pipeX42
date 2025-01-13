/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:02:34 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/01/11 16:51:37 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	execute_the_child(int *pipfd, t_pip *pip)
{
	char	**argm;
	char	*cmd;

	close(pipfd[0]);
	cmd = check_cmd(pip->argv[pip->cmd_start + pip->cmd_numb], pip->envp);
	argm = ft_split(pip->argv[pip->cmd_start + pip->cmd_numb], ' ');
	execve_2(cmd, argm, pip->envp);
	free_array(argm);
	error_cmd(cmd);
}

void	close_final(void)
{
	close(1);
	close(0);
}

void	close_2(int fd1, int fd2)
{
	close(fd1);
	close(fd2);
}
