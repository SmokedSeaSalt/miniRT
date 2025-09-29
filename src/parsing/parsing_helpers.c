/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:45:52 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/09/29 13:14:37 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_inc.h"
#include "structs.h"
#include "libft.h"
#include "helpers.h"

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

t_color	fill_color(char *r_str, char *g_str, char *b_str)
{
	t_color	color;

	color.r = ft_atoi(r_str);
	color.g = ft_atoi(g_str);
	color.b = ft_atoi(b_str);
	return (color);
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
