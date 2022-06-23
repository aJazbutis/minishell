/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 20:08:13 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/06/06 21:38:39 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_data *sh, char **cmd)
{
	char		msg[256];

	ft_underscore(sh, cmd);
	if (!getcwd(msg, sizeof(msg)))
	{
		perror("minishell: pwd:");
		sh->status = errno;
	}
	else
	{
		ft_putstr_fd(msg, 1);
		write(1, "\n", 1);
		sh->status = 0;
	}
}
