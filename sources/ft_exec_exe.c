/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_exe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 13:54:13 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/06/15 21:51:25 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static char	*ft_safe_path(t_data *sh, char *path)
{
	char	*s;

	if (*path == '~')
	{
		path++;
		s = ft_strjoin(getenv("HOME"), path);
		path--;
		ft_malloc_error(sh, s);
	}
	else
	{
		s = ft_strdup(path);
		ft_malloc_error(sh, s);
	}
	return (s);
}*/

void	ft_pathproofargs(t_data *sh, char **cmd)
{
	char	*s;
	int		i;

	i = -1;
	while (cmd[++i])
	{
		if (!ft_strncmp(cmd[i], "./minishell", 12))
		{
			s = ft_strdup(sh->location);
			if (ft_malloc_error(sh, s))
				return ;
			free(cmd[i]);
			cmd[i] = s;
		}
		else if (*cmd[i] == '~')
		{
			cmd[i]++;
			s = ft_strjoin(getenv("HOME"), cmd[i]);
			cmd[i]--;
			if (ft_malloc_error(sh, s))
				return ;
			free(cmd[i]);
			cmd[i] = s;
		}
	}
}

void	ft_exec_exe(t_data *sh, char **cmd)
{
	char	**envp;

	ft_pathproofargs(sh, cmd);
	ft_pre_exec_env(sh, cmd[0]);
	envp = env_tab(sh);
	if (envp)
	{
		ft_pathproofargs(sh, cmd);
		if (access(cmd[0], X_OK))
		{
			ft_mini_perror(sh, cmd[0]);
			ft_clean_sh(sh);
			exit(126);
		}
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (execve(cmd[0], cmd, envp) == -1)
			ft_mini_perror(sh, "executable not executed");
	}
	ft_free_tab(envp);
	ft_clean_sh(sh);
	exit(errno);
}
