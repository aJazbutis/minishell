/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_executable.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 13:54:13 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/05/20 22:56:49 by ajazbuti         ###   ########.fr       */
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

void	ft_pathproofargs(/*t_data *sh, */char **cmd)
{
	char	*s;
	int		i;

	i = 0;
	while (cmd[++i])
	{
		if (*cmd[i] == '~')
		{
			cmd[i]++;
			s = ft_strjoin(getenv("HOME"), cmd[i]);
			if (!s)
				perror("system malfunction");
			cmd[i]--;
			free(cmd[i]);
			cmd[i] = s;
		}
	}
}

void	ft_exec_exe(t_data *sh, char **cmd)
{
	char	**envp;
	char	*pth;

	pth = ft_safe_path(cmd[0]);
	if (!pth)
		exit(errno);
	if (access(pth, X_OK))
	{
		perror(cmd[0]);
		free(pth);
//		g_status = errno;
		exit(errno);
	}
	envp = env_tab(sh, 0);
	if (!envp)
	{
		perror ("system malfunction");//maybe alreadyperror 
		free(pth);
//		g_status = errno;
		exit(errno);
	}
	ft_pathproofargs(cmd);
//	printf("%s\n", sh->cmd[1]);
	if (execve(pth, cmd, envp) == -1)
	{
		perror("executable not executed");
//		sh->status = errno;
		free(pth);
		ft_free_tab(envp);
		//clean strct
		exit(errno);
	}
}
/*
//add while and pipes
void	ft_execute_executable(t_data *sh, char **cmd)
{
	pid_t		id;
	t_env_lst	*tmp;
	int			i;

	id = fork();
	if (id == -1)
	{
		perror("fork kaputt");
//		g_status = errno;
		return ; //exit
	}
	if (id)
	{
		tmp = ft_get_env_var(sh, "_");
		if (!tmp->unset)
		{
			if (tmp->val)
				free(tmp->val);
			if (!sh->pp_nbr)
			{
				i = 0;
				while (cmd[i + 1])
					i++;
				tmp->val = ft_strdup(cmd[i]);
				if (!tmp->val)
					perror("system malfunction");
			}
			else
				tmp->val = NULL;
		}
	}
	if (!id)
		ft_exec_executable(sh, cmd);
	waitpid(id, &sh->status, 0);
}
*/
