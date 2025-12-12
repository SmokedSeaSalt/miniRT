/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egrisel <egrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 11:42:05 by egrisel           #+#    #+#             */
/*   Updated: 2025/12/12 11:53:24 by egrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H
# include "structs.h"

void	render_frame(t_scene *scene);
t_ray	get_ray(int x, int y, t_camera *camera, t_window_info *window_info);

////////////////////////////////////////////////////////////////////////////////
// light																	  //
////////////////////////////////////////////////////////////////////////////////

void	set_light_hit_angle_and_intensity(t_scene *scene, t_ray *ray);

////////////////////////////////////////////////////////////////////////////////
// sphere																	  //
////////////////////////////////////////////////////////////////////////////////

void	get_hit_data_sphere(t_ray *ray, t_sphere *sphere, t_scene *scene);

////////////////////////////////////////////////////////////////////////////////
// plane																	  //
////////////////////////////////////////////////////////////////////////////////

void	get_hit_data_plane(t_ray *ray, t_plane *plane, t_scene *scene);

////////////////////////////////////////////////////////////////////////////////
// cylinder																	  //
////////////////////////////////////////////////////////////////////////////////

int		is_hit_cylinder(t_ray *ray, t_cylinder *cylinder);
float	get_hit_dist_cylinder(t_ray *ray, t_cylinder *cylinder);
void	get_hit_data_cylinder(t_ray *ray, t_cylinder *cylinder, t_scene *scene);

////////////////////////////////////////////////////////////////////////////////
// endcap																	  //
////////////////////////////////////////////////////////////////////////////////

int		is_hit_endcap(t_ray *ray, t_endcap *endcap);
float	get_hit_dist_endcap(t_ray *ray, t_endcap *endcap);
void	get_hit_data_endcap(t_ray *ray, t_endcap *endcap, t_scene *scene);

////////////////////////////////////////////////////////////////////////////////
// camera movement															  //
////////////////////////////////////////////////////////////////////////////////

void	move_cam_direction(t_camera *camera, int direction);
void	move_horizontal(t_camera *camera, int direction);
void	rotate_camera_up_down(t_camera *camera, int direction);

////////////////////////////////////////////////////////////////////////////////
// display_hit_modes														  //
////////////////////////////////////////////////////////////////////////////////

void	display_normal(t_ray *ray, int x, int y, t_scene *scene);
void	display_xyz(t_ray *ray, int x, int y, t_scene *scene);
void	display_default(t_ray *ray, int x, int y, t_scene *scene);
void	display_light_intensity(t_ray *ray, int x, int y, t_scene *scene);
void	display_distance(t_ray *ray, int x, int y, t_scene *scene);

////////////////////////////////////////////////////////////////////////////////
// display_miss_modes														  //
////////////////////////////////////////////////////////////////////////////////

void	display_black(t_ray *ray, int x, int y, t_scene *scene);
void	display_white(t_ray *ray, int x, int y, t_scene *scene);
void	display_horizon_blue_sky(t_ray *ray, int x, int y, t_scene *scene);

////////////////////////////////////////////////////////////////////////////////
// debug_window																  //
////////////////////////////////////////////////////////////////////////////////

void	update_fpscounter(t_scene *scene);

////////////////////////////////////////////////////////////////////////////////
// uv_mapping																  //
////////////////////////////////////////////////////////////////////////////////

t_color	uv_checkerboard(t_uv uv, t_color color);
t_color	get_uv_value_png(t_uv uv, mlx_texture_t *uv_map);
t_uv	get_sphere_uv(t_ray *ray, t_sphere *sphere);


#endif