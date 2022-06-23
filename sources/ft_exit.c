/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:56:45 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/06/19 20:50:46 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_data *sh, char **cmd)
{
	long long	ret;

	ret = 0;
	if (cmd[1])
		ret = ft_atoll(cmd[1]);
	ft_clean_sh(sh);
	ft_putstr_fd("exit\n", 2);
	exit(ret);
}

int	ft_status(t_data *sh)
{
	if (WIFSIGNALED(sh->status))
	{
		sh->status = WTERMSIG(sh->status) + 128;
		return (1);
	}
	else if (WIFEXITED(sh->status))
		sh->status = WEXITSTATUS(sh->status);
	return (0);
}
