/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_math.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egrisel <egrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 12:21:50 by egrisel           #+#    #+#             */
/*   Updated: 2025/10/08 16:47:45 by egrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "math_inc.h"
#include <math.h>

// cos(θ) = (dot(a,b)) / (mag(a) * mag(b))
float	get_angle_between_vec3(t_vec3 *vec3_a, t_vec3 *vec3_b)
{
	float	numerator;
	float	denominator;

	numerator = vec3_dot(*vec3_a, *vec3_b);
	denominator = vec3_length(*vec3_a) * vec3_length(*vec3_b);
	return (acosf(numerator / denominator));
}

// Vector from A to B is vec3 = [B.x - A.x, B.y - A.y, B.z - A.z]
t_vec3	get_vec3_betweem_two_points(t_vec3 *a, t_vec3 *b)
{
	t_vec3	vec3;

	vec3.x = b->x - a->x;
	vec3.y = b->x - a->y;
	vec3.z = b->z - a->z;
	return (vec3);
}

/// @brief positive dot means angle < 90 (acute), negative dot means angle > 90.
/// zero dot means angle == 90
int	is_vec3_angle_acute(t_vec3 *a, t_vec3 *b)
{
	return (vec3_dot(*a, *b) > 0.0f);
}
