/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 17:52:33 by ajazbuti          #+#    #+#             */
/*   Updated: 2021/09/16 17:35:33 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	unsigned int	i;
	int				set_sign;

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
		if (i == (unsigned int)INT_MIN && set_sign == -1)
			return (INT_MIN);
		if (i > (unsigned int)INT_MAX)
			return (0);
	}
	return ((int)i * set_sign);
}
