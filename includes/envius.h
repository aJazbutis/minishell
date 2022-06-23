/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envius.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:49:05 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/06/15 21:39:50 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIUS_H
# define ENVIUS_H

# include <stdio.h>
# include "libft.h"

typedef struct s_env_lst
{
	unsigned int		unset;
	unsigned int		not_exp;
	char				*var;
	char				*val;
	struct s_env_lst	*next;
}t_env_lst;

void	ft_clean_env(t_env_lst	**env);
void	ft_enlist(t_env_lst **env, t_env_lst *neu);
int		ft_list_env(t_env_lst **env, char **envp);
int		ft_env_size(t_env_lst	*env);

#endif
