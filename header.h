/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 18:24:53 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/01/09 18:18:16 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <unistd.h>
# include <errno.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include "./libft/libft.h"
# include "./get_the_next_line/get_next_line.h"

typedef struct a_pipe{
	char	**argv;
	int		argc;
	char	**envp;
	int		cmd_number;
	int		**pipfd;
	int		pip_read;
	int		pip_write;
}	t_pipe;

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
void	error(void);

#endif
