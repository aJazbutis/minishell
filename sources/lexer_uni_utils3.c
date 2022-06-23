/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_uni_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorunov <kmorunov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:20:44 by kmorunov          #+#    #+#             */
/*   Updated: 2022/06/22 22:48:36 by kmorunov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	do_exp_routine(t_data **data, t_token *head, char *doll, int pos)
{
	char	*expand;

	expand = NULL;
	expand = check_exp(data, head, doll, pos);
	free(head->value);
	head->value = NULL;
	head->value = ft_strdup(expand);
	free(expand);
	expand = NULL;
}

void	do_expansion(t_data **data)
{
	t_token	*head;
	char	*dollar;
	int		position;
	int		length;

	head = (*data)->tokens;
	while (head)
	{
		dollar = ft_strchr(head->value, '$');
		if (dollar)
		{
			length = var_len(dollar + 1);
			position = get_position(head->value, '$');
			if (length != 0 || dollar[1] == '?')
				do_exp_routine(data, head, dollar, position);
		}
		if (!dollar || length == 0)
			head = head->next;
	}
	put_dollar_back(data);
}

static char	*do_qt_routine(t_data **data, char c, char *clean)
{
	if ((c != '\'' && c != '\"') || ((*data)->flag != c && (*data)->flag != 0))
		clean = append_str(clean, c);
	return (clean);
}

/*(*data)->tokens->split = 0 JUST A COUNTER!*/
void	remove_quotes(t_data **data)
{
	char	*clean;
	char	*dirty;
	t_token	*head;

	(*data)->flag = 0;
	head = (*data)->tokens;
	while (head)
	{
		(*data)->tokens->split = 0;
		clean = NULL;
		dirty = head->value;
		if (!dirty)
			return ;
		while (dirty[(*data)->tokens->split])
		{
			check_flag(dirty[(*data)->tokens->split], data);
			clean = do_qt_routine(data, dirty[(*data)->tokens->split], clean);
			((*data)->tokens->split)++;
		}
		free(head->value);
		head->value = ft_strdup(clean);
		free(clean);
		head = head->next;
		dirty = NULL;
	}
}
