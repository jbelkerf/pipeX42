/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 18:23:37 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/01/03 22:03:27 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "./libft/libft.h"


void exec_parent(char *argv[], char *envp[], int *pipefd, int cmd_numb)
{
	char	*cmd;
	int		fd;

	cmd = check_cmd(argv[cmd_numb + 1], envp);
	
	close(pipefd[1]);
	fd = open(argv[4], O_TRUNC | O_WRONLY);
	dup2(fd, 1);
	//close(fd);
	dup2(pipefd[0], 0);
	execve(cmd, ft_split(argv[cmd_numb + 1], ' '), NULL);
	ft_putstr_fd("pipex: command not found", 2);
	exit(1);
}
void exec_child(char *argv[], char *envp[], int *pipefd, int cmd_numb)
{
	char	*cmd;
	int		fd;

	cmd = check_cmd(argv[cmd_numb + 1], envp);
	
		close(pipefd[0]);
		fd = open(argv[1], O_RDONLY);
		dup2(fd, 0);
		//close(fd);
		dup2(pipefd[1], 1);
	execve(cmd, ft_split(argv[cmd_numb + 1], ' '), NULL);
	ft_putstr_fd("pipex: command not found", 2);
	exit(1);
}
int	main(int argc, char *argv[], char *envp[])
{
	int	pid;
	int	pipefd[2];

	if (argc != 5)
		exit(1);
	if (pipe(pipefd) == -1)
	{
		ft_putstr_fd("pipex: command not found", 2);
		exit(128);
	}
	pid = fork();
	if (pid == 0)
		exec_child(argv, envp, pipefd, 1);
	else if (pid > 0)
		exec_parent(argv, envp, pipefd, 2);
	else
	{
		ft_putstr_fd("cant fork", 2);
		exit(1);
	}
}