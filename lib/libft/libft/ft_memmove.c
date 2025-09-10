/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:22:04 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/04/24 13:46:18 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const unsigned char	*srcp = (unsigned char*) src;
	unsigned char		*destp;
	size_t				i;

	destp = dest;
	if (destp < srcp)
	{
		i = 0;
		while (i < n)
		{
			destp[i] = srcp[i];
			i++;
		}
	}
	else if (destp > srcp)
	{
		i = n - 1;
		while (i + 1 > 0)
		{
			destp[i] = srcp[i];
			i--;
		}
	}
	return (dest);
}
