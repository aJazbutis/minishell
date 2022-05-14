/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_executable.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 13:54:13 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/05/14 22:42:31 by ajazbuti         ###   ########.fr       */
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
//		printf("%s\n", s);
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

void	ft_pathproofargs(t_data *sh)
{
	char	*s;
	int		i;

	i = 0;
	while (sh->cmd[++i])
	{
		if (*sh->cmd[i] == '~')
		{
			sh->cmd[i]++;
			s = ft_strjoin(getenv("HOME"), sh->cmd[i]);
			if (!s)
				perror("system malfunction");
			sh->cmd[i]--;
			free(sh->cmd[i]);
			sh->cmd[i] = s;
		}
	}
}

static void	ft_exec_executable(t_data *sh)
{
	char	**envp;
	char	*pth;

	pth = ft_safe_path(sh->cmd[0]);
	if (access(pth, X_OK))
	{
		perror(sh->cmd[0]);
		free(pth);
//		g_status = errno;
		exit(errno);
	}
	envp = env_tab(sh);
	if (!envp)
	{
		perror ("system malfunction");
		free(pth);
//		g_status = errno;
		exit(errno);
	}
	ft_pathproofargs(sh);
	printf("%s\n", sh->cmd[1]);
	if (execve(pth, sh->cmd, envp) == -1)
	{
		perror("executable not executed");
		g_status = errno;
		free(pth);
		ft_free_tab(envp);
		//clean strct
		exit(errno);
	}
}

void	ft_execute_executable(t_data *sh)
{
	pid_t		id;
	t_env_lst	*tmp;
	int			i;

	id = fork();
	if (id == -1)
	{
		perror("fork kaputt");
		g_status = errno;
		return ;
	}
	if (id)
	{
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
	if (!id)
		ft_exec_executable(sh);
	waitpid(id, &g_status, 0);
}

