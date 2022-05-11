/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 17:54:53 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/05/09 18:03:00 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_here_doc(t_data *sh)
{
	char	*line;

//	sh->here_doc = 1;
	if (pipe(sh->pp1))
	{
		perror("pipe kaputt");
		exit(errno);
	//	ft_clean_exit("Pipe exploaded during creation", ppx);
	}
	ft_putstr_fd("heredoc> ", 1);
	line = get_next_line(0);
	while (line)
	{
		if (!ft_strncmp(sh->limiter, line, ft_strlen(sh->limiter))
			&& ft_strlen(line) - 1 == ft_strlen(sh->limiter))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, sh->pp1[1]);
		free(line);
		ft_putstr_fd("heredoc> ", 1);
		line = get_next_line(0);
	}
	close(sh->pp1[1]);
}
