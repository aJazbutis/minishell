/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 23:33:26 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/05/29 23:38:29 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_hereadd_back(t_here **lst, t_here *new)
{
	t_here	*current;

	if (!(*lst))
		(*lst) = new;
	else
	{
		current = *lst;
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
}

void	ft_hereclear(t_here **lst)
{
	t_here	*current;
	t_here	*begin_lst;

	if (*lst && lst)
	{
		begin_lst = *lst;
		while (begin_lst)
		{
			current = begin_lst;
			begin_lst = begin_lst->next;
			free(current->limiter);
			free(current);
		}
		*lst = NULL;
	}
}

t_here	*ft_herenew(char *limiter)
{
	t_here	*head;

	head = NULL;
	head = (t_here *)malloc(sizeof(t_here));
	if (head)
	{
		(*head).limiter = limiter;
		(*head).next = NULL;
	}
	return (head);
}

int	ft_heresize(t_here *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
