/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 19:37:49 by ajazbuti          #+#    #+#             */
/*   Updated: 2021/09/07 20:29:23 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memset(void *b, int c, size_t len)
{
	char	*b_char;
	size_t	i;

	i = 0;
	b_char = b;
	while (i < len)
	{
		b_char[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
