/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorunov <kmorunov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 16:34:29 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/06/21 21:03:48 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_dup2_dup2(int inpt, int outpt)
{
	dup2(inpt, 0);
	dup2(outpt, 1);
}

int	ft_redir_out(t_data *sh, t_cmd *cmd, int out_fd)
{
	int		fd;
	t_flst	*out;

	out = NULL;
	out = cmd->out;
	while (out)
	{
		if (out->nbr[0])
			fd = open(out->str, O_CREAT | O_APPEND | O_WRONLY, 0644);
		else
			fd = open(out->str, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (fd < 0)
		{
			ft_mini_perror(sh, out->str);
			return (fd);
		}
		out = out->next;
		if (!out)
			return (fd);
		close(fd);
	}
	return (out_fd);
}

static int	ft_in_fd(t_cmd *cmd, t_flst *in)
{
	if (!ft_strncmp("heredoc", in->str, 8))
		return (dup(cmd->here_fd));
	else
		return (open(in->str, O_RDONLY));
}

int	ft_redir_in(t_data *sh, t_cmd *cmd, int in_fd)
{
	int		fd;
	t_flst	*in;

	in = cmd->in;
	while (in)
	{
		fd = ft_in_fd(cmd, in);
		if (fd < 0)
		{
			ft_mini_perror(sh, in->str);
			return (fd);
		}
		in = in->next;
		if (!in)
			return (fd);
		close(fd);
	}
	return (in_fd);
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
