/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 21:58:18 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/06/13 22:11:14 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exp_print(t_data *sh)
{
	int		i;
	char	**prnt;

	prnt = env_tab_exp(sh);
	if (prnt)
	{
		prnt = ft_sort_tab(prnt);
		i = -1;
		while (prnt[++i])
		{
			if ((prnt[i][0] == '_' && prnt[i][1] == '=') &&
				ft_strncmp(&prnt[i][3], sh->location, ft_strlen(sh->location)))
				continue ;
			ft_putstr_fd(prnt[i], 1);
			ft_putchar_fd('\n', 1);
		}
		ft_free_tab(prnt);
	}
}
