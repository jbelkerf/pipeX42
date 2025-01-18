/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 18:24:53 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/01/16 16:49:49 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include "./libft/libft.h"
# include "./get_the_next_line/get_next_line.h"

typedef struct ap
{
	int		infd;
	int		outfd;
	int		argc;
	char	**argv;
	char	**envp;
	int		cmd_numb;
	int		cmd_total;
	int		cmd_start;
	int		i;
	int		pid;
	char	*str;
	int		last_pid;
}	t_pip;

void	error_cmd(char *str);
char	**ft_split2(char const *s, char c);
char	*check_cmd(char *cmd, char **envp, int i);
void	here_doc_it(t_pip *pip);
void	print_prompt(void);
void	error(char *str);
void	free_array(char **str);
void	command_not_found(char *cmd);
void	set_1(t_pip *pip, int argc, char **argv, char **envp);
void	set_2(t_pip *pip, char *file_path, int option);
void	dup_3(int a, int b);
void	pipe_2(int *pipefd);
void	execve_2(char *cmd, char **argm, char **envp);
void	execute_the_child(int *pipfd, t_pip *pip);
int		free_and_true(char *str);
void	close_2(int fd1, int fd2);
char	**ft_split3(char const *s, char *set);
int		is_set(char c, char *set);

#endif
