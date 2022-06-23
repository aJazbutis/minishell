/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorunov <kmorunov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:55:10 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/06/22 22:57:01 by kmorunov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_failed_pipes(t_data *sh, int i)
{
	t_cmd	*cmd;

	cmd = sh->cmd;
	while (i)
	{
		close(cmd->pp[0]);
		close(cmd->pp[1]);
		i--;
		cmd = cmd->next;
	}
}

void	ft_close_pps(t_data *sh, int i)
{
	t_cmd	*cmd;

	cmd = sh->cmd;
	while (cmd)
	{
		close(cmd->pp[i]);
		cmd->here_fd = cmd->pp[0];
		if (!cmd->heredoc)
			close(cmd->pp[0]);
		cmd = cmd->next;
	}
}

int	ft_here_pipes(t_data *sh)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	cmd = sh->cmd;
	while (cmd)
	{
		if (pipe(cmd->pp))
		{
			ft_mini_perror(sh, "pipe kaputt");
			ft_failed_pipes(sh, i);
			return (1);
			i++;
		}
		cmd = cmd->next;
	}
	return (0);
}
