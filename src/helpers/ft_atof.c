/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:14:56 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/09/26 09:52:53 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <float.h>
#include <errno.h>

// The atof() function returns a double value that is produced by interpreting
// the input characters as a number. The return value is 0 if the function
// cannot convert the input to a value of that type. In case of overflow, the
// function sets errno to ERANGE and returns the value -HUGE_VAL or +HUGE_VAL.
/*
ascii string >>─┬─────────────┬─┬───┬─┬ digits ┬───┬─┬────────┬┬─>> float
                └ whitespaces ┘ ├ + ┤ │        └ . ┘ └ digits ┘│
                                └ - ┘ └───────── . ─── digits ─┘
*/

static int	ft_isspace(int c)
{
	if (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v')
	{
		return (c);
	}
	else
	{
		return (0);
	}
}

static int	set_minus_mult(const char *str, size_t *i)
{
	if (str[*i] == '-')
	{
		(*i)++;
		return (-1);
	}
	else if (str[*i] == '+')
		(*i)++;
	return (1);
}

static double	calc_ret_value(const char *str, size_t i, int minus_mult)
{
	double	scale;
	double	ret_value;
	int		dot_toggle;

	scale = 1;
	ret_value = 0;
	dot_toggle = 0;
	while (str[i] != '\0' && (ft_isdigit(str[i]) || str[i] == '.'))
	{
		if (str [i] == '.')
		{
			if (dot_toggle == 1)
				return (ret_value);
			dot_toggle = 1;
		}
		else if (dot_toggle == 0)
			ret_value = ret_value * 10 + ((str[i] - '0') * minus_mult);
		else
		{
			scale = scale / 10;
			ret_value = ret_value + (str[i] - '0') * scale * minus_mult;
		}
		i++;
	}
	return (ret_value);
}

double	ft_atof(const char *str)
{
	size_t	i;
	int		minus_mult;

	i = 0;
	while (ft_isspace(str[i]) != 0)
		i++;
	minus_mult = set_minus_mult(str, &i);
	return (calc_ret_value(str, i, minus_mult));
}
