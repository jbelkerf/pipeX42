/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 18:24:53 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/01/11 16:52:35 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <sys/wait.h>
# include <unistd.h>
# include <errno.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include "./libft/libft.h"
# include "./get_the_next_line/get_next_line.h"

typedef struct ap{
	int		infd;
	int		outfd;
	int		argc;
	char	**argv;
	char	**envp;
	int		cmd_numb;
	int		cmd_total;
	int		cmd_start;
}	t_pip;

char	**ft_split2(char const *s, char c);
char	*check_cmd(char *cmd, char **envp);
void	here_doc_it(t_pip *pip);
void	clear_delemeter(t_pip *pip);
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
void	close_final(void);
void	close_2(int fd1, int fd2);

#endif
