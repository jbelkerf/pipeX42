/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:58:23 by jbelkerf          #+#    #+#             */
/*   Updated: 2024/11/04 12:36:04 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*the first while is for skip the isspace
 *the first if condition is for handling the sign, - or + but just for once
 *the last while is for handling the actual number by mining the string
 *			 str checkin each char for number than add it in mathimatical way to n
 *finally we return the minned number n multipled by the sign factor
*/
int	ft_atoi(const char *str)
{
	long int	n;
	int			sign;

	n = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		n = n * 10 + (*str - '0');
		str++;
		if (n < 0 && sign == -1)
			return (0);
		else if (n < 0 && sign == 1)
			return (-1);
	}
	return ((int)(sign * n));
}
