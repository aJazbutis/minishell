/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorunov <kmorunov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 23:42:10 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/06/23 14:21:04 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_dup_dup(t_data *sh, t_cmd *cmd, int i)
{
	if (!i)
	{
		sh->fd[0] = ft_redir_in(sh, cmd, 0);
		if (sh->fd[0] < 0)
			ft_clean_child(sh, NULL);
		sh->fd[1] = ft_redir_out(sh, cmd, *(sh->pp + 2 * i + 1));
	}
	else if (i == sh->pp_n)
	{
		sh->fd[0] = ft_redir_in(sh, cmd, *(sh->pp + 2 * i - 2));
		if (sh->fd[0] < 0)
			ft_clean_child(sh, NULL);
		sh->fd[1] = ft_redir_out(sh, cmd, 1);
	}
	else
	{
		sh->fd[0] = ft_redir_in(sh, cmd, *(sh->pp + 2 * i - 2));
		if (sh->fd[0] < 0)
			ft_clean_child(sh, NULL);
		sh->fd[1] = ft_redir_out(sh, cmd, *(sh->pp + 2 * i + 1));
	}
	if (sh->fd[1] < 0)
		ft_clean_child(sh, NULL);
}

static void	ft_child(t_data *sh, t_cmd *cmd, int i)
{
	if (sh->id == 0)
	{
		ft_dup_dup(sh, cmd, i);
		ft_dup2_dup2(sh->fd[0], sh->fd[1]);
		ft_close_pipes(sh, 0);
		if (cmd->cmd)
		{
			if (ft_is_builtin(cmd->cmd[0]))
			{
				ft_which_builtin(sh, cmd->cmd);
				ft_clean_child(sh, NULL);
			}
			else if (*cmd->cmd[0] == '.' || *cmd->cmd[0] == '~')
				ft_exec_exe(sh, cmd->cmd);
			else
				ft_exec_cmd(sh, cmd->cmd);
		}
		else
			ft_clean_child(sh, NULL);
	}
}

static int	ft_spawns(t_data *sh)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	cmd = sh->cmd;
	while (cmd)
	{
		sh->id = fork();
		if (sh->id == -1)
		{
			ft_mini_perror(sh, "fork kaputt");
			return (i);
		}
		ft_child(sh, cmd, i);
		++i;
		cmd = cmd->next;
	}
	return (i);
}

static int	ft_got_heredoc(t_data *sh)
{
	t_cmd	*cmd;

	cmd = sh->cmd;
	while (cmd)
	{
		if (cmd->heredoc)
			return (1);
		cmd = cmd->next;
	}
	return (0);
}

/*	Before first 'if' statement - ft_minor_expnd(sh); */

void	ft_exec(t_data *sh)
{
	int		i;

	sh->pp_n = ft_cmdsize(sh->cmd) - 1;
	if (!sh->pp_n)
		ft_pipeless(sh);
	else
	{
		ft_underscore(sh, NULL);
		if (ft_got_heredoc(sh))
		{
			if (ft_here_doc(sh))
				return ;
		}
		if (ft_pipes(sh))
			return ;
		i = ft_spawns(sh);
		signal(SIGINT, SIG_IGN);
		ft_close_pipes(sh, 0);
		while (i--)
			wait(&sh->status);
		ft_status(sh);
	}
}
