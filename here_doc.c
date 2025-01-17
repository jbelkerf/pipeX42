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

void	do_the_read(t_pip *pip, int fd1)
{
	char	*str;

	while (1)
	{
		str = get_next_line(0);
		if (str == NULL)
		{
			unlink("read_line");
			error("here_doc EOF - CTL + D");
		}
		str[ft_strlen(str) - 1] = 0;
		if (ft_strcmp(str, pip->argv[2]) == 0)
		{
			free(str);
			close(fd1);
			break ;
		}
		str[ft_strlen(str)] = '\n';
		write(fd1, str, ft_strlen(str));
		free(str);
		print_prompt();
	}
}

void	here_doc_it(t_pip *pip)
{
	int		fd1;

	fd1 = open("read_line", O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (fd1 == -1)
		error("read_line");
	print_prompt();
	do_the_read(pip, fd1);
}
