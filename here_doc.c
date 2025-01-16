/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:45:57 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/01/16 16:50:21 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	print_prompt(void)
{
	write(1, "> ", 2);
}

void	clear_delemeter(t_pip *pip)
{
	int		fd1;
	int		fd2;
	char	*str;

	fd1 = open("read_line", O_RDONLY, 0777);
	fd2 = open ("read_in_line", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd1 == -1 || fd2 == -1)
		error("open here_doc");
	while (1)
	{
		str = get_next_line(fd1);
		if (str)
		{
			str[ft_strlen(str) - 1] = 0;
			if (!ft_strcmp(str, pip->argv[2]) && free_and_true(str))
				break ;
			str[ft_strlen(str)] = '\n';
			write(fd2, str, ft_strlen(str));
			free(str);
		}
		else
			break ;
	}
	close_2(fd1, fd2);
	unlink("read_line");
}

void	do_the_read(t_pip *pip, int fd1, int fd2)
{
	char	c;
	char	*str;

	while (1)
	{
		read(0, &c, 1);
		write(fd1, &c, 1);
		if (c == '\n')
		{
			c = 0;
			str = get_next_line(fd2);
			if (str == NULL)
				break ;
			str[ft_strlen(str) - 1] = 0;
			if (!ft_strcmp(str, pip->argv[2]))
			{
				free(str);
				close_2(fd1, fd2);
				break ;
			}
			free(str);
			print_prompt();
		}
	}
}

void	here_doc_it(t_pip *pip)
{
	int		fd1;
	int		fd2;

	fd1 = open("read_line", O_WRONLY | O_TRUNC | O_CREAT, 0777);
	fd2 = open("read_line", O_RDONLY, 0777);
	if (fd1 == -1 || fd2 == -1)
		error("read_line");
	print_prompt();
	do_the_read(pip, fd1, fd2);
	clear_delemeter(pip);
}
