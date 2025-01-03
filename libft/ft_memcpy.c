/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:09:13 by jbelkerf          #+#    #+#             */
/*   Updated: 2024/11/03 17:08:16 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * the memcpy func copy the n byte from the memory src to the memory dest 
 * if the n is 0 then the memcpy return the dst if the both memory is NULL
 * then it returns null if everything is perfect then dest is being returned
 */
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*b;
	char	*s;
	size_t	i;

	b = (char *)dest;
	s = (char *)src;
	if (n == 0)
		return (dest);
	if (b == NULL && s == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		b[i] = s[i];
		i++;
	}
	return (dest);
}
