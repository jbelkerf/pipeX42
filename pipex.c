/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 18:23:37 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/01/03 18:29:22 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	exec_cmd(char *argv[], char *envp[], int *pipefd, int cmd_numb)
{
	char	*cmd;
	int		fd;

	cmd = check_cmd(argv[cmd_numb + 1], envp);
	if (cmd_numb == 1)
	{
		close(pipefd[0]);
		fd = open(argv[1], O_RDONLY);
		dup2(fd, 0);
		close(fd);
		dup2(pipefd[1], 1);
		execve(cmd, ft_split(argv[cmd_numb + 1], ' '), NULL);
	}
	else
	{
		close(pipefd[1]);
		fd = open(argv[4], O_TRUNC | O_WRONLY);
		dup2(fd, 1);
		close(fd);
		dup2(pipefd[0], 0);
		execve(cmd, ft_split(argv[cmd_numb + 1], ' '), NULL);
	}
}

void	execute_prog(char *argv[], char *envp[])
{
	int	pid;
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		exit(1);
	pid = fork();
	if (pid == 0)
	{
		exec_cmd(argv, envp, pipefd, 1);
	}
	else if (pid > 0)
	{
		exec_cmd(argv, envp, pipefd, 2);
	}
	else
		exit(1);
}

int	main(int argc, char *argv[], char *envp[])
{
	int	pid;

	if (argc != 5)
		exit(1);
	pid = fork();
	if (pid < 0)
		exit (1);
	else if (pid == 0)
	{
		execute_prog(argv, envp);
	}
	else
	{
		exit(0);
	}
	return (0);
}
