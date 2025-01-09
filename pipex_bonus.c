/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:04:54 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/01/09 17:56:55 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "./get_the_next_line/get_next_line.h"
#include "header.h"

void	do_thing(t_pip *pip, int *pipfd, int option)
{
	char	**argv;
	char	*cmd;

	argv = ft_split(pip->argv[pip->cmd_start + pip->cmd_numb], ' ');
	cmd = check_cmd(pip->argv[pip->cmd_start + pip->cmd_numb], pip->envp);
	if (option == 1)
	{
		dup2(pipfd[1], STDOUT_FILENO);
		close(pipfd[0]);
		execve(cmd, argv, pip->envp);
	}
	else if (option == 2)
	{
		execve(cmd, argv, pip->envp);
	}
}

int	exec_mid(t_pip *pip)
{
	int	i;
	int	pid;
	int	pipfd[2];

	while (pip->cmd_numb < pip->cmd_total)
	{
		pipe(pipfd);
		pid = fork();
		if (pid == 0)
			do_thing(pip, pipfd, 1);
		else if (pid > 0)
		{
			dup2(pipfd[0], STDIN_FILENO);
			close(pipfd[1]);
			pip->cmd_numb++;
		}
	}
	dup2(pip->outfd, STDOUT_FILENO);
	pid = fork();
	if (pid == 0)
		do_thing(pip, pipfd, 2);
	else if (pid > 0)
		return (waitpid(pid, &i, 0), i);
	return (error(), 1);
}

int	pip_it(t_pip *pip)
{
	int		pipfd[2];
	int		pid;
	char	**argv;
	char	*cmd;

	dup2(pip->infd, STDIN_FILENO);
	pipe(pipfd);
	dup2(pipfd[1], STDOUT_FILENO);
	pid = fork();
	if (pid == 0)
	{
		close(pipfd[0]);
		cmd = check_cmd(pip->argv[pip->cmd_start + pip->cmd_numb], pip->envp);
		argv = ft_split(pip->argv[pip->cmd_start + pip->cmd_numb], ' ');
		execve(cmd, argv, pip->envp);
	}
	else if (pid > 0)
	{
		dup2(pipfd[0], STDIN_FILENO);
		close(pipfd[1]);
		pip->cmd_numb++;
		return (exec_mid(pip));
	}
	return (error(), 1);
}

int	main(int argc, char **argv, char **envp)
{
	t_pip	pip;
	int		i;

	pip.argc = argc;
	pip.argv = argv;
	pip.cmd_numb = 1;
	pip.envp = envp;
	if (argc < 5)
		return (1);
	pip.outfd = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (argc >= 6 && !ft_strcmp(argv[1], "here_doc"))
	{
		here_doc_it(&pip);
		pip.infd = open("read_in_line", O_RDONLY, 0777);
		pip.cmd_total = argc - 4;
		pip.cmd_start = 2;
	}
	else
	{
		pip.cmd_total = argc - 3;
		pip.infd = open(argv[1], O_RDONLY, 0777);
		pip.cmd_start = 1;
	}
	i = pip_it(&pip);
	return (unlink("read_in_line"), WEXITSTATUS(i));
}
