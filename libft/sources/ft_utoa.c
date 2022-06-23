/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 22:10:01 by ajazbuti          #+#    #+#             */
/*   Updated: 2021/11/05 23:12:02 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_len(unsigned int n)
{
	size_t	len;

	if (n == 0)
		return (2);
	len = 1;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static void	ft_utos(char *s, unsigned int n, size_t len)
{
	len--;
	while (len)
	{
		len--;
		*(s + len) = n % 10 + '0';
		n = n / 10;
	}
}

char	*ft_utoa(unsigned int n)
{
	size_t	len;
	char	*s;

	s = NULL;
	len = ft_len(n);
	s = (char *)ft_calloc(len, sizeof(char));
	if (!s)
		return (s);
	if (n == 0)
	{
		*s = '0';
		return (s);
	}
	ft_utos(s, n, len);
	return (s);
}
