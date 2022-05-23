/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 21:57:46 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/05/23 22:20:06 by ajazbuti         ###   ########.fr       */
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

/*static void	ft_clean_child(t_data *sh, char *msg)
{
	if (sh->cmd1)
		free(sh->cmd1);
	sh->cmd1 = NULL;
	ft_close_pipes(sh, 0);
	ft_clean_exit(msg, sh);
}*/
static void	ft_dup2_dup2(int inpt, int outpt)
{
	dup2(inpt, 0);
	dup2(outpt, 1);
}

static void	ft_dup_dup(t_data *sh, int i)
{
	if (!i)
	{
//		if (sh->here_doc)
//			ft_dup2_dup2(sh->pp1[0], *(sh->pp + 2 * i + 1));
//		else
//		{
		if (sh->in)
		{
			sh->fd[0] = open(sh->in, O_RDONLY);
			if (sh->fd[0] < 0)
			{
				perror (sh->in);
				exit(errno);
			//	ft_clean_child(sh, av[1]);
			}
			ft_dup2_dup2(sh->fd[0], *(sh->pp + 2 * i + 1));
		}
		else
			ft_dup2_dup2(0, *(sh->pp + 2 * i + 1));
//		}
	}
	if (i == sh->pp_n)
	{
	//	if (sh->append)
//			sh->fd[1] = open(sh->out, O_CREAT | O_APPEND | O_WRONLY, 0644);
//		else
		if (sh->out)
		{
			sh->fd[1] = open(sh->out, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (sh->fd[1] < 0)
			exit(errno);
		//	ft_clean_child(sh, av[ac - 1]);
		ft_dup2_dup2(*(sh->pp + 2 * i - 2), sh->fd[1]);
		}
		else
			ft_dup2_dup2(*(sh->pp + 2 * i - 2), 1);
		
	}
	else
		ft_dup2_dup2(*(sh->pp + 2 * i - 2), *(sh->pp + 2 * i + 1));
}

static void	ft_child(t_data *sh, char **cmd, int i)
{

	if (sh->id == 0)
	{

//		printf("%s\n", cmd[0]);
		ft_dup_dup(sh, i);
		ft_close_pipes(sh, 0);
		//
		if (ft_is_builtin(cmd[0]))//how it's not segmenting
		{
			ft_which_builtin(sh, cmd);//child versio
			//clean
			exit(sh->status);
		}
		else if (*cmd[0] == '.' || *cmd[0] == '~')//how it's not segmenting
			ft_exec_exe(sh, cmd);
		else
			ft_exec_cmd(sh, cmd);
	}
}
static void	ft_pipeless(t_data *sh)
{
//	t_env_lst	*tmp;
//	int			i;
	
/*	tmp = ft_get_env_var(sh, "_");
	if (!tmp->unset)
	{
		if (tmp->val)
			free(tmp->val);
		i = 0;
		while (sh->cmd->cmd[i + 1])
			i++;
		tmp->val = ft_strdup(sh->cmd->cmd[i]);
		if (!tmp->val)
			perror("system malfunction");
	}*/
	if (ft_is_builtin(sh->cmd->cmd[0]))
		ft_which_builtin(sh, sh->cmd->cmd);
	else
	{
		sh->id = fork();
		if (sh->id == -1)
		{
			perror("fork kaputt");
//		ddg_status = errno;
			exit(errno); //exit
		}
		if (!sh->id)
		{
			if (*sh->cmd->cmd[0] == '.' || *sh->cmd->cmd[0] == '~')
				ft_exec_exe(sh, sh->cmd->cmd);
			else
				ft_exec_cmd(sh, sh->cmd->cmd);
		}
	wait(&sh->status);
	}
}

void	ft_exec(t_data *sh)
{
	int		i;
	t_cmd	*tmp;

	if (!sh->pp_n)
		ft_pipeless(sh);
	//printf("%d\n", sh->pp_n);
	else
	{
		//UPDATE _ WITH NULL
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
				exit(errno);
	//			ft_clean_exit("pipe()->kaputt", sh);
			}
		}
		i = -1;
		tmp = sh->cmd;
		while (++i < sh->pp_n + 1)
//		while (tmp)
		{
			sh->id = fork();
//			if (sh->id == -1)
//				ft_clean_child(sh, "fork()->kaputt");
			if (tmp->cmd)
				ft_child(sh, tmp->cmd, i);
			else
				ft_child(sh, NULL, i);
			if (tmp)
				tmp = tmp->next;
		}
	}
	ft_close_pipes(sh, 0);
	i = -1;
	while (++i < sh->pp_n + 1)
//	while (++i < ft_cmdsize(sh->cmd))
		wait(&sh->status);
}
