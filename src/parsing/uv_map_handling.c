/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_map_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 10:42:19 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/12/12 11:32:50 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs.h"
#include <stdlib.h>
#include <stdio.h>

t_uv_map	*get_uv_map(char *line)
{
	t_uv_map	*map;

	if (ft_strncmp(line, "default", ft_strlen(line)) == 0)
		return (NULL);
	map = (t_uv_map *)ft_calloc(1, sizeof(t_uv_map));
	if (map == NULL)
		return (NULL);
	if (ft_strncmp(line, "checkered", ft_strlen(line)) == 0)
	{
		map->type = CHECKERBOARD;
		return (map);
	}
	map->type = PNG;
	map->png = mlx_load_png(line);
	if (map->png == NULL)
	{
		free(map);
		printf("Error\nParsing: Error reading file: %s\n", line);
		return (NULL);
	}
	return (map);
}

t_uv_map	*get_bump_map(char *line)
{
	t_uv_map	*map;
	if (ft_strncmp(line, "default", ft_strlen(line)) == 0)
		return (NULL);
	map = (t_uv_map *)ft_calloc(1, sizeof(t_uv_map));
	if (map == NULL)
		return (NULL);
	map->type = PNG;
	map->png = mlx_load_png(line);
	if (map->png == NULL)
	{
		free(map);
		printf("Error\nParsing: Error reading file: %s\n", line);
		return (NULL);
	}
	return (map);
}
