/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 21:30:28 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/06/21 17:00:38 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env_lst	*neu_node(t_data *sh, char **s)
{
	t_env_lst	*neu;	

	neu = malloc(sizeof(t_env_lst));
	if (ft_malloc_error(sh, neu))
		return (NULL);
	ft_memset(neu, 0, sizeof(*neu));
	neu->var = s[0];
	neu->val = s[1];
	return (neu);
}

static void	ft_add_more(t_data *sh, char **cut, char *eq)
{
	t_env_lst	*current;

	current = ft_get_env_var(sh, cut[0]);
	if (current)
	{
		current->unset = 0;
		current->not_exp = 0;
		if (eq)
		{
			if (current->val)
				free(current->val);
			current->val = cut[1];
		}
		free(cut[0]);
	}
	else
		ft_enlist(&sh->env, neu_node(sh, cut));
}

static void	ft_add(t_data *sh, char *var)
{
	char		*cut[2];
	char		*eq;

	eq = ft_strchr(var, '=');
	if (eq)
	{
		cut[0] = ft_substr(var, 0, eq - var);
		if (ft_malloc_error(sh, cut[0]))
			return ;
		cut[1] = ft_substr(eq + 1, 0, ft_strlen(eq + 1));
		if (ft_malloc_error(sh, cut[1]))
		{
			free(cut[0]);
			return ;
		}
	}
	else
	{
		cut[0] = ft_strdup(var);
		if (ft_malloc_error(sh, cut[0]))
			return ;
		cut[1] = NULL;
	}
	ft_add_more(sh, cut, eq);
}

static int	ft_not_ok(char *cmd)
{
	int		j;
	char	lim;

	j = 0;
	lim = '\0';
	if (ft_strchr(cmd, '='))
		lim = '=';
	if (!ft_isalpha(cmd[j]) && !(cmd[j] == '_'))
		return (1);
	j++;
	while (cmd[j] != lim)
	{
		if (!ft_isalnum(cmd[j]) && !(cmd[j] == '_'))
			return (1);
		j++;
	}
	return (0);
}

void	ft_export(t_data *sh, char **cmd)
{
	int		i;

	if (!cmd[1])
		ft_exp_print(sh);
	else
	{
		i = 0;
		while (cmd[++i])
		{
			if (ft_not_ok(cmd[i]))
			{
				sh->status = 1;
				ft_putstr_fd("<( ^.^ )>: export: '", 2);
				ft_putstr_fd(cmd[i], 2);
				ft_putstr_fd("': not a valid identifier\n", 2);
				continue ;
			}
			ft_add(sh, cmd[i]);
		}
	}
	ft_underscore(sh, cmd);
}
