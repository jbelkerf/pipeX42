/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 13:22:23 by jbelkerf          #+#    #+#             */
/*   Updated: 2024/11/15 16:13:11 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 2
#endif

int	check(char *buf)
{
	int	i;

	i = 0;
	if (buf == NULL)
		return (0);
	while (buf[i])
	{
		if (buf[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}

char	*do_the_job(char **left, char **line, int separator, int f)
{
	char	*tmp;

	if (f == 1)
	{
		tmp = *left;
		*line = ft_substr(*left, 0, separator);
		*left = ft_substr(*left, separator, BUFFER_SIZE);
	}
	else
	{
		tmp = *line;
		*line = ft_substr(tmp, 0, separator);
		*left = ft_substr(tmp, separator, BUFFER_SIZE);
		if (**left == 0)
			free_p(left);
	}
	return (free(tmp), tmp = NULL, *line);
}

int	check_left(char **left, char **line)
{
	int	i;

	i = -1;
	if (*left != NULL)
	{
		if (**left != 0)
		{
			i = check(*left);
		}
	}
	if (i > 0)
	{
		*line = do_the_job(left, line, i, 1);
		if (**left == 0)
			free_p(left);
		return (1);
	}
	else if (i == 0)
	{
		*line = ft_strjoin(*line, *left);
		free_p(left);
	}
	return (0);
}

void free_node(int fd, t_list **head)
{
    t_list *m_in;
    t_list *prev;

    m_in = *head;
    prev = m_in;
    while (m_in)
    {
        if (m_in->fd == fd)
        {
            if (prev == m_in)
                *head = m_in->next;
            else
            {
                prev->next = m_in->next;
            }
			free(m_in->left);
			free(m_in);
			return ;
        }
        prev = m_in;
        m_in = m_in->next;
    }
}
char	*read_line(int fd, char *buffer, char *line, char **left, t_list **head)
{
	int	read_bytes;

	while (1)
	{
		buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (buffer == NULL)
			return (NULL);
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1 || read_bytes == 0)
		{
			free_p(&buffer);
            free_node(fd, head);
			if (read_bytes == -1)
				return (free_p(&line));
			return (line);
		}
		buffer[read_bytes] = 0;
		line = ft_strjoin(line, buffer);
		free_p(&buffer);
		read_bytes = check(line);
		if (read_bytes)
			return (do_the_job(left, &line, read_bytes, 2));
	}
}
char *get_next_line(int fd)
{
    char *buffer;
    char **left;
    static t_list *head;
    char *line;

    buffer = NULL;
    if (fd < 0 || fd >= 1000)
    return (NULL);
    left = check_fd_node(fd, &head);
    line = NULL;
    if (check_left(left, &line))
		return (line);
	line = read_line(fd, buffer, line, left, &head);
	// if (*left != NULL)
	// {
	// 	if (**left == 0)
	// 		free_p(left);
	// }
	return (line);
}