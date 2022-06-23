/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorunov <kmorunov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 12:20:53 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/06/20 21:27:10 by kmorunov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_backup_fds(t_data *sh)
{
	errno = 0;
	sh->st_fd[0] = dup(0);
	sh->st_fd[1] = dup(1);
	return (errno);
}

int	ft_restore_fds(t_data *sh)
{
	errno = 0;
	dup2(sh->st_fd[0], 0);
	dup2(sh->st_fd[1], 1);
	return (errno);
}
