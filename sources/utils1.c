/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 18:59:23 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/05/21 19:36:13 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_status(t_data *sh, char **cmd)
{
	char		*stts;
	t_env_lst	*tmp;
	int			j;
	int			status;

	status = sh->status;
	if (WIFEXITED(sh->status))
		status = WEXITSTATUS(sh->status);
	
	tmp = ft_get_env_var(sh, "_");
	if (!tmp->unset)
	{
		if (tmp->val)
			free(tmp->val);
		j = 0;
		while (cmd[j + 1])
			j++;
		if (j)
			tmp->val = ft_strdup(cmd[j]);
		else
			tmp->val = ft_itoa(status);
		if (!tmp->val)
			perror("system malfunction");
	}
	if (!status)
		ft_putstr_fd("minishell: 0: command not found\n", 2);
	else if (status == 127) 
		ft_putstr_fd("minishell: 127: command not found\n", 2);
	else
	{
		ft_putstr_fd("minishell: ", 2);
		if (j)
			ft_putstr_fd(tmp->val, 2);
		else
		{
			stts = ft_itoa(status);
			if (!stts)
				perror("system malfunction");
			ft_putstr_fd(stts, 2);
			free(stts);
		}
		ft_putstr_fd(": ", 2);
		stts = strerror(status);
		ft_putstr_fd(stts, 2);
		ft_putstr_fd("\n", 2);
	}
}

void	ft_underscore(t_data *sh, char **cmd)
{
	t_env_lst	*tmp;
	int			j;

	tmp = ft_get_env_var(sh, "_");
	if (!tmp->unset)
	{
		if (tmp->val)
			free(tmp->val);
		j = 0;
		while (cmd[j + 1])
			j++;
		tmp->val = ft_strdup(cmd[j]);
		if (!tmp->val)
			perror("system malfunction");
	}
}

void	ft_prompt(char *s)
{
	ft_putstr_fd(s, 2);
}

void ft_which_builtin(t_data *sh, char **cmd)
{
	if (!ft_strncmp("echo", cmd[0], ft_strlen(cmd[0])))
		ft_echo(sh, cmd);
	else if	(!ft_strncmp("pwd", cmd[0], ft_strlen(cmd[0])))
		ft_pwd(sh, cmd);
	else if (!ft_strncmp("cd", cmd[0], ft_strlen(cmd[0])))
		ft_cd(sh, cmd);
	else if (!ft_strncmp("unset", cmd[0], ft_strlen(cmd[0])))
		ft_unset(sh, cmd);
	else if (!ft_strncmp("export", cmd[0], ft_strlen(cmd[0])))
		ft_export(sh, cmd);
	else if (!ft_strncmp("exit", cmd[0], ft_strlen(cmd[0])))
		ft_exit(sh, cmd);
	else if (!ft_strncmp("env", cmd[0], ft_strlen(cmd[0])))
		ft_env(sh, cmd);
	else if (ft_strchr(cmd[0], '='))
		ft_add_env_var(sh, cmd);
	else if (*cmd[0] == '?')//
		ft_status(sh, cmd);
}
		
/*int	ft_is_builtin(t_data *sh, char *cmd)
{
	if (!ft_strncmp("echo", sh->cmd[i][0], ft_strlen(sh->cmd[i][0])) ||
		!ft_strncmp("pwd", sh->cmd[i][0], ft_strlen(sh->cmd[i][0])) ||
		!ft_strncmp("cd", sh->cmd[i][0], ft_strlen(sh->cmd[i][0])) ||
		!ft_strncmp("unset", sh->cmd[i][0], ft_strlen(sh->cmd[i][0])) ||
		!ft_strncmp("export", sh->cmd[i][0], ft_strlen(sh->cmd[i][0])) ||
		!ft_strncmp("exit", sh->cmd[i][0], ft_strlen(sh->cmd[i][0])) ||
		!ft_strncmp("env", sh->cmd[i][0], ft_strlen(sh->cmd[i][0])) ||
		(ft_strchr(sh->cmd[i][0], '=')) ||
		(*sh->cmd[i][0] == '?'))
	{
//		ft_which_builtin(sh);
		return (1);
	}
	return (0);
}*/
int	ft_is_builtin(char *cmd)
{
	if (!ft_strncmp("echo", cmd, ft_strlen(cmd)) ||
		!ft_strncmp("pwd", cmd, ft_strlen(cmd)) ||
		!ft_strncmp("cd", cmd, ft_strlen(cmd)) ||
		!ft_strncmp("unset", cmd, ft_strlen(cmd)) ||
		!ft_strncmp("export", cmd, ft_strlen(cmd)) ||
		!ft_strncmp("exit", cmd, ft_strlen(cmd)) ||
		!ft_strncmp("env", cmd, ft_strlen(cmd)) ||
		(ft_strchr(cmd, '=')) ||
		(*cmd == '?'))
	{
//		ft_which_builtin(sh);
		return (1);
	}
	return (0);
}
