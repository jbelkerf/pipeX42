/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 18:24:53 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/01/03 21:20:39 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>

char	**ft_split2(char const *s, char c);
char	*check_cmd(char *cmd, char **envp);
#endif
