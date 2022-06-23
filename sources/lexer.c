/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorunov <kmorunov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 21:10:18 by kmorunov          #+#    #+#             */
/*   Updated: 2022/06/22 20:47:40 by kmorunov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_count(t_token *token)
{
	t_token	*ptr;
	int		i;

	i = 0;
	ptr = token;
	while (ptr)
	{
		if (ptr->type == PIPE)
			i++;
		ptr = ptr->next;
	}
	return (i);
}

int	check_fn(const char *filename)
{
	int	i;

	i = 0;
	while (filename[i])
	{
		if (filename[i] == ';' || filename[i] == '\\')
			return (0);
		i++;
	}
	return (1);
}

void	get_tokens(t_data **data)
{
	char	*token_value;
	t_token	*token;
	char	*line;
	int		i;

	i = 0;
	token_value = NULL;
	line = (*data)->input;
	while (line[i])
	{
		check_flag(line[i], data);
		if (line[i] == '$' && (*data)->flag == '\'')
			line[i] = 7;
		if (!is_space(line[i]) || (*data)->flag != 0)
		{
			token_value = append_str(token_value, line[i]);
			if (cut_token(line[i], line[i + 1], token_value, *data))
			{
				token = new_token(line[i], token_value, *data);
				save_token(&(*data)->tokens, token);
				token_value = NULL;
			}
		}
		i++;
	}
}

void	get_more_tokens(t_data **data)
{
	t_token	*head;

	head = (*data)->tokens;
	while (head)
	{
		if (head->type == OPERATOR && head->value != NULL)
		{
			if (!ft_strcmp(head->value, ">") || !ft_strcmp(head->value, ">|"))
				head->type = REDIR_OUT;
			else if ((!ft_strcmp(head->value, "|")))
				head->type = PIPE;
			else if ((!ft_strcmp(head->value, "<<")))
				head->type = REDIR_HEREDOC;
			else if ((!ft_strcmp(head->value, "<")))
				head->type = REDIR_IN;
			else if ((!ft_strcmp(head->value, ">>")))
				head->type = REDIR_APPEND;
			if (is_redir(head->type)
				&& head->next != NULL && head->next->type == WORD)
				head->next->type = REDIR_FILE;
		}
		else if (head->type != REDIR_FILE && head->type != HASH)
			head->type = WORD;
		head = head->next;
	}
}

int	ft_lex(t_data **data)
{
	get_tokens(data);
	check_comments(data);
	do_expansion(data);
	remove_quotes(data);
	get_more_tokens(data);
	delete_empty_tokens(data);
	return (error_check(data));
}
