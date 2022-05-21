/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:35:24 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/05/21 19:21:12 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_get_path(t_data *sh)
{
	char	*path;
//	char	**pathe;
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
		
static char *ft_get_cmd(t_data *sh, char **cmd)
{
	char	*s;
	char	*tmp;
	char	**path;
	int		i;

	if (!access(cmd[0], X_OK))
	{
		s = ft_strdup(cmd[0]);
		if (!s)
		{
			perror("system malfunction");
			exit(errno);
		}
		return (s);
	}
	path = ft_get_path(sh);
	if (!path)
		return (NULL);
	i = -1;
	while (path[++i])
	{
		 tmp = ft_strjoin(path[i], "/");
		 if (!tmp)
		 {
			perror("system malfunction");
			ft_free_tab(path);
			exit(errno);
		 }
		 s = ft_strjoin(tmp, cmd[0]);
		 free(tmp);
		 if (!s)
		 {
			perror("system malfunction");
			ft_free_tab(path);
			exit(errno);
		 }
		 if (!access(s, X_OK))
		 {
			 ft_free_tab(path);
			 return (s);
		 }
		 free(s);
	}
	ft_free_tab(path);
	return (NULL);
}

void	ft_exec_cmd(t_data *sh, char **cmd)
{
	char	**envp;
	char	*cmnd;

	cmnd = ft_get_cmd(sh, cmd);
	if (!cmnd)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
//		g_status = 127;
		exit(127);
	}
	envp = env_tab(sh, 0);
	if (!envp)
	{
		perror ("system malfunction");
		free(cmd);
//		g_status = errno;
		exit(errno);
	}
	ft_pathproofargs(cmd);
	if (execve(cmnd, cmd, envp) == -1)
	{
		perror("command not executed");
//		g_status = errno;
		free(cmnd);
		ft_free_tab(envp);
		exit(errno);
	}
}

//while fork pipess
/*void	ft_execute_command(t_data *sh, char **cmd)
{
	pid_t		id;
	t_env_lst	*tmp;
	int			i;

	id = fork();
	if (id == -1)
	{
		perror("fork kaputt");
//		g_status = errno;
		return ;
	}
	if (id && !sh->pp_nbr)
	{
	tmp = ft_get_env_var(sh, "_");
	if (!tmp->unset)
	{
		if (tmp->val)
			free(tmp->val);
		i = 0;
		while (cmd[i + 1])
			i++;
		tmp->val = ft_strdup(cmd[i]);
		if (!tmp->val)
			perror("system malfunction");
	}
	}
	if (!id)
		ft_procede(sh, cmd);
	waitpid(id, &sh->status, 0);
}*/
