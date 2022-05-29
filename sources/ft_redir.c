/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 16:34:29 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/05/29 18:53:32 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_redir_out(t_flst *out) 
{
	int	fd;

	while (out)
	{
		if (out->append)
			fd = open(out->file, O_CREAT | O_APPEND | O_WRONLY, 0644);
		else
			fd = open(out->file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (fd < 0)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(out->file);
			return (fd);
		}
		out = out->next;
		if (!out)
			return (fd);
		close(fd);
	}
	return (1);
}

int	ft_redir_in(t_flst *in)
{
	int	fd;

	while (in)
	{
	//	if (in->append)
	//		fd = open(out->file, O_CREAT | O_APPEND | O_WRONLY, 0644);
	//	HEREDoC????
	//	else
			fd = open(in->file, O_RDONLY);
		if (fd < 0)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(in->file);
			return (fd);
		}
		in = in->next;
		if (!in)
			return (fd);
		close(fd);
	}
	return (0);
}

/*int ft_redir_err(t_flst *err) 
{
	int	fd;

	while (err)
	{
		if (err->append)
			fd = open(err->file, O_CREAT | O_APPEND | O_WRONLY, 0644);
		else
			fd = open(err->file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (fd < 0)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(err->file);
			return (fd);
		}
		err = err->next;
		if (!err)
			return (fd);
		close(fd);
	}
	return (2);
}*/
