/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extension_is_ok.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 19:01:11 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/01/12 21:19:22 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_extension_is_ok(char *ext, char *name)
{
	char	*s;
	size_t	len;

	len = ft_strlen(ext);
	s = ft_strnstr(name, ext, ft_strlen(name));
	if (ft_strlen(s) == len && !ft_strncmp(s, ext, len))
		return (1);
	return (0);
}

/*
** 	if (len >= ft_strlen(name))
**		return (0);
*/
