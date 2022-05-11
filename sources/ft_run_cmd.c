/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:35:24 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/05/10 22:20:51 by ajazbuti         ###   ########.fr       */
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
		
static char *ft_get_cmd(t_data *sh)
{
	char	*s;
	char	*tmp;
	char	**path;
	int		i;

	if (!access(sh->cmd[0], X_OK))
	{
		s = ft_strdup(sh->cmd[0]);
		if (!s)
		{
			perror("system malfunction");
			exit(errno);
		}
		return (s);
	}
	path = ft_get_path(sh);
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
		 s = ft_strjoin(tmp, sh->cmd[0]);
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

static void	ft_procede(t_data *sh)
{
	char	**envp;
	char	*cmd;

	cmd = ft_get_cmd(sh);
	if (!cmd)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(sh->cmd[0], 2);
		ft_putstr_fd(": not found\n", 2);
		g_status = 127;
		exit(127);
	}
	envp = env_tab(sh);
	if (!envp)
	{
		perror ("system malfunction");
		free(cmd);
		g_status = errno;
		exit(errno);
	}
	if (execve(cmd, sh->cmd, envp) == -1)
	{
		perror("executable not executed");
		g_status = errno;
		free(cmd);
		ft_free_tab(envp);
		exit(errno);
	}
}

void	ft_execute_command(t_data *sh)
{
	pid_t	id;

	id = fork();
	if (id == -1)
	{
		perror("fork kaputt");
		g_status = errno;
		return ;
	}	
	if (!id)
		ft_procede(sh);
	waitpid(id, &g_status, 0);
}


