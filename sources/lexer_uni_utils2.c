/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_uni_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorunov <kmorunov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 21:15:09 by kmorunov          #+#    #+#             */
/*   Updated: 2022/06/20 18:46:57 by kmorunov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_flag(int c, t_data **data)
{
	if (c == '\'' && (*data)->flag == '\'')
		(*data)->flag = 0;
	else if (c == '\'' && (*data)->flag == 0)
		(*data)->flag = '\'';
	else if (c == '\"' && (*data)->flag == '\"')
		(*data)->flag = 0;
	else if (c == '\"' && (*data)->flag == 0)
		(*data)->flag = '\"';
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (-1);
	while (s1[i] == s2[i] && (s1[i] != '\0' && s2[i] != '\0'))
		i++;
	return ((unsigned char) s1[i] - s2[i]);
}

void	put_dollar_back(t_data **data)
{
	t_token	*head;
	int		i;

	head = (*data)->tokens;
	while (head)
	{
		if (head->type == WORD && ft_strchr(head->value, 7))
		{
			i = get_position(head->value, 7);
			head->value[i] = '$';
		}
		if (!ft_strchr(head->value, 7))
			head = head->next;
	}
}

static void	do_delete_routine(t_data **data, t_token **curr, t_token **prev)
{
	if ((*curr)->type == HASH || (*curr)->value == NULL)
	{
		if (*prev)
		{
			(*prev)->next = (*curr)->next;
			free((*curr)->value);
			free(*curr);
			*curr = (*prev)->next;
		}
		else
		{
			(*data)->tokens = (*curr)->next;
			free((*curr)->value);
			free(*curr);
			*curr = (*data)->tokens;
		}
	}
	else
	{
		*prev = *curr;
		*curr = (*curr)->next;
	}
}

void	delete_empty_tokens(t_data **data)
{
	t_token	*curr;
	t_token	*prev;

	prev = NULL;
	if ((*data)->tokens)
	{
		curr = (*data)->tokens;
		while (curr)
			do_delete_routine(data, &curr, &prev);
	}
}
