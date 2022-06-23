/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorunov <kmorunov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 21:10:47 by kmorunov          #+#    #+#             */
/*   Updated: 2022/06/20 23:59:52 by kmorunov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_init(t_cmd **cmd)
{
	*cmd = malloc(sizeof(t_cmd));
	if (!(*cmd))
		return ;
	(*cmd)->cmd = NULL;
	(*cmd)->in = NULL;
	(*cmd)->out = NULL;
	(*cmd)->heredoc = NULL;
	(*cmd)->next = NULL;
}

static void	do_routine(int i, t_cmd **command, t_token **head)
{
	int	j;

	j = 0;
	(*command)->cmd = malloc(sizeof(char *) * (i + 1));
	(*command)->cmd[i] = NULL;
	while ((*head) != NULL && (*head)->type != PIPE)
	{
		if ((*head)->type == WORD)
		{
			(*command)->cmd[j] = ft_strdup((*head)->value);
			j++;
		}
		(*head) = (*head)->next;
	}
}

static int	is_quote(const char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] != '\"' && string[i] != '\'')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static int	give_str_cmd(t_data **data, t_token *head, t_cmd **command)
{
	if (!head && (*data)->flag == 0 && is_quote((*data)->input))
	{
		(*command)->cmd = malloc(sizeof(char *) * (1 + 1));
		(*command)->cmd[0] = ft_strdup("\0");
		(*command)->cmd[1] = NULL;
		return (1);
	}
	return (0);
}

void	ft_parse(t_data **data)
{
	t_token	*head;
	t_cmd	*command;
	int		i;

	head = (*data)->tokens;
	cmd_init(&(*data)->cmd);
	command = (*data)->cmd;
	if (give_str_cmd(data, head, &command))
		return ;
	while (head && !redirection(&command, head))
	{
		i = token_count(head);
		if (i)
			do_routine(i, &command, &head);
		else
			command->cmd = NULL;
		while (head != NULL && head->type != PIPE)
			head = head->next;
		if (head == NULL)
			break ;
		head = head->next;
		cmd_init(&command->next);
		command = command->next;
	}	
}
