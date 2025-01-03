/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:01:48 by jbelkerf          #+#    #+#             */
/*   Updated: 2024/10/28 11:45:59 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * this func check if the char is upercase then made it lowercase
 */
int	ft_tolower(int c)
{
	int	i;

	i = 'a' - 'A';
	if (c >= 'A' && c <= 'Z')
	{
		return (c + i);
	}
	return (c);
}
