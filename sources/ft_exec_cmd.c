/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:35:24 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/06/20 19:44:51 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_get_path(t_data *sh)
{
	char	*path;
	char	**pathes;

	path = ft_getenv(sh, "PATH");
	if (!path)
		return (NULL);
	pathes = ft_split(path, ':');
	free(path);
	if (!pathes)
	{
		perror("system malfunction");
		exit(errno);
	}
	return (pathes);
}

static char	*ft_combine_cmd(t_data *sh, char **path, char *cmd)
{
	char	*tmp;
	char	*s;
	int		i;

	i = -1;
	s = NULL;
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], "/");
		if (ft_malloc_error(sh, tmp))
			break ;
		s = ft_strjoin(tmp, cmd);
		free(tmp);
		if (ft_malloc_error(sh, s))
			break ;
		if (!access(s, X_OK))
			break ;
		free(s);
		s = NULL;
	}
	ft_free_tab(path);
	return (s);
}

static char	*ft_get_cmd(t_data *sh, char **cmd)
{
	char	*s;
	char	**path;

	if (cmd[0][0] == '\0')
		return (NULL);
	if (!access(cmd[0], X_OK))
	{
		s = ft_strdup(cmd[0]);
		ft_malloc_error(sh, s);
		return (s);
	}
	path = ft_get_path(sh);
	if (!path)
		return (NULL);
	s = ft_combine_cmd(sh, path, cmd[0]);
	return (s);
}

void	ft_exec_cmd(t_data *sh, char **cmd)
{
	char	**envp;
	char	*full_cmd;

	ft_uncntrl();
	full_cmd = ft_get_cmd(sh, cmd);
	if (!full_cmd)
	{
		ft_putstr_fd("\033[1;35m<( ^.^ )>\033[1;0m\033[0m: ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		ft_clean_sh(sh);
		exit(127);
	}
	ft_pre_exec_env(sh, full_cmd);
	envp = env_tab(sh);
	if (envp)
	{
		ft_pathproofargs(sh, cmd);
		if (execve(full_cmd, cmd, envp) == -1)
			ft_mini_perror(sh, "command not executed");
	}
	free(full_cmd);
	ft_free_tab(envp);
	ft_clean_sh(sh);
	exit(errno);
}
