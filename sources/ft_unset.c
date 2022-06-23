/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorunov <kmorunov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 21:00:03 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/06/19 21:43:25 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_not_ok(char	*name)
{
	int	i;

	if (!name)
		return (0);
	i = 0;
	if (!ft_isalpha(name[i]) && !(name[i] == '_'))
		return (1);
	while (name[++i])
	{
		if (!ft_isalnum(name[i]) && !(name[i] == '_'))
			return (1);
	}
	return (0);
}

/*node->not_exp = 1;*/

static void	ft_unset_node(t_env_lst *node)
{
	if (node->val)
		free(node->val);
	node->val = NULL;
	node->unset = 1;
}

void	ft_unset(t_data *sh, char **cmd)
{
	t_env_lst	*tmp;
	int			i;

	i = 0;
	ft_underscore(sh, cmd);
	while (cmd[++i])
	{
		if (ft_not_ok(cmd[i]))
		{
			sh->status = 1;
			ft_putstr_fd("\033[1;35m<( ^.^ )>\033[1;0m\033[0m: unset: '", 2);
			ft_putstr_fd(cmd[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			continue ;
		}
		tmp = ft_get_env_var(sh, cmd[i]);
		if (tmp)
			ft_unset_node(tmp);
	}
}
