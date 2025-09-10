/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:59:02 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/05/01 14:43:11 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	size_t	str_i;
	char	*sptr;
	char	*ret;

	sptr = (char *)s;
	str_i = 0;
	while (sptr[str_i] != '\0')
	{
		str_i++;
	}
	ret = malloc((str_i + 1) * sizeof(unsigned char));
	if (ret == NULL)
		return (NULL);
	str_i = 0;
	while (sptr[str_i] != '\0')
	{
		ret[str_i] = sptr[str_i];
		str_i++;
	}
	ret[str_i] = '\0';
	return (ret);
}
