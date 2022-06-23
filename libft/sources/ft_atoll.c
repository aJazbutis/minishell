/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 22:49:14 by ajazbuti          #+#    #+#             */
/*   Updated: 2021/11/22 00:57:47 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_atoll(const char *str)
{
	long long	i;
	int			set_sign;

	i = 0;
	set_sign = 1;
	while (*str == 32 || (*str > 7 && *str < 15))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			set_sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		i = i * 10 + (*str - '0');
		str++;
	}
	return (i * set_sign);
}
