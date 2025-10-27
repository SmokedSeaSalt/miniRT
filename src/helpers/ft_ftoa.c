/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 10:38:50 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/10/27 10:07:13 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char *geti(double *val)
{
	int nflag;
	char *tmp;
	char *reti;

	nflag = 0;
	if (*val < 0.0f)
	{
		*val = -(*val);
		nflag = 1;
	}
	reti = ft_itoa((int)*val);
	if (reti == NULL)
		return (NULL);
	if (nflag == 1)
	{
		tmp = ft_strjoin("-", reti);
		free(reti);
		reti = tmp;
	}
	return (reti);
}

static char *getf(double val)
{
	char *tmp;
	double	fpart;
	char *retf;

	fpart = (((val - (int)val) * 10) + 0.5);
	if (fpart > 9.99f)
		fpart = 9.0f;
	retf = ft_itoa((int)fpart);
	if (retf == NULL)
		return ( NULL);
	tmp = ft_strjoin(".", retf);
	free(retf);
	retf = tmp;
	return (retf);
}

/// @brief float(double) to string. will always do up to one digit after the ..
/// @param val
/// @return malloced str
char *ft_ftoa(double val)
{
	char *reti;
	char *retf;
	char *tmp;

	reti = geti(&val);
	if (reti == NULL)
		return (NULL);
	retf = getf(val);
	if (retf == NULL)
		return (free(reti), NULL);
	tmp = ft_strjoin(reti, retf);
	free(reti);
	free(retf);
	if (tmp == NULL)
		return (NULL);
	return (tmp);
}
