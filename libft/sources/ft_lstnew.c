/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 12:19:37 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/01/21 19:00:31 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*head;

	head = NULL;
	head = (t_list *)malloc(sizeof(t_list));
	if (head)
	{
		(*head).content = content;
		(*head).next = NULL;
	}
	return (head);
}

t_llst	*ft_llstnew(void *content)
{
	t_llst	*head;

	head = NULL;
	head = (t_llst *)malloc(sizeof(t_llst));
	if (head)
	{
		(*head).content = content;
		(*head).next = NULL;
		head->prev = NULL;
	}
	return (head);
}
