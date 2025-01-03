/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:58:43 by jbelkerf          #+#    #+#             */
/*   Updated: 2024/11/04 12:45:05 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * the ft_calloc take number of memberes and the size of each member then it 
 * allocate the total memory neeeded using malloc then it send the memory to
 * the bzero func to set it to 0
 */
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;
	size_t	t;

	t = nmemb * size;
	if (!t)
		return (malloc(0));
	if (size != (t / nmemb))
		return (NULL);
	p = (void *)malloc(nmemb * size);
	if (p == NULL)
		return (NULL);
	ft_bzero(p, nmemb * size);
	return (p);
}
