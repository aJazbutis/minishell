/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utobase.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 20:58:24 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/06/20 16:00:30 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*static int	ft_len(unsigned int n, int base)
{
	int	i;

	if (n == 0)
		return (2);
	i = 1;
	if (n < 0)
	{
		n = n * (-1);
		i = 2;
	}
	while (n)
	{
		n = n / base;
		i++;
	}
	return (i);
}

static void	ft_result(char *result, unsigned int n, char *base_to, int len)
{
	int	base;
	int	sign;
	int	i;

	base = ft_strlen(base_to);
	sign = 0;
	if (n == 0)
	{
		result[0] = base_to[0];
		return ;
	}
	if (n < 0)
	{
		result[0] = '-';
		n = n * (-1);
		sign = 1;
	}
	while (len >= sign)
	{
		i = n % base;
		result[len] = base_to[i];
		n = n / base;
		len--;
	}
}*/

static int	ft_len(unsigned int n, int base)
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

static void	ft_result(char *result, unsigned int n, char *base_to, int len)
{
	int	base;
	int	i;

	base = ft_strlen(base_to);
	if (n == 0)
	{
		result[0] = base_to[0];
		return ;
	}
	while (len)
	{
		i = n % base;
		result[len] = base_to[i];
		n = n / base;
		len--;
	}
}

char	*ft_utobase(unsigned int n, char *base_to)
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
	ft_result(result, n, base_to, len - 2);
	return (result);
}
