/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_map_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 10:42:19 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/12/23 15:12:05 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs.h"
#include <stdlib.h>
#include <stdio.h>

void	add_texture_delete_list(t_texture_list **list, mlx_texture_t *png)
{
	t_texture_list *new;
	t_texture_list *tmp;

	new = ft_calloc(1, sizeof(t_texture_list));
	if (new == NULL)
		return ;
	new->png = png;
	if (*list == NULL)
	{
		*list = new;
		return ;
	}
	tmp = *list;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	return ;
}

void	get_uv_map(char *line, t_uv_map *map, t_texture_list *list)
{
	if (ft_strncmp(line, "default", ft_strlen(line)) == 0)
		return ;
	if (ft_strncmp(line, "checkered", ft_strlen(line)) == 0)
	{
		map->type = CHECKERBOARD;
		return ;
	}
	map->type = PNG;
	map->png = mlx_load_png(line);
	if (map->png == NULL)
	{
		printf("Error\nParsing: Error reading file: %s\n", line);
		map->type = DEFAULT;
		return ;
	}
	add_texture_delete_list(&list, map->png);
	return ;
}

void	get_bump_map(char *line, t_uv_map *map, t_texture_list *list)
{
	if (ft_strncmp(line, "default", ft_strlen(line)) == 0)
		return ;
	map->type = PNG;
	map->png = mlx_load_png(line);
	if (map->png == NULL)
	{
		printf("Error\nParsing: Error reading file: %s\n", line);
		map->type = DEFAULT;
		return ;
	}
	add_texture_delete_list(&list, map->png);
	return ;
}
