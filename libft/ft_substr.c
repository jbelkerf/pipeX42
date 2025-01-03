/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:02:00 by jbelkerf          #+#    #+#             */
/*   Updated: 2024/11/01 13:19:23 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * the substr func tries to ceate a string starting from an existing one by 
 * knwing its start and its lenght.
 * 1- first alocate enough space for the sub
 * 2- copy the sub from the existing then null terminat it then returned it
 *
 * ### hard cases 
 * 1- if the start is greater than the len of the existing then we return null
 * byte
 * 2- if the len + start is more than the len_s then we should modify the len to
 * ensure that the sub does not cos segv
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	len_s;
	char			*sub;

	if (s == NULL)
		return (NULL);
	len_s = ft_strlen(s);
	if (len_s < start)
		return (ft_strdup(""));
	if (len_s - start < len)
		len = len_s - start;
	sub = (char *)malloc((len + 1) * sizeof(char));
	if (sub == NULL)
		return (NULL);
	ft_strlcpy(sub, s + start, len + 1);
	return (sub);
}
