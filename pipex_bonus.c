/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ner-roui <ner-roui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:04:54 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/01/11 22:12:14 by ner-roui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	eterate_it(int *pipfd, t_pip *pip)
{
	dup_3(pipfd[0], STDIN_FILENO);
	close(pipfd[1]);
	pip->cmd_numb++;
}

void	do_thing(t_pip *pip, int *pipfd, int option)
{
	char	**argv;
	char	*cmd;

	argv = ft_split(pip->argv[pip->cmd_start + pip->cmd_numb], ' ');
	cmd = check_cmd(pip->argv[pip->cmd_start + pip->cmd_numb], pip->envp);
	if (option == 1)
	{
		dup_3(pipfd[1], STDOUT_FILENO);
		close(pipfd[0]);
	}
	execve(cmd, argv, pip->envp);
	free_array(argv);
	error(cmd);
}

int	exec_mid(t_pip *pip)
{
	int	pid;
	int	pipfd[2];

	while (pip->cmd_numb < pip->cmd_total)
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
		return (pid);
	return (0);
}

int	pip_it(t_pip *pip)
{
	int		pipfd[2];
	int		pid;
	int		i;

	i = 0;
	dup_3(pip->infd, STDIN_FILENO);
	pipe_2(pipfd);
	dup2(pipfd[1], STDOUT_FILENO);
	pid = fork();
	if (pid == 0)
		execute_the_child(pipfd, pip);
	else if (pid > 0)
	{
		dup_3(pipfd[0], STDIN_FILENO);
		close(pipfd[1]);
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

	set_1(&pip, argc, argv, envp);
	if (argc < 5)
		return (1);
	pip.outfd = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0777);
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
	i = pip_it(&pip);
	while (i != 0 && waitpid(i, &i, 0) > 0)
		;
	// while (wait(NULL) > 0)
	// 	;
	close_final();
	unlink("read_in_line");
	return (WEXITSTATUS(i));
}
