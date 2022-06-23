/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flst.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 19:03:10 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/06/19 23:34:36 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_flstadd_back(t_flst **lst, t_flst *new)
{
	t_flst	*current;

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

void	ft_flstclear(t_flst **lst)
{
	t_flst	*current;
	t_flst	*begin_lst;

	if (*lst && lst)
	{
		begin_lst = *lst;
		while (begin_lst)
		{
			current = begin_lst;
			begin_lst = begin_lst->next;
			if (current->str)
				free(current->str);
			free(current);
		}
		*lst = NULL;
	}
}

t_flst	*ft_flstnew(char *file, int append)
{
	t_flst	*head;

	head = NULL;
	head = (t_flst *)malloc(sizeof(t_flst));
	if (head)
	{
		(*head).str = file;
		(*head).nbr[0] = append;
		(*head).next = NULL;
	}
	return (head);
}

int	ft_flstsize(t_flst *lst)
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
