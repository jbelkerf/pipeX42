/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 13:42:20 by jbelkerf          #+#    #+#             */
/*   Updated: 2024/11/19 12:28:59 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct a_list
{
	int				fd;
	char			*left;
	struct a_list	*next;
}	t_list;

char	*ft_strdup(const char *s);
void	*free_p(char **p);
char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(const char *str);
char	*ft_strdup(const char *s);
char	*ft_substr(char *s, unsigned int start, size_t len);

#endif
