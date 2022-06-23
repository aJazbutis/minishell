/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorunov <kmorunov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:52:30 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/06/19 21:44:59 by ajazbuti         ###   ########.fr       */
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
	ft_memset(neu, 0, sizeof(*neu));
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

void	ft_enlist(t_env_lst **env, t_env_lst *neu)
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

int	ft_list_env(t_env_lst **env, char **environ)
{
	int				i;
	t_env_lst		*tmp;

	i = -1;
	while (environ[++i])
	{
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

int	ft_env_size(t_env_lst *env)
{	
	unsigned int	i;

	i = 0;
	while (env)
	{
		if (!env->unset && !env->not_exp)
			i++;
		env = env->next;
	}
	return (i);
}
