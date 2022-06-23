/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_exp_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorunov <kmorunov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 22:50:04 by kmorunov          #+#    #+#             */
/*   Updated: 2022/06/22 22:54:06 by kmorunov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*do_here_exp(char *line, char *dollar, t_data *sh, int position)
{
	char	*before;
	char	*after;
	char	*buff;
	char	*buff2;
	int		length;

	length = var_len(dollar + 1);
	dollar = ft_substr(dollar, 1, length);
	if (dollar[0] == '?')
		buff = ft_itoa(sh->status);
	else
		buff = ft_getenv(sh, dollar);
	free(dollar);
	dollar = NULL;
	before = ft_my_substr(line, 0, position);
	after = ft_my_substr(line, position + length + 1,
			ft_strlen(line));
	buff2 = ft_my_string_join(before, buff);
	free(buff);
	free(before);
	dollar = ft_my_string_join(buff2, after);
	free(after);
	free(buff2);
	return (dollar);
}

static char	*do_here_exp_routine(t_data *sh, char *line, char *dollar)
{
	int		length;
	char	*buff;
	int		position;

	buff = NULL;
	length = var_len(dollar + 1);
	position = get_position(line, '$');
	if (length != 0 || dollar[1] == '?')
		buff = do_here_exp(line, dollar, sh, position);
	return (buff);
}

void	ft_here_expand(t_data *sh, char *line, int fd)
{
	char	*dollar;
	char	*buff;

	if (ft_strchr(line, '$'))
	{
		while (ft_strchr(line, '$'))
		{
			buff = NULL;
			dollar = ft_strchr(line, '$');
			if (dollar)
			{
				buff = do_here_exp_routine(sh, line, dollar);
				line = ft_strdup(buff);
				free(buff);
			}
			if (!dollar || var_len(dollar + 1) == 0)
				break ;
		}
		ft_putstr_fd(line, fd);
		free(line);
	}
	else
		ft_putstr_fd(line, fd);
}
