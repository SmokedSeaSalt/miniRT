/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 10:38:50 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/10/24 11:08:03 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/// @brief float(double) to string. will always do up to one digit after the ..
/// @param val
/// @return malloced str
char *ft_ftoa(double val)
{
	int fpart;
	char *reti;
	char *retf;
	char *tmp;

	fpart = (int)(((int)val - val) * 10);
	reti = ft_itoa((int)val);
	if (reti == NULL)
		return (NULL);
	tmp = ft_itoa((int)(fpart * 10));
	if (tmp == NULL)
		return (free(reti), NULL);
	retf = ft_strjoin(".", tmp);
	free(tmp);
	if (retf == NULL)
		return (free(reti), NULL);
	tmp = ft_strjoin(reti, retf);
	return (free(reti), free(retf), tmp);
}
