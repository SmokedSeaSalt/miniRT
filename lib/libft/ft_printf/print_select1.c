/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_select1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:42:57 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/05/20 15:37:39 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_c(va_list args)
{
	char	c;

	c = va_arg(args, unsigned int);
	return (write(1, &c, 1));
}

int	print_s(va_list args)
{
	char	*s;

	s = va_arg(args, char *);
	if (s == NULL)
		return (write(1, "(null)", 6));
	return (write(1, s, pf_strlen(s)));
}

int	print_p(va_list args)
{
	void	*p;

	p = va_arg(args, void *);
	if (p == NULL)
		return (write(1, "(nil)", 5));
	write(1, "0x", 2);
	return (pf_putpointer((unsigned long long)p) + 2);
}

int	print_d(va_list args)
{
	int	x;

	x = va_arg(args, int);
	return (pf_putnbr(x));
}

int	print_u(va_list args)
{
	unsigned int	x;

	x = va_arg(args, unsigned int);
	return (pf_putunsignednbr(x));
}
