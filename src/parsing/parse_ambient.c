/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 11:58:48 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/11/04 14:23:58 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>		//to use free
#include <stdio.h>		//to use printf
#include "parsing.h"
#include "helpers.h"
#include "libft.h"
#include "structs.h"
#include "math_inc.h"
#include "consts.h"

static int	fill_ambient_struct(t_ambient *ambient, char **line)
{
	if (count_arguments(line) != 3)
		return (printf("Error\nAmbient: " N_ARGS_ERR "\n"), 1);
	if (parse_ratio(&(ambient->ratio), line[1]) != 0)
		return (printf("Ambient: Ratio parsing error\n"), 1);
	if (parse_color(&(ambient->color), line[2]) != 0)
		return (printf("Ambient: Color parsing error\n"), 1);
	ambient->intensity = vec3_new( \
(ambient->color.r / 255) * ambient->ratio, \
(ambient->color.g / 255) * ambient->ratio, \
(ambient->color.b / 255) * ambient->ratio);
	return (0);
}

int	new_ambient_struct(t_scene *scene, char **line)
{
	t_ambient	*ambient;

	if (scene->ambient != NULL)
		return (printf("Error\nAmbient: "N_ELEMENTS_ERR"\n"), 1);
	ambient = ft_calloc(1, sizeof(t_ambient));
	if (ambient == NULL)
		return (printf("Error\nMalloc fail\n"), 2);
	if (fill_ambient_struct(ambient, line) != 0)
		return (free(ambient), 1);
	scene->ambient = ambient;
	return (0);
}
