/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:40:43 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/04/28 13:06:10 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h> //to use malloc()
#include <stdint.h> //to use SIZE_MAX
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ret;

	if (nmemb == 0 || size == 0)
	{
		ret = malloc(0);
		if (ret == NULL)
			return (NULL);
		return (ret);
	}
	if (nmemb > SIZE_MAX / size)
		return (NULL);
	ret = malloc(nmemb * size);
	if (ret == NULL)
		return (NULL);
	ft_bzero(ret, nmemb * size);
	return (ret);
}
