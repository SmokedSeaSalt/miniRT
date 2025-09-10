/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 20:51:20 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/05/01 14:39:38 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strchr(const char *s, int c)
{
	char	*strp;
	size_t	i;

	strp = (char *)s;
	i = 0;
	while (strp[i] != '\0')
	{
		if (strp[i] == (char) c)
			return (&strp[i]);
		i++;
	}
	if (strp[i] == (char) c)
		return (&strp[i]);
	return ((void *)0);
}
