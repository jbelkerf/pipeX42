/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:07:42 by jbelkerf          #+#    #+#             */
/*   Updated: 2024/10/28 14:47:25 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * the strdup func take a string and ceate a duplicate to this func
 */
char	*ft_strdup(const char *s)
{
	char	*re;

	re = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (re == NULL)
		return (NULL);
	ft_strlcpy(re, s, ft_strlen(s) + 1);
	return (re);
}
