/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envius.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:49:05 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/05/06 16:07:01 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	ENVIUS_H
#define	ENVIUS_H
# include <stdio.h>
# include "libft.h"

typedef struct s_env_lst
{
	int					unset;
	int					not_exp;
	char				*var;
	char				*val;
	struct s_env_lst	*next;
}t_env_lst;

void	ft_clean_env(t_env_lst	**env);
int		ft_list_env(t_env_lst	**env);
//char	*ft_getenv(t_data *sh, char s);
#endif
