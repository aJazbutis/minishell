/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 19:44:11 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/01/27 19:59:01 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	if (s)
	{
		if (*s == 0 && (char)c == 0)
			return ((char *)s);
		while (*s)
		{
			if (*s == (char)c)
				return ((char *)s);
			s++;
			if (*s == 0 && (char)c == 0)
				return ((char *)s);
		}
	}
	return (NULL);
}
