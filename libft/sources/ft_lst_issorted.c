/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_issorted.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 21:36:58 by ajazbuti          #+#    #+#             */
/*   Updated: 2021/12/20 22:13:46 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_lst_isasc(t_list *lst)
{
	if (lst)
	{
		while (lst->next)
		{
			if (*((int *)lst->content) > *((int *)lst->next->content))
				return (0);
			lst = lst->next;
		}
	}
	return (1);
}

int	ft_lst_isdsc(t_list *lst)
{
	if (lst)
	{
		while (lst->next)
		{
			if (*((int *)lst->content) < *((int *)lst->next->content))
				return (0);
			lst = lst->next;
		}
	}
	return (1);
}
