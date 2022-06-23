/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_to_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorunov <kmorunov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:18:03 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/06/19 21:44:21 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_combine_str(t_data *sh, t_env_lst *env)
{
	char		*s[2];

	ft_memset(s, 0, sizeof(s));
	s[0] = ft_strjoin(env->var, "=");
	if (ft_malloc_error(sh, s[0]))
		return (NULL);
	s[1] = ft_strjoin(s[0], env->val);
	free(s[0]);
	if (ft_malloc_error(sh, s[1]))
		return (NULL);
	return (s[1]);
}

/*For line 45 - !current->unset && */

char	**env_tab(t_data *sh)
{
	int			i;
	t_env_lst	*current;
	char		**env;

	i = ft_env_size(sh->env);
	env = ft_calloc((i + 1), sizeof(char *));
	if (ft_malloc_error(sh, env))
		return (NULL);
	current = sh->env;
	i = -1;
	while (current)
	{
		if (!current->not_exp && current->val)
		{
			env[++i] = ft_combine_str(sh, current);
			if (!env[i])
			{
				ft_free_tab(env);
				return (NULL);
			}
		}
		current = current->next;
	}
	return (env);
}

static char	*ft_qq_str(t_data *sh, char *s)
{
	char	*s1;

	if (!s)
	{
		s1 = ft_strdup("\"\"");
		ft_malloc_error(sh, s1);
		return (s1);
	}
	else
	{
		s1 = ft_strjoin("\"", s);
		ft_malloc_error(sh, s1);
		s = ft_strjoin(s1, "\"");
		ft_malloc_error(sh, s);
		free(s1);
		return (s);
	}
}

static char	*ft_combine_qq_str(t_data *sh, t_env_lst *env)
{
	char	*s[3];

	if (!env->val)
	{
		s[0] = ft_strdup(env->var);
		ft_malloc_error(sh, s[0]);
		return (s[0]);
	}
	ft_memset(s, 0, sizeof(*s[3]));
	s[0] = ft_strjoin(env->var, "=");
	if (ft_malloc_error(sh, s[0]))
		return (NULL);
	s[1] = ft_qq_str(sh, env->val);
	if (ft_malloc_error(sh, s[1]))
	{
		free(s[0]);
		return (NULL);
	}
	s[2] = ft_strjoin(s[0], s[1]);
	free(s[0]);
	free(s[1]);
	ft_malloc_error(sh, s[2]);
	return (s[2]);
}

char	**env_tab_exp(t_data *sh)
{
	int			i;
	t_env_lst	*current;
	char		**env;

	i = ft_env_size(sh->env);
	env = ft_calloc((i + 1), sizeof(char *));
	if (ft_malloc_error(sh, env))
		return (NULL);
	current = sh->env;
	i = -1;
	while (current)
	{
		if (!current->unset && !current->not_exp)
		{
			env[++i] = ft_combine_qq_str(sh, current);
			if (!env[i])
			{
				ft_free_tab(env);
				return (NULL);
			}
		}
		current = current->next;
	}
	return (env);
}
