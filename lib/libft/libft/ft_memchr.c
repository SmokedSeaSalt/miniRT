/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:26:41 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/04/24 10:05:19 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*memptr;
	size_t			i;

	memptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (memptr[i] == (unsigned char) c)
			return (&memptr[i]);
		i++;
	}
	return ((void *)0);
}
