/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:52:30 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/05/12 21:03:20 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envius.h"
#include "minishell.h"

static t_env_lst	*neu_node(char *str)
{
	char		*s;
	t_env_lst	*neu;	

	neu = malloc(sizeof(t_env_lst));
	if (!neu)
		return (NULL);
	ft_memset(neu, 0, sizeof(neu));
	s = ft_strchr(str, '=');
	neu->var = ft_substr(str, 0, s - str);
	if (!(neu->var))
	{
		free(neu);
		perror("Malloc kaputt");
		return (NULL);
	}
	neu->val = ft_substr(s + 1, 0, ft_strlen(s + 1));
	if (!(neu->val))
	{
		ft_clean_env(&neu);
		perror("Malloc kaputt");
		return (NULL);
	}
	return (neu);
}

static void	ft_enlist(t_env_lst **env, t_env_lst *neu)
{
	t_env_lst	*current;

	if (!(*env))
		*env = neu;
	else
	{
		current = *env;
		while (current->next)
			current = current->next;
		current->next = neu;
	}
}

int	ft_list_env(t_env_lst **env)
{
	extern char		**environ;
	int				i;
	t_env_lst		*tmp;

	i = -1;
	while (environ[++i])	
	{
//printf("%s\n", environ[i]);
		tmp = neu_node(environ[i]);
		if (tmp)
			ft_enlist(env, tmp);
		else
		{
			ft_clean_env(env);
			return (1);
		}
	}
	return (0);
}

void	ft_clean_env(t_env_lst	**env)
{
	t_env_lst	*current;
	t_env_lst	*tmp;

	current = *env;
	while (current)
	{
		tmp = current;
		current = current->next;
		if (tmp->var)
			free(tmp->var);
		if (tmp->val)
			free(tmp->val);
		free(tmp);
	}
	*env = NULL;
}
static int	ft_env_size(t_data *sh)
{	
	t_env_lst		*current;
	unsigned int	i;

	i = 0;
	current = sh->env;
	while (current)
	{
		if (!current->unset && !current->not_exp)
			i++;
		current = current->next;
	}
	return (i);
}

char	**env_tab(t_data *sh)
{
	int			i;
	char		*s1;
	t_env_lst	*current;
	char		**env;

	i = ft_env_size(sh);
	if (!i)
		return (NULL);
	env = ft_calloc((i + 1), sizeof(char *));
	if (!env)
	{
		perror("system malfunction");
		exit(errno);//cleanup
	}
	current = sh->env;
	i = -1;
	while (current)
	{

		if (!current->unset && !current->not_exp)
		{
//			write(1, current->var, ft_strlen(current->var));

//			printf("%s\n", current->var);
			s1 = ft_strjoin(current->var, "=");
			if (!s1)
			{
				perror("system malfunction");
				exit(errno);//cleanup
			}
			env[++i] = ft_strjoin(s1, current->val);
			free(s1);
			if (!env[i])
			{
				perror("system malfunction");
				ft_free_tab(env);
				exit(errno);////cleanup;
			}
		}
		current = current->next;
	}
	return (env);
}

	


	

