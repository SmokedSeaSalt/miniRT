/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_select2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:43:19 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/05/20 15:37:51 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_lx(va_list args)
{
	unsigned int	x;

	x = va_arg(args, unsigned int);
	return (pf_puthex(x, 0));
}

int	print_ux(va_list args)
{
	unsigned int	x;

	x = va_arg(args, unsigned int);
	return (pf_puthex(x, 1));
}

int	print_pct(void)
{
	return (write(1, "%", 1));
}
