/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 18:44:23 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/06/21 17:00:16 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env_lst	*neu_node(char **s)
{
	t_env_lst	*neu;	

	neu = malloc(sizeof(t_env_lst));
	if (!neu)
	{
		perror("system malfunction");
		free(s[0]);
		free(s[1]);
		return (NULL);
	}
	ft_memset(neu, 0, sizeof(*neu));
	neu->not_exp = 1;
	neu->var = s[0];
	neu->val = s[1];
	return (neu);
}

static void	ft_add(t_data *sh, char **s)
{
	t_env_lst	*current;

	current = ft_get_env_var(sh, s[0]);
	if (current)
	{
		current->unset = 0;
		if (current->val)
			free(current->val);
		current->val = s[1];
		free(s[0]);
	}
	else
		ft_enlist(&sh->env, neu_node(s));
}

static int	ft_check_var(char **cmd)
{
	int		i;
	int		j;

	i = -1;
	while (cmd[++i])
	{
		if (!ft_strchr(cmd[i], '='))
			return (i);
		j = 0;
		if (!ft_isalpha(cmd[i][j]) && !(cmd[i][j] == '_'))
			return (i);
		j++;
		while (cmd[i][j] != '=')
		{
			if (!ft_isalnum(cmd[i][j]) && !(cmd[i][j] == '_'))
				return (i);
			j++;
		}
	}
	return (-1);
}

static void	ft_mod_cmd(t_data *sh, int i)
{
	char	**copy;
	int		j;

	j = 0;
	while (sh->cmd->cmd[i + j])
		j++;
	copy = ft_calloc(sizeof(char *), j + 1);
	if (ft_malloc_error(sh, copy))
		return ;
	j = 0;
	while (sh->cmd->cmd[i + j])
	{
		copy[j] = ft_strdup(sh->cmd->cmd[i + j]);
		if (ft_malloc_error(sh, copy[j]))
			ft_free_tab(copy);
		j++;
	}
	i = -1;
	ft_free_tab(sh->cmd->cmd);
	sh->cmd->cmd = copy;
	ft_what_to_do(sh, sh->cmd->cmd);
}

void	ft_add_env_var(t_data *sh, char **cmd)
{
	char	*cut[2];
	int		i;

	i = ft_check_var(cmd);
	if (i > -1)
		ft_mod_cmd(sh, i);
	else
	{
		i = -1;
		while (cmd[++i])
		{
			cut[1] = ft_strchr(cmd[i], '=');
			cut[0] = ft_substr(cmd[i], 0, cut[1] - cmd[i]);
			if (ft_malloc_error(sh, cut[0]))
				return ;
			cut[1] = ft_substr(cut[1] + 1, 0, ft_strlen(cut[1] + 1));
			if (ft_malloc_error(sh, cut[1]))
			{
				free(cut[0]);
				return ;
			}
			ft_add(sh, cut);
		}
	}
}
