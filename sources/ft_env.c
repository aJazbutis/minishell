/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorunov <kmorunov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 20:50:26 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/06/20 20:53:16 by kmorunov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_printout(t_env_lst *p)
{
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

void	ft_env(t_data *sh)
{
	t_env_lst	*p;

	sh->status = 0;
	p = ft_get_env_var(sh, "_");
	if (!p->unset)
	{
		if (p->val)
			free(p->val);
		p->val = ft_strjoin(sh->location, "->ft_env");
		ft_malloc_error(sh, p->val);
	}
	ft_printout(sh->env);
	p = ft_get_env_var(sh, "_");
	if (!p->unset)
	{
		if (p->val)
			free(p->val);
		p->val = ft_strdup("env");
		ft_malloc_error(sh, p->val);
	}
}
