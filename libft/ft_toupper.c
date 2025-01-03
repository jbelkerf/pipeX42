/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:01:35 by jbelkerf          #+#    #+#             */
/*   Updated: 2024/10/28 11:46:58 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * this func check if the char is lower then make it uper
 */
int	ft_toupper(int c)
{
	int	i;

	i = 'a' - 'A';
	if (c >= 'a' && c <= 'z')
	{
		return (c - i);
	}
	return (c);
}
