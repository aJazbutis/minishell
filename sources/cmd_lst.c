/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorunov <kmorunov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 14:47:43 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/06/19 23:33:44 by ajazbuti         ###   ########.fr       */
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
			if (current->cmd)
				ft_free_tab(current->cmd);
			ft_flstclear(&current->in);
			ft_flstclear(&current->out);
			ft_flstclear(&current->heredoc);
			free(current);
		}
		*lst = NULL;
	}
}

t_cmd	*ft_cmdnew(char **cmd, t_flst *in, t_flst *out, t_flst *here)
{
	t_cmd	*head;

	head = NULL;
	head = (t_cmd *)malloc(sizeof(t_cmd));
	if (head)
	{
		(*head).cmd = cmd;
		(*head).in = in;
		(*head).out = out;
		(*head).heredoc = here;
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

void	ft_tokclear(t_token **token)
{
	t_token	*current;
	t_token	*begin_lst;

	if (*token)
	{
		begin_lst = *token;
		while (begin_lst)
		{
			current = begin_lst;
			begin_lst = begin_lst->next;
			free(current->value);
			free(current);
		}
		*token = NULL;
	}
}
