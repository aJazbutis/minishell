/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 17:54:53 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/05/29 21:35:27 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_here_rewrite(t_data *sh, t_list	*lst)
{
	t_list	*tmp;
	
	tmp = lst;
	while (tmp)
	{
		ft_putstr_fd((char *)tmp->content, sh->here_pp[1]);
		ft_putchar_fd('\n', sh->here_pp[1]);
		tmp = tmp->next;
	}
	close(sh->here_pp[1]);
	ft_lstclear(&lst, free);
	sh->here_fd = sh->here_pp[0];
}

/*static int	ft_here_pipes(t_data *sh)
{
	errno = 0;
	if (pipe(sh->pp1))
	{
		perror("pipe kaputt");
		return (errno);//exit
	}
	if (pipe(sh->pp1 + 2))
	{
		perror("pipe kaputt");
		close(sh->pp1[0]);
		return (errno);//exit
	}
	return (errno);
}*/

static void	ft_temp_expand(t_data *sh)
{
	char	*line;
	char	*line_nonl;
	t_list	*lst;

	lst = NULL;
	line = get_next_line(sh->here_fd);
	while (line)
	{
		line_nonl = ft_substr(line, 0, ft_strlen(line) - 1);
		if (!line_nonl)
			perror("system malfunction");
		ft_lstadd_back(&lst, ft_lstnew(line_nonl));
		free(line);
		line = get_next_line(sh->here_fd);
	}
	close(sh->here_fd);
	if (pipe(sh->here_pp))
	{
		perror("pipe kaputt");
		ft_lstclear(&lst, free);
		exit(errno);//cleanup
	}
	ft_here_rewrite(sh, lst);
}

static void	ft_here_write(t_here *here)
{
	char	*line;

	ft_putstr_fd("heredoc> ", 1);//2?);
	line = get_next_line(0);
	while (line)
	{
		if (!ft_strncmp(here->limiter, line, ft_strlen(here->limiter))
			&& ft_strlen(line) - 1 == ft_strlen(here->limiter))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, here->pp[1]);
		free(line);
		ft_putstr_fd("heredoc> ", 1);
		line = get_next_line(0);
	}
	close(here->pp[1]);
}

static void	ft_heredocs(t_data *sh)
{
	t_here	*tmp;

	tmp = sh->heredoc;
	while (tmp)
	{
		if (pipe(tmp->pp))
		{
			perror("pipe kaputt");
			exit(1); //cleanup
		}
		ft_here_write(tmp);
		if (tmp->next)
		{
			close(tmp->pp[0]);
			tmp = tmp->next;
		}
		else
		{
			sh->here_fd = tmp->pp[0];
			return ;
		}
	}
}
		
int		ft_here_doc(t_data *sh)
{
//	errno = 0;
//	sh->here_doc = 1;
//	if (ft_here_pipes(sh))
//	{
//		perror(errno);
//		return (errno);
//	}	
	ft_heredocs(sh);
//	ft_here_write(sh);
	ft_temp_expand(sh);
	//ft_expand
	return (0);
}
