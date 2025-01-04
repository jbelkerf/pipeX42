/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 18:23:37 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/01/03 23:29:31 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "./libft/libft.h"

void error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}
void exec_parent(char *argv[], char *envp[], int *pipefd, int cmd_numb)
{
	char	*cmd;
	int		fd;

	cmd = check_cmd(argv[cmd_numb + 1], envp);
	
	close(pipefd[1]);
	fd = open(argv[4], O_TRUNC | O_WRONLY | O_CREAT, 0777);
	if (fd == -1)
		error();
	dup2(fd, STDOUT_FILENO);
	//close(fd);
	dup2(pipefd[0], STDIN_FILENO);
	execve(cmd, ft_split(argv[cmd_numb + 1], ' '), envp);
	error();
}
	
void exec_child(char *argv[], char *envp[], int *pipefd, int cmd_numb)
{
	char	*cmd;
	int		fd;

	cmd = check_cmd(argv[cmd_numb + 1], envp);
	
		close(pipefd[0]);
		fd = open(argv[1], O_RDONLY, 0777);
		if (fd == -1)
			error();
		dup2(fd, STDIN_FILENO);
		//close(fd);
		dup2(pipefd[1], STDOUT_FILENO);
	execve(cmd, ft_split(argv[cmd_numb + 1], ' '), envp);
	error();
}
int	main(int argc, char *argv[], char *envp[])
{
	int	pid;
	int	pipefd[2];

	if (argc != 5)
	{
		exit(1);
	}
	if (pipe(pipefd) == -1)
	{
		error();
	}
	pid = fork();
	if (pid == 0)
		exec_child(argv, envp, pipefd, 1);
	else if (pid > 0)
	{
		waitpid(pid, NULL, 0);
		exec_parent(argv, envp, pipefd, 2);
	}
	else
	{
		error();
	}
}
