/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 18:44:23 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/05/21 22:13:48 by ajazbuti         ###   ########.fr       */
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
	ft_memset(neu, 0, sizeof(neu));
	neu->not_exp = 1;
	neu->var = s[0];
//	if (!(neu->var))
//	{
//		free(neu);
//		perror("Malloc kaputt");
//		return (NULL);
//	}
	neu->val = s[1];
//	if (!(neu->val))
//	{
//		free(neu->var);
//		free(neu);
//		perror("Malloc kaputt");
//		return (NULL);
//	}
	return (neu);
}

static void	ft_enlist(t_data *sh, char **s)
{
	t_env_lst	*current;
	t_env_lst	*neu;

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
	{
		neu = neu_node(s);
		current = sh->env;
		while (current->next)
			current = current->next;
		current->next = neu;
	}
}

void	ft_add_env_var(t_data *sh, char **cmd)
{
	char	*cut[2];
	char	*eq;
	int		i;

	i = -1;
	while (cmd[++i])
	{
		eq = ft_strchr(cmd[i], '=');
		if (!eq)
		{
			ft_putstr_fd(cmd[i], 2);
			ft_putstr_fd(": must be sent to pipes and kids\n", 2);
//			ft_exec(sh, &cmd[i]);
			return ;
		}
	}
	i = -1;
	while (cmd[++i])
	{

printf("%s\n", cmd[i]);
		cut[0] = ft_substr(cmd[i], 0, eq - cmd[i]);
	printf("%s\n", cut[0]);
		if (!cut[0])
		{
			perror("system malfunction");
	//		return ;
		}
		cut[1] = ft_substr(eq + 1, 0, ft_strlen(eq + 1));
printf("%s\n", cut[1]);
		if (!cut[1])
		{
//			if (cut[0])
//				free(cut[0]);
		perror("system malfunction");
//		return ;
		}
		ft_enlist(sh, cut);
	}
}
