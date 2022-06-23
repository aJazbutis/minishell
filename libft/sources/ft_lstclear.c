/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 00:56:54 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/01/21 20:32:18 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*begin_lst;

	if (*lst && lst)
	{
		begin_lst = *lst;
		while (begin_lst)
		{
			current = begin_lst;
			begin_lst = begin_lst->next;
			del(current->content);
			free(current);
		}
		*lst = NULL;
	}
}

void	ft_llstclear(t_llst **lst, void (*del)(void *))
{
	t_llst	*current;
	t_llst	*begin_lst;

	if (*lst && lst)
	{
		begin_lst = *lst;
		while (begin_lst)
		{
			current = begin_lst;
			begin_lst = begin_lst->next;
			del(current->content);
			free(current);
		}
		*lst = NULL;
	}
}
