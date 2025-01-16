/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:20:10 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/01/16 11:20:21 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	set_1(t_pip *pip, int argc, char **argv, char **envp)
{
	pip->argc = argc;
	pip->argv = argv;
	pip->cmd_numb = 1;
	pip->envp = envp;
}

void	set_2(t_pip *pip, char *file_path, int option)
{
	char	*file;

	file = pip->argv[pip->argc - 1];
	if (option == 2)
	{
		pip->infd = open(file_path, O_RDONLY, 0777);
		pip->cmd_start = 2;
		file = pip->argv[pip->argc - 1];
		pip->outfd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0666);
	}
	else if (option == 1)
	{
		pip->infd = open(file_path, O_RDONLY, 0777);
		pip->cmd_start = 1;
		pip->outfd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	}
	if (pip->infd == -1)
		error("file_path");
}

void	dup_3(int a, int b)
{
	int	i;

	i = dup2(a, b);
	if (i == -1)
		error("dup2");
	close(a);
}

void	pipe_2(int *pipefd)
{
	if (pipe(pipefd) == -1)
		error("pipe");
}

void	execve_2(char *cmd, char **argm, char **envp)
{
	execve(cmd, argm, envp);
	free_array(argm);
	error(cmd);
}
