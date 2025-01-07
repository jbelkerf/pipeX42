/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:40:04 by jbelkerf          #+#    #+#             */
/*   Updated: 2024/11/19 12:39:01 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

char	*do_the_job(char **left, char **line, int separator)
{
	char	*tmp;

	tmp = *line;
	*line = ft_substr(tmp, 0, separator);
	*left = ft_substr(tmp, separator, BUFFER_SIZE);
	if (*line == NULL || *left == NULL)
		return (free_p(&tmp), free_p(left), free_p(line), NULL);
	return (free_p(&tmp), tmp = NULL, *line);
}

int	check_left(char **left, char **line)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = *left;
	if (*left != NULL)
		i = check(*left);
	if (i > 0)
	{
		*line = ft_substr(*left, 0, i);
		*left = ft_substr(*left, i, BUFFER_SIZE);
		if (*line == NULL || *left == NULL)
			return (free_p(&tmp), free_p(line), free_p(left), 1);
		free_p(&tmp);
		tmp = NULL;
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

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
		return (free_p(left), free_p(&line), NULL);
	while (1)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1 || read_bytes == 0)
		{
			free_p(&buffer);
			if (read_bytes == -1)
				return (free_p(left), free_p(&line));
			return (line);
		}
		buffer[read_bytes] = 0;
		line = ft_strjoin(line, buffer);
		if (line == NULL)
			return (free_p(&buffer), free_p(left), NULL);
		read_bytes = check(line);
		if (read_bytes)
			return (free_p(&buffer), do_the_job(left, &line, read_bytes));
	}
}

char	*get_next_line(int fd)
{
	static char	*left[1024];
	char		*buffer;
	char		*line;

	line = NULL;
	buffer = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (check_left(&left[fd], &line))
		return (line);
	line = read_line(fd, buffer, line, &left[fd]);
	if (left[fd] != NULL && *left[fd] == 0)
		free_p(&left[fd]);
	return (line);
}
