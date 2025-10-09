/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 11:42:05 by egrisel           #+#    #+#             */
/*   Updated: 2025/10/09 10:19:02 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H
# include "structs.h"

int		render_frame(t_scene *scene);
t_ray	get_ray(int x, int y, t_camera *camera);

// light.c
void	set_light_hit_angle_and_intensity(t_scene *scene, t_ray *ray);

// sphere.c
void	get_hit_data_sphere(t_ray *ray, t_sphere *sphere, t_scene *scene);

// plane.c
void	get_hit_data_plane(t_ray *ray, t_plane *plane, t_scene *scene);

// display_hit_modes
void	display_normal(t_ray *ray, int x, int y, t_scene *scene);
void	display_xyz(t_ray *ray, int x, int y, t_scene *scene);
void	display_default(t_ray *ray, int x, int y, t_scene *scene);

// display_miss_modes
void	display_black(t_ray *ray, int x, int y, t_scene *scene);
void	display_white(t_ray *ray, int x, int y, t_scene *scene);

#endif