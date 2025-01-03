/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:07:18 by jbelkerf          #+#    #+#             */
/*   Updated: 2024/11/04 16:40:57 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * the strlcat concatanat two strings in a giving size and ensure there's
 * ### return always len_s + len_d
 * 1- if size less then len_d  ten the len_d == size return is len_s + size
 * 2- if in size there's a room for src or a part of it then we return default
 */
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	if (size == 0)
		return (ft_strlen(src));
	i = ft_strlen(dst);
	j = 0;
	if (ft_strlen(dst) >= size)
		return (size + ft_strlen(src));
	if (size != 0)
	{
		while (i < size - 1 && src[j])
		{
			dst[i] = src[j];
			i++;
			j++;
		}
		dst[i] = 0;
	}
	return (i - j + ft_strlen(src));
}
