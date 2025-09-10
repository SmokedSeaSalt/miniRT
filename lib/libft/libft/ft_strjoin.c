/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 21:41:56 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/05/01 14:44:14 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	int		s1len;
	size_t	i;

	i = 0;
	ret = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(unsigned char));
	if (ret == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		ret[i] = s1[i];
		i++;
	}
	s1len = i;
	i = 0;
	while (s2[i] != '\0')
	{
		ret[s1len + i] = s2[i];
		i++;
	}
	ret[s1len + i] = '\0';
	return (ret);
}
