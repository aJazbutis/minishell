/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 20:50:26 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/05/21 19:38:27 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_data *sh)
{
	t_env_lst	*p;

	p = ft_get_env_var(sh, "_");
	if (!p->unset)
	{
		if (p->val)
			free(p->val);
		p->val = ft_strdup("somewhere/minishell/ft_env");
		if (!p->val)
			perror("system malfunction");
	}
	p = sh->env;
	while (p)
	{
		if (!p->unset && !p->not_exp && p->val)
		{
			ft_putstr_fd(p->var, 1);
			ft_putchar_fd('=', 1);
			ft_putstr_fd(p->val, 1);
			ft_putchar_fd('\n', 1);
		}
		p = p->next;
	}
}
