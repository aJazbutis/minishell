/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_executable.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 13:54:13 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/05/10 21:28:00 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_safe_path(char *path)
{
	char	*s;

	if (*path == '~')
	{
		path++;
		s = ft_strjoin(getenv("HOME"), path);
		if (!s)
			perror("system malfunction");
		printf("%s\n", s);
		path--;
	}
	else
	{
		s = ft_strdup(path);
		if (!s)
			perror("system malfunction");
	}
	return (s);
}
		
static void	ft_exec_executable(t_data *sh, char *path, char	**args)
{
	char	**envp;
	char	*pth;

	pth = ft_safe_path(path);
	if (access(pth, X_OK))
	{
		perror(path);
		free(pth);
		g_status = errno;
		exit(errno);
	}
	envp = env_tab(sh);
	if (!envp)
	{
		perror ("system malfunction");
		free(pth);
		g_status = errno;
		exit(errno);
	}
	if (execve(pth, args, envp) == -1)
	{
		perror("executable not executed");
		g_status = errno;
		free(pth);
		ft_free_tab(envp);
		exit(errno);
	}
}

void	ft_execute_executable(t_data *sh, char *path, char **args)
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
		ft_exec_executable(sh, path, args);
	waitpid(id, &g_status, 0);
}

