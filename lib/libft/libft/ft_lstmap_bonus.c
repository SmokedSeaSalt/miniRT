/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:13:33 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/05/01 15:02:20 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*isrc;
	t_list	*headdest;
	t_list	*new;
	void	*var;

	isrc = lst;
	headdest = NULL;
	while (isrc != NULL)
	{
		var = f(isrc->content);
		new = ft_lstnew(var);
		if (new == NULL)
		{
			free(var);
			ft_lstclear(&headdest, del);
			return (NULL);
		}
		ft_lstadd_back(&headdest, new);
		isrc = isrc->next;
	}
	return (headdest);
}
