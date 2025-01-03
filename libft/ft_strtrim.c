/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:05:15 by jbelkerf          #+#    #+#             */
/*   Updated: 2024/11/01 13:20:38 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * the strim take a string and a set and remove the set from the begging and
 * theend of that string
 * it count the number of set in both beging and the end and subtract it from
 * the total len then give the string and the new len and the set to strlcpy
 * to create the new one then return it
 *
 * ### hard cases
 * 1- if the string is empty or full of sets we return a freable null
 * 2- if set is null we return the total s
 */
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	char	*re;

	if (s1 == NULL || set == NULL)
		return (NULL);
	j = 0;
	i = 0;
	if (*s1 == '\0')
		return (ft_strdup(""));
	if (*set == '\0')
		return (ft_strdup(s1));
	while (ft_strchr(set, s1[i]) && s1[i])
		i++;
	if (s1[i] == '\0')
		return (ft_strdup(""));
	j = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[j]))
		j--;
	re = malloc((j - i + 2) * sizeof(char));
	if (re == 0)
		return (0);
	ft_strlcpy(re, (s1 + i), (j - i + 2));
	return (re);
}
