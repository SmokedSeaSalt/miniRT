/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:16:16 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/10/21 16:24:43 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_inc.h"
#include <math.h>

/// @brief creates a new t_vec3 with the input arguments.
/// @param x
/// @param y
/// @param z
/// @return t_vec3.
inline t_vec3	vec3_new(float x, float y, float z)
{
	t_vec3	result;

	result.x = x;
	result.y = y;
	result.z = z;
	result.w = 0.0f;
	return (result);
}

/// @brief calculates the length of the given t_vec3.
/// @param vec3
/// @return length as a float.
float	vec3_length(t_vec3 vec3)
{
	return (sqrtf(vec3.x * vec3.x + vec3.y * vec3.y + vec3.z * vec3.z));
}

/// @brief normalizes the t_vec3.
/// @param vec3
/// @return normalized t_vec3.
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

/// @brief calculates the dot product of two t_vec3.
/// @brief https://en.wikipedia.org/wiki/Dot_product.
/// @param a
/// @param b
/// @return the dot product as float.
float	vec3_dot(t_vec3 a, t_vec3 b)
{
	t_vec3	tmp;

	tmp.v = a.v * b.v;
	return (tmp.x + tmp.y + tmp.z);
}

/// @brief calculates the cross product of two t_vec3.
/// @brief the resulting cross product is the representation of the normal
/// @brief vector from the plane between vector a and b.
/// @brief https://en.wikipedia.org/wiki/Cross_product.
/// @param a
/// @param b
/// @return the cross product as t_vec3.
t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	t_vec3	tmp;

	tmp.x = ((a.y * b.z) - (a.z * b.y));
	tmp.y = -1 * ((a.x * b.z) - (a.z * b.x));
	tmp.z = ((a.x * b.y) - (a.y * b.x));
	return (tmp);
}

/// @brief sums all t_vec3 components.
/// @param vec3
/// @return sum as float.
float	vec3_sum_components(t_vec3 vec3)
{
	return (vec3.x + vec3.y + vec3.z);
}
