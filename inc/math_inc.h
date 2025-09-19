/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_inc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 15:53:33 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/09/19 13:29:16 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_INC_H
# define MATH_INC_H
/// @brief union for adaptable vector operations
/// @param float v for +-*/ operations on vector	-> vec3_1.v - vec3_2.v
/// @param struct for x y z access					-> vec3.x
/// @param float array[4] for array like access 	-> vec3.array[1]
typedef union u_vec3
{
	float v	__attribute__	((vector_size(16)));
	struct
	{
		float	x;
		float	y;
		float	z;
		float	w;
	};
	float					array[4];
}	t_vec3;

t_vec3	vec3_new(float x, float y, float z);
t_vec3	normalize_vec3(t_vec3 vec3);

#endif
