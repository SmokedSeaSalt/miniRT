/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 01:20:24 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/04/27 14:53:26 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h> //to use malloc()
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	start;
	int				end;
	char			*ret;

	start = 0;
	end = ft_strlen(s1);
	while (ft_strchr(set, s1[start]) != NULL && s1[start] != '\0')
		start++;
	while (ft_strrchr(set, s1[end - 1]) != NULL && end >= 0)
		end--;
	ret = ft_substr(s1, start, end - start);
	if (ret == NULL)
		return (NULL);
	return (ret);
}
