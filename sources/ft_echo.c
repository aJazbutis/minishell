/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 21:18:50 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/05/14 19:25:44 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_data *sh)
{
	unsigned int	nl;
	unsigned int	i;
	char			*val;
//	t_env_lst		*tmp;

	nl = 1;
	i = 1;
	printf("*\n");
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
	printf("**\n");
	while (sh->cmd[i])
	{
		val = ft_getenv(sh, sh->cmd[i]);
		if (val)
		{
			ft_putstr_fd(val, 1);
			free(val);
		}
		else
			ft_putstr_fd(sh->cmd[i], 1);
		i++;
		if (sh->cmd[i])
			ft_putchar_fd(' ', 1);
	}
	if (nl)
		ft_putchar_fd('\n', 1);
	return (0);
}
