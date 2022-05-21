/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 17:54:53 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/05/17 16:21:42 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_here_rewrite(t_data *sh, t_list	*lst)
{
	t_list	*tmp;
	
	tmp = lst;
	while (tmp)
	{
		ft_putstr_fd((char *)tmp->content, sh->pp1[3]);
		ft_putchar_fd('\n', sh->pp1[3]);
		printf("%s", tmp->val);
		tmp = tmp->next;
	}
	close(sh->pp1[3]);
	ft_clearlst(lst);
}

static int	ft_here_pipes(t_data *sh)
{
	errno = 0;
	if (pipe(sh->pp1))
	{
		perror("pipe kaputt");
		g_status = errno;
		return (errno);
	}
	if (pipe(sh->pp1 + 2))
	{
		perror("pipe kaputt");
		close(sh->pp1[0]);
		g_status = errno;
		return (errno);
	}
	return (errno);
}

static void	ft_temp_expand(t_data *sh)
{
	char	*line;
	char	*line_nonl;
	t_list	*lst;

	lst = NULL;
	line = get_next_line(sh->pp1[0]);
	while (line)
	{
		line_nonl = ft_substr(line, 0, ft_strlen(line) - 1);
		if (!line_nonl)
			perror("system malfunction");
		ft_lstadd_back(&lst, ft_lstnew(line_nonl));
		free(line);
		line = get_next_line(sh->pp1[0]);
	}
	close(sh->pp1[0]);
	ft_here_rewrite(sh, lst);
}

static void	ft_here_write(t_data *sh)
{
	char	*line;

	ft_putstr_fd("heredoc> ", 1);//2?);
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

int		ft_here_doc(t_data *sh)
{
	errno = 0;
	sh->here_doc = 1;
	if (ft_here_pipes(sh))
	{
		perror(errno);
		return (errno);
	}	
	ft_here_write(sh);
	ft_temp_expand(sh);
	//ft_expand
}
