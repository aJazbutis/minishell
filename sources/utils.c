/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorunov <kmorunov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 19:26:50 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/06/20 20:35:26 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_mini_perror(t_data *sh, char *s)
{
	sh->status = errno;
	ft_putstr_fd("\033[1;35m<( ^.^ )>: \033[1;0m\033[0m", 2);
	perror(s);
}

int	ft_malloc_error(t_data *sh, void *s)
{
	if (!s)
	{
		perror("system malfunction");
		sh->status = errno;
		return (1);
	}
	return (0);
}

void	ft_location(t_data *sh)
{
	char		*s[3];
	t_env_lst	*tmp;

	tmp = ft_get_env_var(sh, "_");
	if (tmp && tmp->val)
	{
		s[0] = ft_strnstr(tmp->val, "./minishell", ft_strlen(tmp->val));
		if (s[0])
		{
			s[1] = ft_substr(tmp->val, 0, s[0] - tmp->val);
			if (ft_malloc_error(sh, s[1]))
				return ;
			s[2] = ft_strjoin(s[1], "minishell");
			free(s[1]);
			if (ft_malloc_error(sh, s[2]))
				return ;
			free(tmp->val);
			tmp->val = s[2];
		}
	}
}
