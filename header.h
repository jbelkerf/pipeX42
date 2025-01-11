/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 18:24:53 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/01/11 13:08:39 by jbelkerf         ###   ########.fr       */
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

#endif
