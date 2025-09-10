/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:37:31 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/05/01 13:26:32 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	str_i;
	char			*ret;

	str_i = start;
	if (ft_strlen(s) < start)
	{
		ret = malloc(1);
		if (ret == NULL)
			return (NULL);
		ret[0] = '\0';
		return (ret);
	}
	if (start + len <= ft_strlen(s))
		ret = malloc((len + 1) * sizeof(unsigned char));
	else
		ret = malloc((ft_strlen(s) - start + 1));
	if (ret == NULL)
		return (NULL);
	while (s[str_i] != '\0' && str_i - start < len)
	{
		ret[str_i - start] = s[str_i];
		str_i++;
	}
	ret[str_i - start] = '\0';
	return (ret);
}
