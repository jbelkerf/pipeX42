/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:07:26 by jbelkerf          #+#    #+#             */
/*   Updated: 2024/11/01 13:20:14 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * the strjoin take two strings and make them in one string using ft_strlcpy
 * and ft_strcat
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*re;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	re = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (re == NULL)
		return (NULL);
	ft_strlcpy(re, s1, ft_strlen(s1) + 1);
	ft_strlcat(re, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	return (re);
}
