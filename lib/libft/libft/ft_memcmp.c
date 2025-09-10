/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:26:36 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/04/25 12:32:16 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*mem1;
	unsigned char	*mem2;
	size_t			i;

	mem1 = (unsigned char *)s1;
	mem2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (mem1[i] > mem2[i])
		{
			return (mem1[i] - mem2[i]);
		}
		if (mem1[i] < mem2[i])
		{
			return (mem1[i] - mem2[i]);
		}
		i++;
	}
	return (0);
}
