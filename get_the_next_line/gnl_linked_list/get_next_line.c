/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:40:04 by jbelkerf          #+#    #+#             */
/*   Updated: 2024/11/14 14:55:30 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
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

char	*read_line(int fd, char *buffer, char *line, char **left)
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

char	*get_next_line(int fd)
{
	static char	*left;
	char		*buffer;
	char		*line;

	line = NULL;
	buffer = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (check_left(&left, &line))
		return (line);
	line = read_line(fd, buffer, line, &left);
	if (left != NULL)
	{
		if (*left == 0)
			free_p(&left);
	}
	return (line);
}
