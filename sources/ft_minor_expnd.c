/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minor_expnd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 20:27:40 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/06/20 20:32:22 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_not_just_whitespace(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (!(s[i] == 32 || (s[i] > 7 && s[i] < 15)))
			return (1);
	}
	return (0);
}

static int	ft_minor_chck(t_cmd *cmd)
{
	if (ft_strchr(cmd->cmd[0], ' ') && !cmd->cmd[1]
		&& ft_not_just_whitespace(cmd->cmd[0])
		&& !ft_strchr(cmd->cmd[0], '>')
		&& !ft_strchr(cmd->cmd[0], '<')
		&& !ft_strchr(cmd->cmd[0], '|')
		&& !ft_strchr(cmd->cmd[0], '=')
		&& !ft_strchr(cmd->cmd[0], ';'))
		return (1);
	return (0);
}

void	ft_minor_expnd(t_data *sh)
{
	t_cmd	*cmd;
	char	**tmp;

	cmd = sh->cmd;
	while (cmd)
	{
		if (cmd->cmd)
		{
			if (ft_minor_chck(cmd))
			{
				tmp = ft_split(cmd->cmd[0], ' ');
				if (!ft_malloc_error(sh, tmp))
				{
					ft_free_tab(cmd->cmd);
					cmd->cmd = tmp;
				}
			}
		}
		cmd = cmd->next;
	}
}
