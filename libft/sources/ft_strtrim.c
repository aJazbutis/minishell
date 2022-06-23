/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorunov <kmorunov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 14:34:56 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/06/22 22:17:04 by kmorunov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s;
	char	*e;
	int		start;

	if (!s1 || !set)
		return (NULL);
	s = (char *)s1;
	start = 0;
	while (ft_strchr(set, *s) && *s)
	{
		start++;
		s++;
	}
	e = (char *)s1;
	while (*e)
		e++;
	if (e == s)
		return (ft_strdup(""));
	--e;
	while (ft_strchr(set, *(e)))
		e--;
	return (ft_substr(s1, start, (e - s + 1)));
}
