/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:00:51 by jbelkerf          #+#    #+#             */
/*   Updated: 2024/11/04 16:38:01 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * the lstadd_front take a list and node the place this node in the front of 
 * this list
 */
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new != NULL || lst != NULL)
	{
		new->next = *lst;
		*lst = new;
	}
}
