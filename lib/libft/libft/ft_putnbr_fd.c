/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:21:35 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/04/29 10:21:27 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_str_size(long n)
{
	int	str_size;

	str_size = 1;
	if (n < 0)
	{
		str_size++;
		n *= -1;
	}
	if (n == 0)
		str_size++;
	while (n != 0)
	{
		str_size++;
		n /= 10;
	}
	return (str_size);
}

static void	ft_fill_a(char *ret, long nbr, int str_size)
{
	int	offset;
	int	i;

	offset = 2;
	i = 0;
	if (nbr < 0)
	{
		ret[i] = '-';
		i++;
		nbr *= -1;
		offset = 1;
	}
	if (nbr == 0)
		ret[0] = '0';
	while (nbr != 0)
	{
		ret[str_size - i - offset] = (nbr % 10) + '0';
		nbr /= 10;
		i++;
	}
	ret[str_size - 1] = '\0';
}

void	ft_putnbr_fd(int n, int fd)
{
	long	nbr;
	char	ret[12];
	int		str_size;

	nbr = (long)n;
	str_size = ft_get_str_size(n);
	ft_fill_a(ret, nbr, str_size);
	ft_putstr_fd(ret, fd);
}
