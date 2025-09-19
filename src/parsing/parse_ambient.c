/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 11:58:48 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/09/19 13:11:18 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>		//to use free
#include <stdio.h>		//to use printf
#include "parsing.h"
#include "helpers.h"
#include "libft.h"
#include "structs.h"

static int	fill_ambient_struct(t_ambient *ambient, char **line)
{
	if (count_arguments(line) != 5)
		return (printf("Ambient: Incorrect amount of arguments"), 1);
	ambient->ratio = ft_atof(line[1]);
	if (ambient->ratio < 0.0 || ambient->ratio > 1.0)
		return (printf("Ambient: Ratio out of range"), 1);
	ambient->color = fill_color(line[2], line[3], line[4]);
	if (color_out_of_range(ambient->color))
		return (printf("Ambient: Color out of range"), 1);
	return (0);
}

int	new_ambient_struct(t_scene *scene, char **line)
{
	t_ambient	*ambient;

	if (scene->ambient != NULL)
		return (printf("Ambient: Does not support multiple elements"), 1);
	ambient = ft_calloc(1, sizeof(t_ambient));
	if (ambient == NULL)
		return (printf("Malloc fail"), 2);
	if (fill_ambient_struct(ambient, line) != 0)
		return (free(ambient), 1);
	scene->ambient = ambient;
	return (0);
}
