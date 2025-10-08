/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_math.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egrisel <egrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 12:21:50 by egrisel           #+#    #+#             */
/*   Updated: 2025/10/08 14:26:38 by egrisel          ###   ########.fr       */
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
