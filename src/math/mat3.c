/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egrisel <egrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 13:49:39 by egrisel           #+#    #+#             */
/*   Updated: 2025/10/06 13:58:15 by egrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "math_inc.h"

inline t_mat3	mat3_new(t_vec3 *row_0, t_vec3 *row_1,t_vec3 *row_2)
{
	t_mat3	mat3;

	mat3.row_0 = *row_0;
	mat3.row_1 = *row_1;
	mat3.row_2 = *row_2;
	return (mat3);
}

inline t_vec3	mat3_mul_vec3(t_mat3 *mat3, t_vec3 *input_vec3)
{
	t_vec3	vec3;
	
	vec3.x = vec3_sum_components((t_vec3)(mat3->row_0.v * input_vec3->v));
	vec3.y = vec3_sum_components((t_vec3)(mat3->row_1.v * input_vec3->v));
	vec3.z = vec3_sum_components((t_vec3)(mat3->row_2.v * input_vec3->v));
	return (vec3);
}