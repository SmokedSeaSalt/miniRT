/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_map_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 10:42:19 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/12/23 14:13:07 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs.h"
#include <stdlib.h>
#include <stdio.h>

void	get_uv_map(char *line, t_uv_map *map)
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
	return ;
}

void	get_bump_map(char *line, t_uv_map *map)
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
	return ;
}
