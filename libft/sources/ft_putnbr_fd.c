/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 16:07:11 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/01/31 15:42:44 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_put_nbr_fd(long n, int fd)
{
	char	*base;

	base = "0123456789";
	if (n > 9)
	{
		ft_put_nbr_fd(n / 10, fd);
		n = n % 10;
	}
	write(fd, &base[n], 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	m;

	m = (long)n;
	if (m < 0)
	{
		write(fd, "-", 1);
		m *= -1;
	}
	ft_put_nbr_fd(m, fd);
}

/*static int	ft_putnbr(int n, int fd)
{
	int	m;

	m = n % 10 + '0';
	if (n == 0)
		return (m);
	else
	{
		m = n % 10 + '0';
		ft_putnbr(n / 10, fd);
		write(fd, &m, 1);
	}
	return (0);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == INT_MAX)
		write(fd, "2147483647", 10);
	else if (n == INT_MIN)
		write(fd, "-2147483648", 11);
	else if (n == 0)
		write(fd, "0", 1);
	else
	{
		if (n < 0)
		{
			write(fd, "-", 1);
			n = n * (-1);
		}
		ft_putnbr(n, fd);
	}
}*/
