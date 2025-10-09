/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_inc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 15:53:33 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/10/09 12:40:25 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_INC_H
# define MATH_INC_H
# include "structs.h"

// vec3
t_vec3	vec3_new(float x, float y, float z);
t_vec3	vec3_normalize(t_vec3 vec3);
float	vec3_dot(t_vec3 a, t_vec3 b);
t_vec3	vec3_cross(t_vec3 a, t_vec3 b);
float	vec3_length(t_vec3 vec3);
float	vec3_sum_components(t_vec3 vec3);

// vector3_rotate
t_vec3	vec3_rotate_around_z(t_vec3 *vec3, float z_rad);

// vec3_math
float	get_angle_between_vec3(t_vec3 *vec3_a, t_vec3 *vec3_b);
t_vec3	get_vec3_betweem_two_points(t_vec3 *a, t_vec3 *b);
int		is_vec3_angle_acute(t_vec3 *a, t_vec3 *b);

// vec4
t_vec4	vec4_new(float x, float y, float z, float w);
float	vec4_sum_components(t_vec4 vec4);

// mat3
t_mat3	mat3_new(t_vec3 *row_0, t_vec3 *row_1, t_vec3 *row_2);
t_vec3	mat3_mul_vec3(t_mat3 *mat3, t_vec3 *input_vec3);

// mat4
t_mat4	mat4_new(t_vec4 *row_0, t_vec4 *row_1, t_vec4 *row_2, t_vec4 *row_3);
t_vec4	mat4_mul_vec4(t_mat4 *mat4, t_vec4 *input_vec4);

float	deg_to_rad(int angle_in_deg);

float	decide_closest_distance(float distance1, float distance2);

int		is_hit_sphere(t_ray *ray, t_sphere *sphere);
float	sphere_intersects(t_ray *ray, t_sphere *sphere);
float	get_hit_dist_sphere(t_ray *ray, t_sphere *sphere);
t_vec3	sphere_normal_at(t_ray *ray, t_sphere *sphere);

// plane
int		is_hit_plane(t_ray *ray, t_plane *plane);
float	git_hit_dist_plane(t_ray *ray, t_plane *plane);

#endif
