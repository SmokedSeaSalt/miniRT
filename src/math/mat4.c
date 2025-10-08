/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egrisel <egrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 10:33:40 by egrisel           #+#    #+#             */
/*   Updated: 2025/10/08 14:26:04 by egrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_inc.h"
#include "structs.h"

inline t_mat4	mat4_new(t_vec4 *row_0, t_vec4 *row_1,
						t_vec4 *row_2, t_vec4 *row_3)
{
	t_mat4	mat4;

	mat4.row_0 = *row_0;
	mat4.row_1 = *row_1;
	mat4.row_2 = *row_2;
	mat4.row_0 = *row_3;
	return (mat4);
}

inline t_vec4	mat4_mul_vec4(t_mat4 *mat4, t_vec4 *input_vec4)
{
	t_vec4	vec4;

	vec4.x = vec4_sum_components((t_vec4)(mat4->row_0.v * input_vec4->v));
	vec4.y = vec4_sum_components((t_vec4)(mat4->row_1.v * input_vec4->v));
	vec4.z = vec4_sum_components((t_vec4)(mat4->row_2.v * input_vec4->v));
	vec4.w = vec4_sum_components((t_vec4)(mat4->row_3.v * input_vec4->v));
	return (vec4);
}
