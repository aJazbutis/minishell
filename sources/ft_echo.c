/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 21:18:50 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/06/12 15:29:14 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_nl(unsigned int *nl, unsigned int *i, char **cmd)
{
	unsigned int	j;

	*nl = 1;
	*i = 1;
	while (cmd[*i])
	{
		j = 1;
		if (cmd[*i][0] == '-')
		{
			if (!(cmd[*i][j] == 'n'))
				break ;
			while (cmd[*i][j] == 'n')
				j++;
		}
		else
			break ;
		if (cmd[*i][j])
			break ;
		(*i)++;
		*nl = 0;
	}
}

int	ft_echo(t_data *sh, char **cmd)
{
	unsigned int	nl;
	unsigned int	i;

	ft_nl(&nl, &i, cmd);
	sh->status = 0;
	ft_underscore(sh, cmd);
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		i++;
		if (cmd[i])
			ft_putchar_fd(' ', 1);
	}
	if (nl)
		ft_putchar_fd('\n', 1);
	return (0);
}
