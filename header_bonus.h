/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 12:49:56 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/01/05 14:54:43 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_BONUS_H
# define HEADER_BONUS_H

typedef struct a_pipe{
    char **argv;
    int argc;
    char **envp;
    int cmd_number;
    int **pipfd;
    int pip_read;
    int pip_write;
}   t_pipe;

# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>

char	**ft_split2(char const *s, char c);
char	*check_cmd(char *cmd, char **envp);
#endif