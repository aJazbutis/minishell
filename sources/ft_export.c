/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 21:30:28 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/05/21 22:06:00 by ajazbuti         ###   ########.fr       */
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
		return (NULL);
	}
	ft_memset(neu, 0, sizeof(*neu));
	neu->var = s[0];
	neu->val = s[1];
	return (neu);
}

static void	ft_enlist(t_data *sh, char *var)
{
	t_env_lst	*current;
//	t_env_lst	*neu;
	char		*eq;
	char		*cut[2];

	eq = ft_strchr(var, '=');
	if (eq)
	{
		cut[0] = ft_substr(var, 0, eq - var);
		//error//perror//
		cut[1] = ft_substr(eq + 1 , 0 , ft_strlen(eq + 1));
		//error perror//
		current = ft_get_env_var(sh, cut[0]);
		if (current)
		{
			current->unset = 0;
			current->not_exp = 0;
			if (current->val)
				free(current->val);
			current->val = cut[1];
			free(cut[0]);
		}
		else
		{
//			neu = neu_node(cut);
			current = sh->env;
			while (current->next)
				current = current->next;
			current->next = neu_node(cut);
		}
	}
	else
	{
		current = ft_get_env_var(sh, var);
		if (current)
		{
			current->unset = 0;
			current->not_exp = 0;
		}
		else
		{
			cut[0] = ft_strdup(var);
			cut[1] = NULL;
			current = sh->env;
			while (current->next)
				current = current->next;
			current->next = neu_node(cut);
		}
	}
}

static char	**ft_sort_char_tab(char **tab)
{
	char	*tmp;
	int		i;
	int		j;

	j = -1;
	while (tab[++j])
	{

	i = 0;
	while (tab[i + 1])
	{
		if (ft_strncmp(tab[i], tab[i + 1], ft_strlen(tab[i])) > 0)
		{
			tmp = tab[i];
			tab[i] = tab[i + 1];
			tab[i + 1] = tmp;
		}
		i++;
	}
	}
	return (tab);
}

void	ft_export(t_data *sh, char **cmd)
{
	char	**printout;
	int		i;

	ft_underscore(sh, cmd);
	if (!cmd[1])
	{
		printout = env_tab(sh, 1);
		if (!printout)
			perror("system malfunction");
		else
		{
			printout = ft_sort_char_tab(printout);
			i = -1;
			while (printout[++i])
			{
				if (printout[i][0] == '_' && printout[i][1] == '=')//strncmp?
					continue ;
				ft_putstr_fd(printout[i], 1);
				ft_putchar_fd('\n', 1);
			}
			ft_free_tab(printout);
		}
	}
	else
	{
		i = 0;
		while (cmd[++i])
			ft_enlist(sh, cmd[i]);
	}
}
