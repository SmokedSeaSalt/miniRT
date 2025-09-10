/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 20:56:26 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/05/01 15:01:32 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*strp;
	size_t	i;
	size_t	len;

	strp = (char *)s;
	i = 0;
	len = ft_strlen(s);
	while (i <= len)
	{
		if (strp[len - i] == (char) c)
			return (&strp[len - i]);
		i++;
	}
	return (NULL);
}
