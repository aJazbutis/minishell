/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 14:13:37 by ajazbuti          #+#    #+#             */
/*   Updated: 2021/09/22 18:38:15 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_str_end(char *s)
{
	char	*str;

	while (*s)
		s++;
	str = s;
	return (str);
}

char	*ft_strrchr(const char *s, int c)
{
	char	x;
	char	*str;

	x = (char)c;
	str = (char *)s;
	str = ft_str_end(str);
	while (str >= s)
	{
		if (*str == x)
			return (str);
		str--;
	}
	return (NULL);
}
