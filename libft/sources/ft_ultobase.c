/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultobase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 23:28:04 by ajazbuti          #+#    #+#             */
/*   Updated: 2021/11/18 13:10:39 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(unsigned long n, int base)
{
	int	i;

	if (n == 0)
		return (2);
	i = 1;
	while (n)
	{
		n = n / base;
		i++;
	}
	return (i);
}

static void	ft_result(char *result, unsigned long n, char *base_to, int len)
{
	int	base;
	int	i;

	base = ft_strlen(base_to);
	if (n == 0)
	{
		result[0] = base_to[0];
		return ;
	}
	--len;
	while (len)
	{
		len--;
		i = n % base;
		result[len] = base_to[i];
		n = n / base;
	}
}

char	*ft_ultobase(unsigned long n, char *base_to)
{
	char	*result;
	int		len;
	int		base;

	base = ft_strlen(base_to);
	if (base < 2)
		return (NULL);
	result = NULL;
	len = ft_len(n, base);
	result = (char *)ft_calloc(sizeof(char), len);
	if (!result)
		return (NULL);
	ft_result(result, n, base_to, len);
	return (result);
}
