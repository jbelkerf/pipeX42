/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 18:23:37 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/01/08 12:29:33 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "./libft/libft.h"

void	error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

void	exec_parent(char *argv[], char *envp[], int *pipefd, int cmd_numb)
{
	char	*cmd;
	int		fd;

	cmd = check_cmd(argv[cmd_numb + 1], envp);
	close(pipefd[1]);
	fd = open(argv[4], O_TRUNC | O_WRONLY | O_CREAT, 0777);
	if (fd == -1)
		error();
	dup2(fd, STDOUT_FILENO);
	close(fd);
	dup2(pipefd[0], STDIN_FILENO);
	execve(cmd, ft_split(argv[cmd_numb + 1], ' '), envp);
	error();
}

void	exec_child(char *argv[], char *envp[], int *pipefd, int cmd_numb)
{
	char	*cmd;
	int		fd;

	cmd = check_cmd(argv[cmd_numb + 1], envp);
	close(pipefd[0]);
	fd = open(argv[1], O_RDONLY, 0777);
	if (fd == -1)
		error();
	dup2(fd, STDIN_FILENO);
	close(fd);
	dup2(pipefd[1], STDOUT_FILENO);
	execve(cmd, ft_split(argv[cmd_numb + 1], ' '), envp);
	error();
}

int	pipe_this(t_pipe *pip)
{
	int	pid;
	int	pipefd[2];
	int	status;

	status = 1;
	if (pipe(pipefd) == -1)
		error();
	pid = fork();
	if (pid == 0)
		exec_child(pip->argv, pip->envp, pipefd, 1);
	else if (pid == -1)
		error();
	pid = fork();
	if (pid == 0)
		exec_parent(pip->argv, pip->envp, pipefd, 2);
	else if (pid == -1)
		waitpid(pid, &status, 0);
	return (status);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		pid;
	int		i;
	t_pipe	pip;

	if (argc != 5)
	{
		exit(1);
	}
	pip.argc = argc;
	pip.argv = argv;
	pip.envp = envp;
	i = pipe_this(&pip);
	return (WEXITSTATUS(i));
}
