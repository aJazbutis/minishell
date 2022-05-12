/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 21:18:50 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/05/12 21:44:53 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_data *sh)
{
	unsigned int	nl;
	unsigned int	i;
//	t_env_lst		*tmp;

	nl = 1;
	i = 1;
	if (!ft_strncmp("-n", sh->cmd[1], ft_strlen(sh->cmd[1])))
	{
		i = 2;
		nl = 0;
	}
/*	tmp = ft_get_env_var(sh, "_");
	if (!tmp->unset)
	{
		if (tmp->val)
			free(tmp->val);
		while (sh->cmd[i + 1])
			i++;
		tmp->val = ft_strdup(sh->cmd[i]);
		if (!tmp->val)
			perror("system malfunction");
	}*/
	while (sh->cmd[i])
	{
		ft_putstr_fd(sh->cmd[i], 1);
		i++;
		if (sh->cmd[i])
			ft_putchar_fd(' ', 1);
	}
	if (nl)
		ft_putchar_fd('\n', 1);
	return (0);
}
