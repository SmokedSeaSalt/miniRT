/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 15:50:34 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/12/23 15:56:45 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "consts.h"
#include "MLX42.h"
#include "structs.h"
#include "rendering.h"
#include "helpers.h"
#include "math_inc.h"

void	input_movement(mlx_key_data_t keydata, t_scene *scene)
{
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		scene->camera->orientation = vec3_rotate_around_z(
				&scene->camera->orientation, Z_ROTATION_RAD);
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		scene->camera->orientation = vec3_rotate_around_z(
				&scene->camera->orientation, -Z_ROTATION_RAD);
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_RELEASE)
		rotate_camera_up_down(scene->camera, 1);
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_RELEASE)
		rotate_camera_up_down(scene->camera, -1);
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_RELEASE)
		scene->camera->coords.z += STEP_SIZE;
	if (keydata.key == MLX_KEY_LEFT_SHIFT && keydata.action == MLX_RELEASE)
		scene->camera->coords.z -= STEP_SIZE;
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_RELEASE)
		move_cam_direction(scene->camera, 1);
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_RELEASE)
		move_cam_direction(scene->camera, -1);
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE)
		move_horizontal(scene->camera, 1);
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_RELEASE)
		move_horizontal(scene->camera, -1);
}

void	input_render_types(mlx_key_data_t keydata, t_scene *scene)
{
	if (keydata.key == MLX_KEY_1 && keydata.action == MLX_RELEASE)
		scene->render_info.render_hit = &display_default;
	if (keydata.key == MLX_KEY_2 && keydata.action == MLX_RELEASE)
		scene->render_info.render_hit = &display_normal;
	if (keydata.key == MLX_KEY_3 && keydata.action == MLX_RELEASE)
		scene->render_info.render_hit = &display_xyz;
	if (keydata.key == MLX_KEY_4 && keydata.action == MLX_RELEASE)
		scene->render_info.render_hit = &display_light_intensity;
	if (keydata.key == MLX_KEY_5 && keydata.action == MLX_RELEASE)
		scene->render_info.render_hit = &display_distance;
	if (keydata.key == MLX_KEY_8 && keydata.action == MLX_RELEASE)
		scene->render_info.render_miss = &display_horizon_blue_sky;
	if (keydata.key == MLX_KEY_9 && keydata.action == MLX_RELEASE)
		scene->render_info.render_miss = &display_black;
	if (keydata.key == MLX_KEY_0 && keydata.action == MLX_RELEASE)
		scene->render_info.render_miss = &display_white;
}

void	handle_inputs(mlx_key_data_t keydata, void *param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	if (keydata.action == MLX_RELEASE)
	{
		scene->window_info.render_depth = scene->window_info.max_render_depth;
		scene->window_info.render_y = 0;
		scene->window_info.start_time = get_time_in_ms();
	}
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
		mlx_close_window(scene->mlx);
	if (keydata.key == MLX_KEY_F && keydata.action == MLX_RELEASE)
		scene->window_info.fpscounter = !scene->window_info.fpscounter;
	input_movement(keydata, scene);
	input_render_types(keydata, scene);
}
