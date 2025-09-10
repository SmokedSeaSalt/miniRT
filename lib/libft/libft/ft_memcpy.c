/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:10:31 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/04/30 16:14:59 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*srcp;
	unsigned char	*destp;
	size_t			i;

	if (n == 0)
		return (dest);
	i = 0;
	srcp = (unsigned char *)src;
	destp = (unsigned char *)dest;
	while (i < n)
	{
		destp[i] = srcp[i];
		i++;
	}
	return (dest);
}
