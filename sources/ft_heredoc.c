/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorunov <kmorunov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 17:54:53 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/06/22 22:49:37 by kmorunov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_here_write(t_data *sh, t_flst *here, int *pp)
{
	char	*line;
	int		*hd;

	hd = here->nbr;
	if (pp)
		hd = pp;
	ft_putstr_fd("> ", 1);
	line = get_next_line(0);
	while (line)
	{
		if (!ft_strncmp(here->str, line, ft_strlen(here->str))
			&& ft_strlen(line) - 1 == ft_strlen(here->str))
		{
			free(line);
			break ;
		}
		ft_here_expand(sh, line, hd[1]);
		free(line);
		ft_putstr_fd("> ", 1);
		line = get_next_line(0);
		if (!line)
			ft_putstr_fd("\b\b  \b\b", 1);
	}
	close(hd[1]);
	close(hd[0]);
}

static void	ft_exit_here(t_data *sh, char *msg)
{
	if (msg)
		ft_mini_perror(sh, msg);
	ft_clean_sh(sh);
	exit(sh->status);
}

static void	ft_heredocs(t_data *sh)
{
	t_cmd	*cmd;
	t_flst	*tmp;

	cmd = sh->cmd;
	while (cmd)
	{
		tmp = cmd->heredoc;
		while (tmp)
		{
			if (tmp->next)
			{
				if (pipe(tmp->nbr))
					ft_exit_here(sh, "pipe->kaputt");
				ft_here_write(sh, tmp, NULL);
			}
			else
				ft_here_write(sh, tmp, cmd->pp);
			tmp = tmp->next;
		}
		cmd = cmd->next;
	}
	ft_clean_sh(sh);
	exit(EXIT_SUCCESS);
}

int	ft_here_doc(t_data *sh)
{
	if (ft_here_pipes(sh))
		return (1);
	sh->id = fork();
	if (sh->id == -1)
	{
		ft_mini_perror(sh, "fork fail");
		return (1);
	}
	if (!sh->id)
	{
		ft_cntrl_here();
		ft_heredocs(sh);
	}
	ft_close_pps(sh, 1);
	signal(SIGINT, SIG_IGN);
	wait(&sh->status);
	signal(SIGINT, ft_cntrl_cntrl);
	ft_status(sh);
	if (sh->status == 2)
	{
		sh->status = sh->status + 128;
		ft_close_pps(sh, 0);
		return (1);
	}
	return (0);
}
