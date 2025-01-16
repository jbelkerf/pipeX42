/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:04:54 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/01/16 11:23:44 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	eterate_it(int *pipfd, t_pip *pip)
{
	dup_3(pipfd[0], STDIN_FILENO);
	close(pipfd[1]);
	pip->cmd_numb++;
	pip->i++;
}

void	do_thing(t_pip *pip, int *pipfd, int option)
{
	char	**argv;
	char	*cmd;

	cmd = check_cmd(pip->argv[pip->cmd_start + pip->cmd_numb - 1], pip->envp);
	argv = ft_split3(pip->argv[pip->cmd_start + pip->cmd_numb - 1], "\' \"");
	if (option == 1)
	{
		dup_3(pipfd[1], STDOUT_FILENO);
		close(pipfd[0]);
	}
	execve(cmd, argv, pip->envp);
	free_array(argv);
	error_cmd(cmd);
}

void	exec_mid(t_pip *pip)
{
	int	pid;
	int	pipfd[2];

	while (pip->cmd_numb <= pip->cmd_total)
	{
		pipe_2(pipfd);
		pid = fork();
		if (pid == 0)
			do_thing(pip, pipfd, 1);
		else if (pid > 0)
			eterate_it(pipfd, pip);
		else if (pid < 0)
			error("fork");
	}
	dup_3(pip->outfd, STDOUT_FILENO);
	pid = fork();
	if (pid == 0)
		do_thing(pip, pipfd, 2);
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
	dup2(pipfd[1], STDOUT_FILENO);
	pip->pid = fork();
	if (pip->pid == 0)
		execute_the_child(pipfd, pip);
	else if (pip->pid > 0)
	{
		dup_3(pipfd[0], STDIN_FILENO);
		close(pipfd[1]);
		pip->cmd_numb++;
		exec_mid(pip);
	}
	else if (pip->pid == -1)
		error("fork");
}

int	main(int argc, char **argv, char **envp)
{
	t_pip	pip;
	int		i;

	i = 0;
	set_1(&pip, argc, argv, envp);
	if (argc < 5)
		return (1);
	if (argc >= 6 && !ft_strcmp(argv[1], "here_doc"))
	{
		here_doc_it(&pip);
		set_2(&pip, "read_in_line", 2);
	}
	else
		set_2(&pip, argv[1], 1);
	pip.cmd_total = argc - 2 - pip.cmd_start;
	if (pip.infd == -1 || pip.outfd == -1)
		error(argv[1]);
	pip_it(&pip);
	close_final();
	while (wait(NULL) > 0)
		;
	unlink("read_in_line");
	return (WEXITSTATUS(pip.last_pid));
}
