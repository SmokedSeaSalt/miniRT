/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_fillers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 14:58:50 by mvan-rij          #+#    #+#             */
/*   Updated: 2026/01/02 14:07:45 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "consts.h"
#include "parsing.h"
#include "math_inc.h"
#include "libft.h"
#include "helpers.h"
#include <stdio.h>

int	parse_color(t_color *color, char *str)
{
	char	**split;

	split = ft_split(str, ',');
	if (split == NULL || count_arguments(split) != 3)
		return (ft_free_split(split), 1);
	color->r = ft_atoi(split[0]);
	color->g = ft_atoi(split[1]);
	color->b = ft_atoi(split[2]);
	ft_free_split(split);
	if (color_out_of_range(*color) == 1)
		return (printf("Error\nColor: " RANGE_ERR "\n"), 1);
	return (0);
}

int	parse_orig(t_vec3 *orig, char *str)
{
	char	**split;

	split = ft_split(str, ',');
	if (split == NULL || count_arguments(split) != 3)
	{
		ft_free_split(split);
		return (printf("Error\nOrigin: "N_ARGS_ERR"\n"), 1);
	}
	*orig = fill_vec3(split[0], split[1], split[2]);
	ft_free_split(split);
	return (0);
}

int	parse_normal_vector(t_vec3 *vec, char *str)
{
	char	**split;

	split = ft_split(str, ',');
	if (split == NULL || count_arguments(split) != 3)
	{
		ft_free_split(split);
		return (printf("Error\nOrientation: "N_ARGS_ERR"\n"), 1);
	}
	*vec = fill_vec3(split[0], split[1], split[2]);
	ft_free_split(split);
	if (orientation_out_of_range(*vec) == 1)
		return (printf("Error\nOrientation: "RANGE_ERR"\n"), 1);
	if (orientation_all_zero(*vec) == 1)
		return (printf("Error\nOrientation: "VEC_0_ERR"\n"), 1);
	*vec = vec3_normalize(*vec);
	return (0);
}

int	parse_ratio(float *ratio, char *str)
{
	*ratio = ft_atof(str);
	if (*ratio < 0.0 || *ratio > 1.0)
		return (printf("Error\nRatio: "RANGE_ERR"\n"), 1);
	return (0);
}

int	parse_fov(float *fov, char *str)
{
	*fov = deg_to_rad(ft_atof(str));
	if (*fov < 0 || *fov > deg_to_rad(180))
		return (printf("Error\nFOV: "RANGE_ERR"\n"), 1);
	return (0);
}
