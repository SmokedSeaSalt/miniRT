/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:45:22 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/04/25 15:47:14 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

static size_t	ft_to_findcmp(char *offsetbig, const char *little, size_t len)
{
	size_t	i;

	i = 0;
	while (little[i] != '\0')
	{
		if (offsetbig[i] != little[i] || i >= len)
		{
			return (-1);
		}
		i++;
	}
	return (0);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*bigp;
	size_t	str_index;

	bigp = (char *)big;
	str_index = 0;
	if (little[0] == '\0')
		return (bigp);
	while (bigp[str_index] != '\0' && str_index < len)
	{
		if (bigp[str_index] == little[0])
		{
			if (ft_to_findcmp(&bigp[str_index], little, len - str_index) == 0)
			{
				return (&bigp[str_index]);
			}
		}
		str_index++;
	}
	return ((void *)0);
}
