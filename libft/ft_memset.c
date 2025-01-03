/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:09:31 by jbelkerf          #+#    #+#             */
/*   Updated: 2024/11/04 13:21:54 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * this func take a pointer to an memory and set every byte of it to the 
 * unsigned c 
 */
void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	char			*p;
	unsigned char	x;

	x = (unsigned char)c;
	p = (char *)s;
	i = 0;
	while (i < n)
	{
		p[i] = x;
		i++;
	}
	return (s);
}
