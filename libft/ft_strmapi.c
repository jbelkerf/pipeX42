/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:06:49 by jbelkerf          #+#    #+#             */
/*   Updated: 2024/11/04 16:42:02 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t		i;
	size_t		l;
	char		*re;

	if (s == NULL || f == NULL)
		return (NULL);
	i = 0;
	l = ft_strlen(s);
	re = (char *)malloc((l + 1) * sizeof(char));
	if (re == NULL)
		return (NULL);
	while (i < l)
	{
		re[i] = f(i, s[i]);
		i++;
	}
	re[i] = 0;
	return (re);
}
