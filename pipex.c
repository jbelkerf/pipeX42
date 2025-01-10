/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 18:23:37 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/01/10 10:56:47 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	exec_parent(char *argv[], char *envp[], int *pipefd, int cmd_numb)
{
	char	*cmd;
	int		fd;

	cmd = check_cmd(argv[cmd_numb + 1], envp);
	close(pipefd[1]);
	fd = open(argv[4], O_TRUNC | O_WRONLY | O_CREAT, 0777);
	if (fd == -1)
		error(argv[4]);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	dup2(pipefd[0], STDIN_FILENO);
	execve(cmd, ft_split(argv[cmd_numb + 1], ' '), envp);
	error(cmd);
}

void	exec_child(char *argv[], char *envp[], int *pipefd, int cmd_numb)
{
	char	*cmd;
	int		fd;

	cmd = check_cmd(argv[cmd_numb + 1], envp);
	close(pipefd[0]);
	fd = open(argv[1], O_RDONLY, 0777);
	if (fd == -1)
		error(argv[1]);
	dup2(fd, STDIN_FILENO);
	close(fd);
	dup2(pipefd[1], STDOUT_FILENO);
	execve(cmd, ft_split(argv[cmd_numb + 1], ' '), envp);
	error(cmd);
}

void	pipe_this(t_pipe *pip)
{
	int	pid;
	int	pipefd[2];
	int	status;

	status = 1;
	if (pipe(pipefd) == -1)
		error("pipe");
	pid = fork();
	if (pid == 0)
		exec_child(pip->argv, pip->envp, pipefd, 1);
	else if (pid == -1)
		error("fork");
	pid = fork();
	if (pid == 0)
		exec_parent(pip->argv, pip->envp, pipefd, 2);
	else if (pid == -1)
		error("fork");
}

int	main(int argc, char *argv[], char *envp[])
{
	int		i;
	t_pipe	pip;

	if (argc != 5)
		exit(EXIT_FAILURE);
	pip.argc = argc;
	pip.argv = argv;
	pip.envp = envp;
	pipe_this(&pip);
	while (waitpid(-1, &i, 0) > 0);
	return (WEXITSTATUS(i));
}
