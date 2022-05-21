/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 14:47:43 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/05/21 21:58:12 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cmdadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*current;

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

void	ft_cmdclear(t_cmd **lst)
{
	t_cmd	*current;
	t_cmd	*begin_lst;

	if (*lst && lst)
	{
		begin_lst = *lst;
		while (begin_lst)
		{
			current = begin_lst;
			begin_lst = begin_lst->next;
			ft_free_tab(current->cmd);
			free(current);
		}
		*lst = NULL;
	}
}

t_cmd	*ft_cmdnew(char **cmd)
{
	t_cmd	*head;

	head = NULL;
	head = (t_cmd *)malloc(sizeof(t_cmd));
	if (head)
	{
		(*head).cmd = cmd;
		(*head).next = NULL;
	}
	return (head);
}

int	ft_cmdsize(t_cmd *lst)
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
