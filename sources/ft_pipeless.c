/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipeless.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorunov <kmorunov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 01:18:48 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/06/22 16:38:08 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_redirs(t_data *sh)
{
	if (sh->cmd->heredoc)
	{
		if (ft_here_doc(sh))
			return (1);
	}
	sh->fd[0] = ft_redir_in(sh, sh->cmd, 0);
	if (sh->fd[0] < 0)
	{
		if (sh->cmd->heredoc)
			close(sh->cmd->here_fd);
		return (1);
	}
	sh->fd[1] = ft_redir_out(sh, sh->cmd, 1);
	if (sh->fd[1] < 0)
	{
		close(sh->fd[0]);
		return (1);
	}
	ft_dup2_dup2(sh->fd[0], sh->fd[1]);
	if (sh->cmd->heredoc)
		close(sh->cmd->here_fd);
	return (0);
}

static void	ft_child(t_data *sh)
{
	if (!sh->id)
	{
		if (sh->cmd->heredoc)
			close(sh->cmd->here_fd);
		if (*sh->cmd->cmd[0] == '.' || *sh->cmd->cmd[0] == '~')
			ft_exec_exe(sh, sh->cmd->cmd);
		else
			ft_exec_cmd(sh, sh->cmd->cmd);
	}
}

static void	ft_quit3(t_data *sh)
{
	if (sh->status == 130)
		ft_putstr_fd("\n", 1);
	else if (sh->status == 131)
		ft_putstr_fd("Quit: 3\n", 1);
}

static void	ft_lose_ends(t_data *sh)
{
	if (sh->cmd->in)
		close(sh->fd[0]);
	if (sh->cmd->out)
		close(sh->fd[1]);
}

void	ft_pipeless(t_data *sh)
{
	if (ft_redirs(sh))
		return ;
	if (sh->cmd->cmd)
	{
		if (ft_is_builtin(sh->cmd->cmd[0]))
			ft_which_builtin(sh, sh->cmd->cmd);
		else
		{
			ft_underscore(sh, sh->cmd->cmd);
			sh->id = fork();
			if (sh->id == -1)
				ft_mini_perror(sh, "fork kaputt");
			else
			{
				ft_child(sh);
				signal(SIGINT, SIG_IGN);
				wait(&sh->status);
				ft_status(sh);
				ft_quit3(sh);
			}
		}
	}
	ft_lose_ends(sh);
}
