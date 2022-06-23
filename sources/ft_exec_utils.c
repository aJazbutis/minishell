/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 23:42:28 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/06/20 21:47:31 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pipes(t_data *sh)
{
	int		i;

	sh->pp = (int *)malloc(sizeof(int) * 2 * (sh->pp_n));
	if (ft_malloc_error(sh, sh->pp))
		return (sh->status);
	i = -1;
	while (++i < sh->pp_n)
	{
		if (pipe(sh->pp + 2 * i))
		{
			if (i)
			{
				ft_close_pipes(sh, i);
				ft_mini_perror(sh, "pipe kaputt");
				return (sh->status);
			}
		}
	}
	return (0);
}

void	ft_close_pipes(t_data *sh, int pipe_fail)
{
	int		i;
	int		n;
	t_cmd	*cmd;

	i = -1;
	cmd = sh->cmd;
	n = sh->pp_n;
	if (pipe_fail)
		n = pipe_fail;
	while (++i < n)
	{
		close(*(sh->pp + 2 * i));
		close(*(sh->pp + 2 * i + 1));
	}
	while (cmd)
	{
		if (cmd->heredoc)
			close(cmd->here_fd);
		cmd = cmd->next;
	}
}

void	ft_clean_child(t_data *sh, char *msg)
{
	int	ret;

	if (msg)
		ft_mini_perror(sh, msg);
	ret = sh->status;
	ft_close_pipes(sh, 0);
	ft_clean_sh(sh);
	exit(ret);
}
