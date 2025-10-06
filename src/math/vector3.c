/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egrisel <egrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:16:16 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/10/06 14:03:17 by egrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_inc.h"
#include <math.h>

inline t_vec3	vec3_new(float x, float y, float z)
{
	t_vec3	result;

	result.x = x;
	result.y = y;
	result.z = z;
	result.w = 0.0f;
	return (result);
}

float	vec3_length(t_vec3 vec3)
{
	return (sqrtf(vec3.x * vec3.x + vec3.y * vec3.y + vec3.z * vec3.z));
}

t_vec3	vec3_normalize(t_vec3 vec3)
{
	float		length;
	t_vec3		result;

	length = vec3_length(vec3);
	if (length != 0.0f)
		result.v = vec3.v / vec3_new(length, length, length).v;
	else
		result = vec3_new(0, 0, 0);
	return (result);
}

float	vec3_dot(t_vec3 a, t_vec3 b)
{
	t_vec3	tmp;

	tmp.v = a.v * b.v;
	return (tmp.x + tmp.y + tmp.z);
}

t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	t_vec3	tmp;

	tmp.x = ((a.y * b.z) - (a.z * b.y));
	tmp.y = -1 * ((a.x * b.z) - (a.z * b.x));
	tmp.z = ((a.x * b.y) - (a.y * b.x));
	return (tmp);
}

float	vec3_sum_components(t_vec3 vec3)
{
	return (vec3.x + vec3.y + vec3.z);
}
