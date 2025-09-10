/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:47:47 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/05/13 16:40:54 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	select_print(char c, va_list args)
{
	if (c == 'c')
		return (print_c(args));
	else if (c == 's')
		return (print_s(args));
	else if (c == 'p')
		return (print_p(args));
	else if (c == 'd' || c == 'i')
		return (print_d(args));
	else if (c == 'u')
		return (print_u(args));
	else if (c == 'x')
		return (print_lx(args));
	else if (c == 'X')
		return (print_ux(args));
	else if (c == '%')
		return (print_pct());
	else
		return (-1);
}

int	process_str(const char *c, va_list args)
{
	int		count;
	size_t	index;
	int		ret;

	index = 0;
	count = 0;
	while (c[index] != '\0')
	{
		if (c[index] == '%')
		{
			ret = select_print(c[index + 1], args);
			if (ret == -1)
				return (-1);
			count += ret;
			index += 2;
		}
		else
		{
			write(1, &c[index], 1);
			index++;
			count++;
		}
	}
	return (count);
}

int	ft_printf(const char *c, ...)
{
	va_list	args;
	int		ret;

	if (c == NULL)
		return (-1);
	va_start(args, c);
	ret = process_str(c, args);
	va_end(args);
	return (ret);
}
