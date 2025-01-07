/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:41:44 by jbelkerf          #+#    #+#             */
/*   Updated: 2024/11/14 12:19:22 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2
# endif

char	*ft_strdup(const char *s);
void	*free_p(char **p);
char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2);
int		check_nwln(char *str);
int		ft_strlen(const char *str);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
#endif
