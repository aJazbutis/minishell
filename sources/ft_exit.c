/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:56:45 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/05/20 19:14:18 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_data *sh, char **cmd)
{
	long long	ret;

	if (!sh)//error prev
		return ;
	ret = 0;
	if (cmd[1])
		ret = ft_atoll(cmd[1]);
	//cleen free
	ft_putstr_fd("exit\n", 2);
	exit(ret);
}


