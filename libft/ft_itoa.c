/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:00:27 by jbelkerf          #+#    #+#             */
/*   Updated: 2024/10/30 16:40:04 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * the count func counts the number of digit in n by dividing by 10 
 */
static int	count(int n)
{
	int	w;

	w = 0;
	while (n != 0)
	{
		n = n / 10;
		w++;
	}
	return (w);
}
/*
 * the full_it func check if the n is negative if yes it add 1 to total n 
 * lenght and fail the first index by '-' and then it handles the n like 
 * positive, it start by failing the last index of str by '\0' aka 0
 * then fail the others by n digits
 */

static char	*full_it(int n, int w, int sign)
{
	char	*re;

	if (sign == -1)
		w = w + 1;
	re = (char *)malloc((w + 1) * sizeof(char));
	if (re == NULL)
		return (NULL);
	re[w] = 0;
	while (n != 0)
	{
		w--;
		re[w] = n % 10 + '0';
		n = n / 10;
	}
	if (w == 1)
		re[0] = '-';
	return (re);
}

/*
 * 1-) the itoa func transform the given n to an string from and return it
 * if the n is 0 or the MAX negative it send to strup to make a duplicate 
 * and return 
 * the n is sent to count to count the number of digit in it when it done it 
 * sent again with its lenght to full_it that does the real work
 */
char	*ft_itoa(int n)
{
	int		sign;
	char	*cas;
	int		w;

	sign = 1;
	cas = "-2147483648";
	if (n == 0)
		cas = "0";
	if (n == -2147483648 || n == 0)
		return (ft_strdup(cas));
	if (n < 0)
	{
		n = n * (-1);
		sign = -1;
	}
	w = count(n);
	return (full_it(n, w, sign));
}
