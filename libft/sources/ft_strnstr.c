/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 18:34:58 by ajazbuti          #+#    #+#             */
/*   Updated: 2021/09/15 15:15:10 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t			i;
	size_t			j;
	unsigned char	*hay;
	unsigned char	*needl;

	if (*needle == '\0')
		return ((char *)haystack);
	i = 0;
	hay = (unsigned char *)haystack;
	needl = (unsigned char *)needle;
	while (i < len && haystack[i])
	{
		j = 0;
		while (i + j < len && hay[i] && (hay[i + j] == needl[j]))
		{
			j++;
			if (needle[j] == '\0')
				return ((char *)&(haystack[i]));
		}
		i++;
	}
	return (NULL);
}
