/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:53:45 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/05/20 15:38:42 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h> //to use size_t
#include "ft_printf.h"

size_t	pf_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	pf_putnbr(int nb)
{
	int		i;
	char	c;
	int		ret;

	ret = 0;
	if (nb == -2147483648)
		return (write(1, "-2147483648", 11));
	if (nb < 0)
	{
		nb = nb * -1;
		write(1, "-", 1);
		return (pf_putnbr(nb) + 1);
	}
	else if (nb > 9)
	{
		ret = pf_putnbr(nb / 10);
		i = (nb % 10);
		c = '0' + i;
		return (ret + write(1, &c, 1));
	}
	else
	{
		c = '0' + nb;
		return (ret + write(1, &c, 1));
	}
}

int	pf_putunsignednbr(unsigned int nb)
{
	unsigned int	i;
	char			c;
	int				ret;

	ret = 0;
	if (nb > 9)
	{
		ret = pf_putunsignednbr(nb / 10);
		i = (nb % 10);
		c = '0' + i;
		return (ret + write(1, &c, 1));
	}
	else
	{
		c = '0' + nb;
		return (ret + write(1, &c, 1));
	}
}

int	pf_puthex(unsigned int nb, int uppercase)
{
	char	c;
	int		ret;

	ret = 0;
	if (nb > 15)
	{
		ret = pf_puthex(nb / 16, uppercase);
		if (uppercase == 1)
			c = "0123456789ABCDEF"[nb % 16];
		else
			c = "0123456789abcdef"[nb % 16];
		return (ret + write(1, &c, 1));
	}
	else
	{
		if (uppercase == 1)
			c = "0123456789ABCDEF"[nb % 16];
		else
			c = "0123456789abcdef"[nb % 16];
		return (ret + write(1, &c, 1));
	}
}

int	pf_putpointer(unsigned long long p)
{
	char	c;
	int		ret;

	ret = 0;
	if (p > 15)
	{
		ret = pf_putpointer(p / 16);
		c = "0123456789abcdef"[p % 16];
		return (ret + write(1, &c, 1));
	}
	else
	{
		c = "0123456789abcdef"[p % 16];
		return (ret + write(1, &c, 1));
	}
}
