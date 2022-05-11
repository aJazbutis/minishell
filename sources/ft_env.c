/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 20:50:26 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/05/07 18:41:43 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_data *sh)
{
	t_env_lst	*p;

	p = sh->env;
	while (p)
	{
		if (!p->unset && !p->not_exp)
		{
			ft_putstr_fd(p->var, 1);
			ft_putchar_fd('=', 1);
			ft_putstr_fd(p->val, 1);
			ft_putchar_fd('\n', 1);
		}
		p = p->next;
	}
}
