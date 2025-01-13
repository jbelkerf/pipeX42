/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:07:57 by jbelkerf          #+#    #+#             */
/*   Updated: 2024/11/04 13:23:30 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static char	**h_fail(char **re, int elm)
{
	int	i;

	i = 0;
	while (i < elm)
	{
		free(re[i]);
		i++;
	}
	free(re);
	return (NULL);
}

static int	c_c(char *ss, char *set)
{
	int	i;

	i = 0;
	while (is_set(*ss, set))
		ss++;
	while (!is_set(*ss, set) && *ss)
	{
		ss++;
		i++;
	}
	return (i + 1);
}

static char	**fill_tab(char **re, char *ss, char *set, int w_c)
{
	int	i;
	int	j;

	i = 0;
	while (i < w_c)
	{
		re[i] = (char *)malloc(c_c(ss, set) * sizeof(char));
		if (re[i] == 0)
			return (h_fail(re, i));
		j = 0;
		while (is_set(*ss, set))
			ss++;
		while (*ss && !is_set(*ss, set))
		{
			re[i][j] = *ss;
			ss++;
			j++;
		}
		re[i][j] = 0;
		if (*ss)
			ss++;
		i++;
	}
	re[i] = 0;
	return (re);
}

static int	c_w(char *ss, char *set)
{
	int	i;

	i = 0;
	while (*ss)
	{
		if (!is_set(*ss, set))
		{
			i++;
			while (!is_set(*ss, set) && *ss)
				ss++;
		}
		if (*ss)
			ss++;
	}
	return (i);
}

char	**ft_split3(char const *s, char *set)
{
	char	**re;
	char	*ss;
	int		w_c;

	if (s == NULL)
		return (NULL);
	ss = (char *)s;
	w_c = c_w(ss, set);
	if (w_c == 0)
	{
		re = malloc(sizeof(char *));
		if (re == 0)
			return (0);
		re[0] = 0;
		return (re);
	}
	re = (char **)malloc((w_c + 1) * sizeof(char *));
	if (re == 0)
		return (0);
	return (fill_tab(re, ss, set, w_c));
}
