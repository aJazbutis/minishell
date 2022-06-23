/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_route.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 19:13:58 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/06/14 23:52:58 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_which_builtin(t_data *sh, char **cmd)
{
	sh->status = 0;
	if (!ft_strncmp("echo", cmd[0], 5))
		ft_echo(sh, cmd);
	else if (!ft_strncmp("pwd", cmd[0], 4))
		ft_pwd(sh, cmd);
	else if (!ft_strncmp("cd", cmd[0], 3))
		ft_cd(sh, cmd);
	else if (!ft_strncmp("unset", cmd[0], 6))
		ft_unset(sh, cmd);
	else if (!ft_strncmp("export", cmd[0], 7))
		ft_export(sh, cmd);
	else if (!ft_strncmp("exit", cmd[0], 5))
		ft_exit(sh, cmd);
	else if (!ft_strncmp("env", cmd[0], 4))
		ft_env(sh);
	else if (ft_strchr(cmd[0], '='))
		ft_add_env_var(sh, cmd);
}

static void	ft_mini_child(t_data *sh)
{
	ft_underscore(sh, sh->cmd->cmd);
	sh->id = fork();
	if (sh->id == -1)
	{
		perror("fork kaputt");
		sh->status = errno;
		return ;
	}
	if (!sh->id)
	{
		if (*sh->cmd->cmd[0] == '.' || *sh->cmd->cmd[0] == '~')
			ft_exec_exe(sh, sh->cmd->cmd);
		else
			ft_exec_cmd(sh, sh->cmd->cmd);
	}
	wait(&sh->status);
	ft_status(sh);
}

void	ft_what_to_do(t_data *sh, char **cmd)
{
	if (!ft_strncmp("echo", cmd[0], 5))
		ft_echo(sh, cmd);
	else if (!ft_strncmp("pwd", cmd[0], 4))
		ft_pwd(sh, cmd);
	else if (!ft_strncmp("cd", cmd[0], 3))
		ft_cd(sh, cmd);
	else if (!ft_strncmp("unset", cmd[0], 6))
		ft_unset(sh, cmd);
	else if (!ft_strncmp("export", cmd[0], 7))
		ft_export(sh, cmd);
	else if (!ft_strncmp("exit", cmd[0], 5))
		ft_exit(sh, cmd);
	else if (!ft_strncmp("env", cmd[0], 4))
		ft_env(sh);
	else
		ft_mini_child(sh);
}

int	ft_is_builtin(char *cmd)
{
	if (!ft_strncmp("echo", cmd, 5)
		|| !ft_strncmp("pwd", cmd, 4)
		|| !ft_strncmp("cd", cmd, 3)
		|| !ft_strncmp("unset", cmd, 6)
		|| !ft_strncmp("export", cmd, 7)
		|| !ft_strncmp("exit", cmd, 5)
		|| !ft_strncmp("env", cmd, 4)
		|| (ft_strchr(cmd, '=')))
	{
		return (1);
	}
	return (0);
}
