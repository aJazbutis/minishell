/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_uni_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorunov <kmorunov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 21:14:46 by kmorunov          #+#    #+#             */
/*   Updated: 2022/06/22 22:13:12 by kmorunov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(int c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (TRUE);
	return (FALSE);
}

int	is_delimeter(int c)
{
	if (c == '|' || c == '<' || c == '>')
		return (TRUE);
	return (FALSE);
}

int	is_redir(int c)
{
	if (c == REDIR_IN || c == REDIR_OUT || c == REDIR_APPEND
		|| c == REDIR_HEREDOC)
		return (TRUE);
	return (FALSE);
}

void	check_comments(t_data **data)
{
	t_token	*head;

	head = (*data)->tokens;
	while (head)
	{
		if (head->value[0] == '#')
		{
			while (head)
			{
				head->type = HASH;
				head = head->next;
			}
			return ;
		}
		head = head->next;
	}
}
