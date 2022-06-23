/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorunov <kmorunov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 14:52:18 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/06/22 22:16:57 by kmorunov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*f_str;
	unsigned int	i;

	if (!s)
		return (NULL);
	f_str = NULL;
	f_str = (char *)ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!f_str)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		f_str[i] = f(i, s[i]);
		i++;
	}
	return (f_str);
}
