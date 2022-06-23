/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorunov <kmorunov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 21:12:06 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/06/22 22:17:12 by kmorunov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_str;
	size_t	size;

	if (!s)
		return (NULL);
	sub_str = NULL;
	size = ft_strlen(s + start);
	if (size < len)
		sub_str = (char *)ft_calloc(sizeof(char), (size + 1));
	else
		sub_str = (char *)ft_calloc(sizeof(char), (len + 1));
	if (!sub_str)
		return (sub_str);
	if (start > ft_strlen(s))
		return (sub_str);
	ft_strlcpy(sub_str, s + start, len + 1);
	return (sub_str);
}
