/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 20:15:49 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/05/12 21:39:08 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(t_data *sh, char *s)
{
	t_env_lst	*current;
	char		*ret;

	ret = NULL;
	current = sh->env;
	while (current)
	{
		if (!ft_strncmp(s, current->var, ft_strlen(current->var)) && !current->unset)
		{
			ret = ft_strdup(current->val);
			if (!ret)
				perror("system malfunction");
			return (ret);
		}
		current = current->next;
	}
	return (NULL);
}

t_env_lst *ft_get_env_var(t_data *sh, char *s)
{
	t_env_lst	*current;

	current = sh->env;
	while (current)
	{
		if (!ft_strncmp(s, current->var, ft_strlen(current->var)))
			return (current);
		current = current->next;
	}
	return (NULL);
}

static void	ft_unset_node(t_env_lst *node)
{
	if (!node)
		return ;
//	if (node->var)
//		free(node->var);
//	node->var = NULL;
	if (node->val)
		free(node->val);
	node->val = NULL;
	node->unset = 1;
//	free(node);
//	node = NULL;
}

void	ft_unset(t_data *sh)
{
	t_env_lst	*current;
	t_env_lst	*tmp;

	ft_underscore(sh);
	current = sh->env;
	if (!ft_strncmp(sh->cmd[1], sh->env->var, ft_strlen(sh->cmd[1])))
	{
		tmp = sh->env;
//		sh->env = sh->env->next;
		ft_unset_node(tmp);
	}
	else
	{
		while (current->next)
		{
			if (!ft_strncmp(sh->cmd[1], current->next->var, ft_strlen(sh->cmd[1])))
			{
				tmp = current->next;
//				current->next = current->next->next;
				ft_unset_node(tmp);
//				continue ;
			}
			current = current->next;
		}
	}
	g_status = 0;
}
