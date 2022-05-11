/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 18:59:23 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/05/10 16:32:58 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_prompt(char *s)
{
	ft_putstr_fd(s, 2);
}

static void ft_which_builtin(t_data *sh)
{
	if (!ft_strncmp("echo", sh->cmd[0], ft_strlen(sh->cmd[0])))
		ft_echo(sh);
	else if	(!ft_strncmp("pwd", sh->cmd[0], ft_strlen(sh->cmd[0])))
		ft_pwd();
	else if (!ft_strncmp("cd", sh->cmd[0], ft_strlen(sh->cmd[0])))
		ft_cd(sh);
	else if (!ft_strncmp("unset", sh->cmd[0], ft_strlen(sh->cmd[0])))
		ft_unset(sh);
//	else if (!ft_strncmp("export", sh->cmd[0], ft_strlen(sh->cmd[0])))
//		ft_export(sh);
	else if (!ft_strncmp("exit", sh->cmd[0], ft_strlen(sh->cmd[0])))
		ft_exit(sh);
	else if (!ft_strncmp("env", sh->cmd[0], ft_strlen(sh->cmd[0])))
		ft_env(sh);
	else if (ft_strchr(sh->cmd[0], '='))
		ft_add_env_var(sh);
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
		(ft_strchr(sh->cmd[0], '=')))
	{
		ft_which_builtin(sh);
		return (1);
	}
	return (0);
}
