/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorunov <kmorunov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 21:14:39 by kmorunov          #+#    #+#             */
/*   Updated: 2022/06/20 16:30:48 by kmorunov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_flst	*new_redir(char *value, int redir_mode)
{
	t_flst	*new;

	new = malloc(sizeof(t_flst));
	if (new == NULL)
		return (NULL);
	new->str = ft_strdup(value);
	if (redir_mode == REDIR_APPEND)
	{
		new->nbr[0] = TRUE;
		new->nbr[1] = FALSE;
	}
	else
	{
		new->nbr[0] = FALSE;
		new->nbr[1] = FALSE;
	}
	new->next = NULL;
	return (new);
}

void	add_out(t_cmd **cmd, char *value, int redir_mode)
{
	t_flst	*new;
	t_flst	*ptr;

	ptr = (*cmd)->out;
	new = new_redir(value, redir_mode);
	if (new == NULL)
		return ;
	if ((*cmd)->out == NULL)
	{
		(*cmd)->out = new;
		return ;
	}
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = new;
}

void	append_in(t_flst **head, t_flst *new)
{
	t_flst	*ptr;

	ptr = *head;
	if (new == NULL)
		return ;
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = new;
}

void	add_in(t_cmd **cmd, char *value, int redir_mode, int *count)
{
	t_flst	*new;

	new = NULL;
	if (*count > 0)
	{
		while (*count > 0)
		{
			new = new_redir("heredoc", FALSE);
			append_in(&(*cmd)->in, new);
			(*count)--;
		}
	}
	if (redir_mode == REDIR_HEREDOC)
	{
		(*count)++;
		new = new_redir(value, FALSE);
		append_in(&(*cmd)->heredoc, new);
	}
	else if (redir_mode == REDIR_IN)
	{
		new = new_redir(value, FALSE);
		append_in(&(*cmd)->in, new);
	}
}

int	redirection(t_cmd **cmd, t_token *head)
{
	int	last;
	int	count;

	last = 0;
	count = 0;
	while (head != NULL && head->type != PIPE)
	{
		if (is_redir(head->type))
			last = head->type;
		if (head->type == REDIR_FILE)
		{
			if (last == REDIR_OUT || last == REDIR_APPEND)
				add_out(cmd, head->value, last);
			else if (last == REDIR_IN || last == REDIR_HEREDOC)
				add_in(cmd, head->value, last, &count);
			if (count)
				add_in(cmd, 0, 0, &count);
			last = 0;
		}
		head = head->next;
	}
	return (0);
}
