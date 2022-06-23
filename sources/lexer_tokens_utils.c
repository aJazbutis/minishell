/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokens_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorunov <kmorunov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 21:14:56 by kmorunov          #+#    #+#             */
/*   Updated: 2022/06/22 19:30:34 by kmorunov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_count(t_token *token)
{
	t_token	*ptr;
	int		i;

	i = 0;
	ptr = token;
	while (ptr != NULL && ptr->type != PIPE)
	{
		if (ptr->type == WORD)
			i++;
		ptr = ptr->next;
	}
	return (i);
}

int	cut_token(char prev, char next, char *token, t_data *data)
{
	if (next == '\0')
		return (TRUE);
	if (is_space(next) && data->flag == 0)
		return (TRUE);
	if (!is_delimeter(prev) && is_delimeter(next) && data->flag == 0)
		return (TRUE);
	if (is_delimeter(prev) && !is_delimeter(next) && data->flag == 0)
		return (TRUE);
	if (is_delimeter(prev) && ft_strlen(token) > 1 && data->flag == 0)
		return (TRUE);
	if (prev == '|' && (next == '|' || is_delimeter(next)))
		return (TRUE);
	else
		return (FALSE);
}

t_token	*new_token(int c, char *token, t_data *data)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (tok == NULL)
		return (NULL);
	if (is_delimeter(c) && data->flag == 0)
		tok->type = OPERATOR;
	else
		tok->type = WORD;
	tok->value = ft_strdup(token);
	free(token);
	if (data->flag == '\"')
		tok->split = FALSE;
	else
		tok->split = TRUE;
	tok->next = NULL;
	return (tok);
}

t_token	*last_token(t_token *head)
{
	t_token	*ptr;

	ptr = head;
	if (head == NULL)
		return (NULL);
	while (ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}

void	save_token(t_token **head, t_token *new)
{
	t_token	*ptr;

	if (new == NULL)
		return ;
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	ptr = last_token(*head);
	ptr->next = new;
}
