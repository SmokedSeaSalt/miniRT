/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_inc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egrisel <egrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 15:53:33 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/10/02 11:26:06 by egrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_INC_H
# define MATH_INC_H
# include "structs.h"

t_vec3	vec3_new(float x, float y, float z);
t_vec3	vec3_normalize(t_vec3 vec3);
float	vec3_dot(t_vec3 a, t_vec3 b);
t_vec3	vec3_cross(t_vec3 a, t_vec3 b);
float	vec3_length(t_vec3 vec3);

float	deg_to_rad(int angle_in_deg);

float	sphere_intersects(t_ray ray, t_sphere sphere);

#endif
