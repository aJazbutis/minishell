/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 23:04:59 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/05/21 18:58:05 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_close_pipes(t_data *sh, int pipe_fail)
{
	int	i;
	int	n;

	i = -1;
	n = sh->pp_n;
	if (pipe_fail)
		n = pipe_fail;
	while (++i < n)
	{
		close(*(sh->pp + 2 * i));
		close(*(sh->pp + 2 * i + 1));
	}
	if (sh->here_doc)
		close(sh->pp1[0]);
}

static void	ft_clean_child(t_data *sh, char *msg)
{
	if (sh->cmd1)
		free(sh->cmd1);
	sh->cmd1 = NULL;
	ft_close_pipes(sh, 0);
	ft_clean_exit(msg, sh);
}
static void	ft_dup2_dup2(int inpt, int outpt)
{
	dup2(inpt, 0);
	dup2(outpt, 1);
}

static void	ft_dup_dup(t_data *sh, int i, int ac, char **av)
{
	if (!i)
	{
		if (sh->here_doc)
			ft_dup2_dup2(sh->pp1[0], *(sh->pp + 2 * i + 1));
		else
		{
			sh->fd[0] = open(av[1], O_RDONLY);
			if (sh->fd[0] < 0)
				ft_clean_child(sh, av[1]);
			ft_dup2_dup2(sh->fd[0], *(sh->pp + 2 * i + 1));
		}
	}
	if (i == sh->cmd_n - 1)
	{
		if (sh->here_doc)
			sh->fd[1] = open(av[ac -1], O_CREAT | O_APPEND | O_WRONLY, 0644);
		else
			sh->fd[1] = open(av[ac -1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (sh->fd[1] < 0)
			ft_clean_child(sh, av[ac - 1]);
		ft_dup2_dup2(*(sh->pp + 2 * i - 2), sh->fd[1]);
	}
	else
		ft_dup2_dup2(*(sh->pp + 2 * i - 2), *(sh->pp + 2 * i + 1));
}

static void	ft_child(t_data *sh, int i, int ac, char **av)
{
	if (sh->id == 0)
	{
		sh->cmd1 = ft_get_cmnd(sh, sh->cmd[i][0]);
		ft_dup_dup(sh, i, ac, av);
		ft_close_pipes(sh, 0);
		if (!(sh->cmd1))
		{
			ft_putstr_fd("sh: command not found: ", 2);
			ft_putstr_fd(sh->cmd[i][0], 2);
			ft_putstr_fd("\n", 2);
			ft_clean_exit(NULL, sh);
		}
		execve(sh->cmd1, sh->cmd[i], sh->ep);
	}
}

void	ft_piping(t_data *sh)
{
	int	i;
	int	j;

	
	if (sh->pp_n)
	i = -1;
	sh->pp = (int *)malloc(sizeof(int) * 2 * (sh->pp_n));
	if (!(sh->pp))
	{
	//	ft_clean_exit("Malloc->kaputt", sh);
		perror("Malloc -> kaputt");
		return ;
	}
	while (++i < sh->pp_n)
	{
		if (pipe(sh->pp + 2 * i))
		{
			if (i)
				ft_close_pipes(sh, i);
			ft_clean_exit("pipe()->kaputt", sh);
		}
	}
	i = -1;
	j = 0;
	while (cmd[++i])
	{
		if (ft_isbuiltin(sh->cmd[i][0]))
			//dupdup built in cmd

		else
		{
			sh->id = fork();
			if (sh->id == -1)
				ft_clean_child(sh, "fork()->kaputt");
			if (sh->id)
				j++;	
			ft_child(sh, i, ac, av);
		}
	}
	ft_close_pipes(sh, 0);
	while (j--)
//		waitpid(-1, NULL, 0);
		wait(&g_status);
}
