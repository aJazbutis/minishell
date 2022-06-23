/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorunov <kmorunov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 20:15:49 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/06/21 16:09:51 by ajazbuti         ###   ########.fr       */
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
		if (!ft_strncmp(s, current->var, ft_strlen(current->var) + 1)
			&& !current->unset)
		{
			if (current->val)
			{
				ret = ft_strdup(current->val);
				if (!ret)
					perror("system malfunction");
				return (ret);
			}
		}
		current = current->next;
	}
	return (NULL);
}

t_env_lst	*ft_get_env_var(t_data *sh, char *s)
{
	t_env_lst	*current;

	current = sh->env;
	while (current)
	{
		if (!ft_strncmp(s, current->var, ft_strlen(current->var) + 1))
			return (current);
		current = current->next;
	}
	return (NULL);
}
