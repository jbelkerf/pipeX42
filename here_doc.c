/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:45:57 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/01/09 14:49:50 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "./get_the_next_line/get_next_line.h"
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
	while (1)
	{
		str = get_next_line(fd1);
		if (str)
		{
			str[ft_strlen(str) - 1] = 0;
			if (!ft_strcmp(str, pip->argv[2]))
				break ;
			else
			{
				str[ft_strlen(str)] = '\n';
				write(fd2, str, ft_strlen(str));
			}
		}
		else
			break ;
	}
	unlink("read_line");
}

void	here_doc_it(t_pip *pip)
{
	int		fd1;
	int		fd2;
	char	*str;
	char	c;

	fd1 = open("read_line", O_WRONLY | O_TRUNC | O_CREAT, 0777);
	fd2 = open("read_line", O_RDONLY, 0777);
	print_prompt();
	while (1)
	{
		read(0, &c, 1);
		write(fd1, &c, 1);
		if (c == '\n')
		{
			c = 0;
			str = get_next_line(fd2);
			str[ft_strlen(str) - 1] = 0;
			if (!ft_strcmp(str, pip->argv[2]))
			{
				close(fd1);
				break ;
			}
			print_prompt();
		}
	}
	clear_delemeter(pip);
}
