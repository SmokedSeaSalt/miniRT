/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 15:39:45 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/12/23 15:49:58 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"
#include "structs.h"
#include "helpers.h"
#include "consts.h"
#include "MLX42.h"
#include <math.h>

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
	mlx_image_to_window(scene->mlx, scene->g_img, 0, 0);
	mlx_key_hook(scene->mlx, &handle_inputs, scene);
	mlx_loop_hook(scene->mlx, &hook, scene);
	return (0);
}

void	init_settings(t_scene *scene)
{
	scene->render_info.render_hit = &display_default;
	scene->render_info.render_miss = &display_black;
	scene->window_info.fpscounter = 0;
	scene->window_info.max_render_depth = 7;
	scene->window_info.render_depth = 7;
	scene->window_info.render_y = 0;
	scene->window_info.start_time = get_time_in_ms();
}

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