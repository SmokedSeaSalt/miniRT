/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:45:52 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/12/16 14:10:30 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_inc.h"
#include "structs.h"
#include "libft.h"
#include "helpers.h"
#include "consts.h"
#include <stdio.h>

int	count_arguments(char **line)
{
	int	i;

	i = 0;
	while (line[i] != NULL)
		i++;
	return (i);
}

int	color_out_of_range(t_color color)
{
	if (color.r < 0 || color.r > 255 \
|| color.g < 0 || color.g > 255 \
|| color.b < 0 || color.b > 255)
		return (1);
	return (0);
}

int	orientation_out_of_range(t_vec3 orientation)
{
	if (orientation.x < -1.0f || orientation.x > 1.0f \
|| orientation.y < -1.0f || orientation.y > 1.0f \
|| orientation.z < -1.0f || orientation.z > 1.0f)
		return (1);
	return (0);
}

int	orientation_all_zero(t_vec3 orientation)
{
	if (orientation.x == 0.0f && orientation.y == 0.0f && orientation.z == 0.0f)
		return (1);
	return (0);
}

t_vec3	fill_vec3(char *x_str, char *y_str, char *z_str)
{
	t_vec3	vec3;

	vec3 = vec3_new(ft_atof(x_str), ft_atof(y_str), ft_atof(z_str));
	return (vec3);
}

void	add_object_to_back(t_object **list, t_object *new)
{
	t_object	*tmp;

	if (list == NULL)
		return ;
	if (*list == NULL)
		*list = new;
	else
	{
		tmp = *list;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

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
