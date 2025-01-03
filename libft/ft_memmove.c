/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:09:20 by jbelkerf          #+#    #+#             */
/*   Updated: 2024/11/04 13:15:24 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * check overlap handle 3 cases
 * 1- s ----------      
 *                            return 1
 *         d----------
 *         ####
 * 2-      s----------
 *                            return 2
 *     d---------
 *     	   ####
 * 3- there is no overlap     return 0
 */
static int	check_overl(char *d, char *s, size_t n)
{
	if (s < d && s + n > d)
		return (1);
	if (d < s && d + n > s)
		return (2);
	return (0);
}

/*
 * the r_cpy reverse copy start the copy from the end
 */
static void	*r_cpy(void *dest, const void *src, size_t n)
{
	unsigned char	*b;
	unsigned char	*s;
	size_t			i;

	b = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (n == 0)
		return (dest);
	i = 0;
	while (n)
	{
		n--;
		b[n] = s[n];
	}
	return (dest);
}

/*
 * the memmove func check if the src and the dest is null then it returns null
 */
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*s;
	char	*d;
	int		i;

	if (dest == src)
		return (dest);
	s = (char *)src;
	d = (char *)dest;
	if (d == 0 && s == 0)
		return (0);
	i = check_overl(d, s, n);
	if (i == 0 || i == 2)
		return (ft_memcpy(dest, src, n));
	return (r_cpy(dest, src, n));
}
