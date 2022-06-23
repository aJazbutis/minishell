/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_error_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorunov <kmorunov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 18:34:41 by kmorunov          #+#    #+#             */
/*   Updated: 2022/06/21 00:07:48 by kmorunov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_my_err(char *value)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `",
		STDERR_FILENO);
	ft_putstr_fd(value, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
}

static int	print_error(t_data **data, int error, char *value)
{
	(*data)->status = 258;
	if (error == QT)
	{
		ft_putstr_fd("minishell: unexpected EOF while ", STDERR_FILENO);
		ft_putstr_fd("looking for matching quote\n", STDERR_FILENO);
	}
	else if (error == PP)
	{
		ft_putstr_fd("minishell: syntax error near ", STDERR_FILENO);
		ft_putstr_fd("unexpected token `|'\n", STDERR_FILENO);
	}
	else if (error == NL)
	{
		ft_putstr_fd("minishell: syntax error near ", STDERR_FILENO);
		ft_putstr_fd("unexpected token `newline'\n", STDERR_FILENO);
	}
	else if ((!error && value) || error == RD)
		print_my_err(value);
	else if (error == DLM)
		print_my_err(value);
	else if (error == INV && value)
		print_my_err(value);
	return (1);
}

static int	do_err_routine(t_data **data, int *i, t_token *head)
{
	if (*i == 1 && head->type == PIPE)
		return (print_error(data, PP, NULL));
	else if (*i == 1 && (is_redir(head->type) && head->next == NULL))
		return (print_error(data, NL, NULL));
	else if (is_redir(head->type) && head->next
		&& (is_redir(head->next->type || head->next->type != REDIR_FILE)))
		return (print_error(data, 0, head->next->value));
	else if (head->type == REDIR_HEREDOC && head->next->type != REDIR_FILE)
		return (print_error(data, 0, head->next->value));
	else if (head->type == REDIR_HEREDOC
		&& !check_fn(head->next->value))
		return (print_error(data, DLM, head->next->value));
	else if ((is_redir(head->type) && !head->next))
		return (print_error(data, NL, NULL));
	else if (is_redir(head->type) && is_redir(head->next->type))
		return (print_error(data, RD, head->next->value));
	*i = 2;
	return (0);
}

/*
static int	do_qt_err_check(t_data **data)
{
	if ((*data)->flag != 0)
		return (print_error(data, QT, NULL));
	return (0);
}
*/

int	error_check(t_data **data)
{
	t_token	*head;
	int		pipe;

	pipe = pipe_count((*data)->tokens);
	head = (*data)->tokens;
	while (pipe + 1)
	{
		if ((*data)->flag != 0)
			return (print_error(data, QT, NULL));
		(*data)->id = 1;
		while (head && (*data)->id && head->type != PIPE)
		{
			if (do_err_routine(data, &(*data)->id, head))
				return (1);
			head = head->next;
		}
		pipe--;
		if (head == NULL)
			break ;
		if (head->next)
			head = head->next;
		else
			return (print_error(data, PP, NULL));
	}
	return (0);
}
