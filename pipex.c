/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:04:54 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/01/11 14:11:24 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	do_thing(t_pip *pip)
{
	char	**argv;
	char	*cmd;

	argv = ft_split(pip->argv[pip->cmd_start + pip->cmd_numb], ' ');
	cmd = check_cmd(pip->argv[pip->cmd_start + pip->cmd_numb], pip->envp);
	execve(cmd, argv, pip->envp);
	free_array(argv);
	error(cmd);
}

int	exec_mid(t_pip *pip)
{
	int		pid;
	char	*path;

	path = pip->argv[pip->argc - 1];
	pip->outfd = open(path, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (pip->outfd == -1)
		error(pip->argv[pip->argc - 1]);
	dup2(pip->outfd, STDOUT_FILENO);
	close(pip->outfd);
	pid = fork();
	if (pid == 0)
		do_thing(pip);
	else if (pid == -1)
		error("fork");
	return (pid);
}

int	pip_it(t_pip *pip)
{
	int		pipfd[2];
	int		pid;
	int		i;

	i = 0;
	dup2(pip->infd, STDIN_FILENO);
	pipe(pipfd);
	dup2(pipfd[1], STDOUT_FILENO);
	close(pipfd[1]);
	pid = fork();
	if (pid == 0)
	{
		close(pipfd[0]);
		do_thing(pip);
	}
	else if (pid > 0)
	{
		dup2(pipfd[0], STDIN_FILENO);
		close(pipfd[0]);
		pip->cmd_numb++;
		i = exec_mid(pip);
	}
	else if (pid == -1)
		error("fork");
	return (i);
}

int	main(int argc, char **argv, char **envp)
{
	t_pip	pip;
	int		i;
	int		j;

	pip.argc = argc;
	pip.argv = argv;
	pip.cmd_numb = 1;
	pip.envp = envp;
	if (argc != 5)
		return (1);
	pip.infd = open(argv[1], O_RDONLY, 0777);
	pip.cmd_start = 1;
	pip.cmd_total = 2;
	if (pip.infd == -1)
		error(argv[1]);
	i = pip_it(&pip);
	while (waitpid(i, &i, 0) > 0)
		;
	while (wait(&j) > 0)
		;
	close(pip.infd);
	return (WEXITSTATUS(i));
}
