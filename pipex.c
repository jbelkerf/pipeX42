/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:04:54 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/01/16 11:09:13 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	do_thing(t_pip *pip)
{
	char	**argv;
	char	*cmd;

	cmd = check_cmd(pip->argv[pip->cmd_start + pip->cmd_numb], pip->envp);
	argv = ft_split3(pip->argv[pip->cmd_start + pip->cmd_numb], "\' \"");
	if (cmd == NULL)
		cmd = ft_strdup(argv[0]);
	execve(cmd, argv, pip->envp);
	free_array(argv);
	error_cmd(cmd);
	return (1);
}

void	exec_mid(t_pip *pip)
{
	int		pid;
	char	*path;

	path = pip->argv[pip->argc - 1];
	pip->outfd = open(path, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (pip->outfd == -1)
		error(pip->argv[pip->argc - 1]);
	dup_3(pip->outfd, STDOUT_FILENO);
	pid = fork();
	if (pid == 0)
		do_thing(pip);
	else if (pid == -1)
		error("fork");
	else
		waitpid(pid, &pip->last_pid, 0);
}

void	pip_it(t_pip *pip)
{
	int		pipfd[2];

	dup_3(pip->infd, STDIN_FILENO);
	pipe_2(pipfd);
	dup_3(pipfd[1], STDOUT_FILENO);
	pip->pid = fork();
	if (pip->pid == 0 && (!close(pipfd[0])) && (do_thing(pip)))
		;
	else if (pip->pid > 0)
	{
		dup_3(pipfd[0], STDIN_FILENO);
		pip->cmd_numb++;
		exec_mid(pip);
	}
	else if (pip->pid == -1)
		error("fork");
}

int	main(int argc, char **argv, char **envp)
{
	t_pip	pip;

	set_1(&pip, argc, argv, envp);
	if (argc != 5)
		return (1);
	set_2(&pip, argv[1], 1);
	pip.cmd_total = 2;
	if (pip.infd == -1)
		error(argv[1]);
	pip_it(&pip);
	close_final();
	while (wait(NULL) > 0)
		;
	return (WEXITSTATUS(pip.last_pid));
}
