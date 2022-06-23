/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 16:32:50 by ajazbuti          #+#    #+#             */
/*   Updated: 2021/09/22 19:09:34 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_len(int n)
{
	size_t	len;
	size_t	sign;
	long	nb;

	if (n == 0)
		return (2);
	nb = (long)n;
	len = 1;
	if (nb < 0)
	{
		nb = nb * (-1);
		sign = 1;
	}
	else
		sign = 0;
	while (nb != 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len + sign);
}

static void	ft_itos(char *s, int n, size_t len)
{
	long	nb;
	size_t	sign;

	nb = (long)n;
	sign = 0;
	if (nb < 0)
	{
		*s = '-';
		nb = nb * (-1);
		sign = 1;
	}
	len--;
	while (len > sign)
	{
		len--;
		*(s + len) = nb % 10 + '0';
		nb = nb / 10;
	}
}

char	*ft_itoa(int n)
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
	ft_itos(s, n, len);
	return (s);
}
