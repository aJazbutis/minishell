/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorunov <kmorunov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 18:59:23 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/06/20 20:59:22 by kmorunov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_underscore(t_data *sh, char **cmd)
{
	t_env_lst	*tmp;
	int			j;

	tmp = ft_get_env_var(sh, "_");
	if (!tmp->unset)
	{
		if (tmp->val)
			free(tmp->val);
		j = 0;
		if (cmd)
		{
			if (cmd[j])
			{
				while (cmd[j + 1])
					j++;
				tmp->val = ft_strdup(cmd[j]);
				ft_malloc_error(sh, tmp->val);
			}
		}
		else
			tmp->val = NULL;
	}
}

void	ft_pre_exec_env(t_data *sh, char *cmd)
{
	t_env_lst	*tmp;

	tmp = ft_get_env_var(sh, "_");
	tmp->unset = 0;
	if (tmp->val)
		free(tmp->val);
	tmp->val = ft_strdup(cmd);
	ft_malloc_error(sh, tmp->val);
}
