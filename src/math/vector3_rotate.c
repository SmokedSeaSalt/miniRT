/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egrisel <egrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 13:54:55 by egrisel           #+#    #+#             */
/*   Updated: 2025/10/07 14:44:36 by egrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "math.h"
#include "math_inc.h"

t_vec3	vec3_rotate_around_z(t_vec3 *vec3, float z_rad)
{
	t_mat3	rotation_matrix;

	rotation_matrix.row_0 = vec3_new(cosf(z_rad), -sinf(z_rad), 0);
	rotation_matrix.row_1 = vec3_new(sinf(z_rad), cosf(z_rad), 0);
	rotation_matrix.row_2 = vec3_new(0, 0, 1);
	return (mat3_mul_vec3(&rotation_matrix, vec3));
}
