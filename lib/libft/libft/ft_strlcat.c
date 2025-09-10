/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:31:46 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/04/24 13:04:06 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

static size_t	ft_getstrsize(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
	{
		len++;
	}
	return (len);
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_index;
	size_t	src_index;
	size_t	total_len;

	dest_index = 0;
	src_index = 0;
	total_len = ft_getstrsize(dest) + ft_getstrsize(src);
	while (dest[dest_index] != '\0' && dest_index < size)
	{
		dest_index++;
	}
	if (dest_index == size)
	{
		return (size + ft_getstrsize(src));
	}
	while (src[src_index] != '\0' && dest_index < size - 1)
	{
		dest[dest_index] = src[src_index];
		dest_index++;
		src_index++;
	}
	dest[dest_index] = '\0';
	return (total_len);
}
