/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 10:04:11 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/11/12 13:40:04 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "parsing.h"
#include "consts.h"
#include "rendering.h"
#include "libft.h"
#include <math.h>
#include <stdio.h> //to use printf
#include <stdlib.h> //to use free
#include "math_inc.h"
#include "helpers.h"

// change later for variable window size
void	set_window_info_struct(t_window_info *window_info)
{
	window_info->width = WIDTH;
	window_info->height = HEIGHT;
	window_info->aspect_ratio = (float)WIDTH / (float)HEIGHT;
}

void	set_fov_scale(t_window_info *window_info, t_camera *camera)
{
	window_info->fov_scale = tanf(camera->fov_rad / 2);
}

void	handle_arrows(mlx_key_data_t keydata, t_scene *scene)
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
	if (keydata.key == MLX_KEY_F && keydata.action == MLX_RELEASE)
		scene->render_info.fpscounter = !scene->render_info.fpscounter;
	handle_arrows(keydata, scene);
}

/// @brief change the rotating moon emoji each frame.
/// @param scene
void	update_framename(t_scene *scene)
{
	static int	i = 0;
	const char	*cycle = "🌕🌔🌓🌒🌑🌘🌗🌖";
	const char	*default_title = "miniRT";
	char		*single_moon;
	char		*title_string;

	single_moon = ft_substr(cycle, i, 4);
	if (single_moon == NULL)
		return ;
	i = (i + 4) % 32;
	title_string = ft_strjoin(default_title, single_moon);
	free(single_moon);
	if (title_string == NULL)
		return ;
	mlx_set_window_title(scene->mlx, title_string);
	free(title_string);
}

static void	hook(void *param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	set_window_info_struct(&(scene->window_info));
	set_fov_scale(&(scene->window_info), scene->camera);
	render_frame(scene);
	update_framename(scene);
	update_fpscounter(scene);
}

int	init_mlx(t_scene *scene)
{
	scene->mlx = mlx_init(WIDTH, HEIGHT, "miniRT", false);
	if (scene->mlx == NULL)
		return (-1);
	scene->g_img = mlx_new_image(scene->mlx, WIDTH, HEIGHT);
	if (scene->g_img == NULL)
	{
		mlx_terminate(scene->mlx);
		return (-1);
	}
	mlx_image_to_window(scene->mlx, scene->g_img, 0, 0); // maybe error handle?
	mlx_key_hook(scene->mlx, &handle_inputs, scene);
	mlx_loop_hook(scene->mlx, &hook, scene);
	return (0);
}

void	init_settings(t_scene *scene)
{
	scene->render_info.render_hit = &display_default;
	scene->render_info.render_miss = &display_black;
	scene->render_info.fpscounter = 1;
	scene->window_info.max_render_depth = 7;
	scene->window_info.render_depth = 7;
	scene->window_info.render_y = 0;
	scene->window_info.start_time = get_time_in_ms();
}

/// @brief general cleanup function that will free all malloced values.
/// @param scene
void cleanup_scene(t_scene *scene)
{
	t_object	*current;
	t_object	*next;
	t_lights	*current_light;
	t_lights	*next_light;

	free(scene->ambient);
	free(scene->camera);
	current_light = scene->lights;
	while (current_light != NULL)
	{
		next_light = current_light->next;
		free(current_light);
		current_light = next_light;
	}
	current = scene->objects;
	while (current != NULL)
	{
		next = current->next;
		free(current->data);
		free(current);
		current = next;
	}
	mlx_delete_image(scene->mlx, scene->g_img);
	mlx_terminate(scene->mlx);
}

int	main(int argc, char *argv[])
{
	t_scene		scene;

	ft_bzero(&scene, sizeof(t_scene));
	if (argc != 2)
		return (printf("Error\nIncorrect amount of arguments"), 1);
	if (parse_file(&scene, argv[1]) == -1)
		return (1);
	if (init_mlx(&scene))
		return (cleanup_scene(&scene), 1);
	init_settings(&scene);
	mlx_loop(scene.mlx);
	cleanup_scene(&scene);
}
