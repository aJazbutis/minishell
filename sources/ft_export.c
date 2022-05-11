/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 21:30:28 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/05/10 16:27:02 by ajazbuti         ###   ########.fr       */
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
	ft_memset(neu, 0, sizeof(neu));
	neu->var = ft_strdup(s[0]);
	if (!(neu->var))
	{
		free(neu);
		perror("Malloc kaputt");
		return (NULL);
	}
	if (s[1])
	neu->val = ft_strdup(s[1]);
	if (!(neu->val))
	{
		ft_clean_env(&neu);
		perror("Malloc kaputt");
		return (NULL);
	}
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
		current->not_exp = 0;
	}
	else if (s[0] && s[1])
	{
		neu = neu_node(s);
		current = sh->env;
		while (current->next)
			current = current->next;
		current->next = neu;
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

void	ft_export(t_data *sh, char **s)
{
	char	**printout;
	int		i;

	if (s)
		ft_enlist(sh, s);
	else
	{
		printout = env_tab(sh);
		if (!printout)
			perror("system malfunction");
		else
		{
			printout = ft_sort_char_tab(printout);
			i = -1;
			while (printout[++i])
			{
				ft_putstr_fd(printout[i], 1);
				ft_putchar_fd('\n', 1);
			}
			ft_free_tab(printout);
		}
	}
}
