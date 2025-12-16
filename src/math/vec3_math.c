/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_math.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 12:21:50 by egrisel           #+#    #+#             */
/*   Updated: 2025/12/16 14:08:56 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "math_inc.h"
#include <math.h>

/// @brief gives the angle in degrees from two vectors.
/// @brief cos(θ) = (dot(a,b)) / (mag(a) * mag(b)).
/// @param vec3_a
/// @param vec3_b
/// @return	angle in degrees as float.
float	get_angle_between_vec3(t_vec3 *vec3_a, t_vec3 *vec3_b)
{
	float	numerator;
	float	denominator;

	numerator = vec3_dot(*vec3_a, *vec3_b);
	denominator = vec3_length(*vec3_a) * vec3_length(*vec3_b);
	return (acosf(numerator / denominator));
}

/// @brief check for acute angle between two vectors.
/// @param a
/// @param b
/// @return 1 if angle is acute, 0 if angle is not acute.
int	is_vec3_angle_acute(t_vec3 *a, t_vec3 *b)
{
	return (vec3_dot(*a, *b) > 0.0f);
}
