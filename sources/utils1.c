/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 18:59:23 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/05/12 21:32:58 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_status(int status)
{
	char	*stts;

	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	if (status == 127)
	{
		ft_putstr_fd("minishell: 127: command not found\n", 2);
		return ;
	}
	stts = strerror(status);
	ft_putstr_fd(stts, 2);
ft_putstr_fd("\n", 2);
}

void	ft_underscore(t_data *sh)
{
	t_env_lst	*tmp;
	int			i;

	tmp = ft_get_env_var(sh, "_");
	if (!tmp->unset)
	{
		if (tmp->val)
			free(tmp->val);
		i = 0;
		while (sh->cmd[i + 1])
			i++;
		tmp->val = ft_strdup(sh->cmd[i]);
		if (!tmp->val)
			perror("system malfunction");
	}
}

void	ft_prompt(char *s)
{
	ft_putstr_fd(s, 2);
}

static void ft_which_builtin(t_data *sh)
{
	if (!ft_strncmp("echo", sh->cmd[0], ft_strlen(sh->cmd[0])))
		ft_echo(sh);
	else if	(!ft_strncmp("pwd", sh->cmd[0], ft_strlen(sh->cmd[0])))
		ft_pwd(sh);
	else if (!ft_strncmp("cd", sh->cmd[0], ft_strlen(sh->cmd[0])))
		ft_cd(sh);
	else if (!ft_strncmp("unset", sh->cmd[0], ft_strlen(sh->cmd[0])))
		ft_unset(sh);
	else if (!ft_strncmp("export", sh->cmd[0], ft_strlen(sh->cmd[0])))
		ft_export(sh);
	else if (!ft_strncmp("exit", sh->cmd[0], ft_strlen(sh->cmd[0])))
		ft_exit(sh);
	else if (!ft_strncmp("env", sh->cmd[0], ft_strlen(sh->cmd[0])))
		ft_env(sh);
	else if (ft_strchr(sh->cmd[0], '='))
		ft_add_env_var(sh);
	else if (*sh->cmd[0] == '?')
		ft_status(g_status);
}
		
int	ft_is_builtin(t_data *sh)
{
	if (!ft_strncmp("echo", sh->cmd[0], ft_strlen(sh->cmd[0])) ||
		!ft_strncmp("pwd", sh->cmd[0], ft_strlen(sh->cmd[0])) ||
		!ft_strncmp("cd", sh->cmd[0], ft_strlen(sh->cmd[0])) ||
		!ft_strncmp("unset", sh->cmd[0], ft_strlen(sh->cmd[0])) ||
		!ft_strncmp("export", sh->cmd[0], ft_strlen(sh->cmd[0])) ||
		!ft_strncmp("exit", sh->cmd[0], ft_strlen(sh->cmd[0])) ||
		!ft_strncmp("env", sh->cmd[0], ft_strlen(sh->cmd[0])) ||
		(ft_strchr(sh->cmd[0], '=')) ||
		(*sh->cmd[0] == '?'))
	{
		ft_which_builtin(sh);
		return (1);
	}
	return (0);
}
