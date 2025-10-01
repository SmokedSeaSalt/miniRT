/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egrisel <egrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 10:04:11 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/10/01 16:41:44 by egrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "parsing.h"
#include "consts.h"
#include "rendering.h"
#include "libft.h"
#include <stdio.h> //to use printf

// change later for variable window size
void	set_window_info_struct(t_window_info *window_info)
{
	window_info->width = WIDTH;
	window_info->height = HEIGHT;
	window_info->aspect_ratio = WIDTH / HEIGHT;
}

void	set_camera_struct(t_camera *camera)
{
	camera->fov_scale = tanf(camera->fov_rad / 2);
}

static void	hook(void *param)
{
	t_scene	*scene;

	scene = (t_scene*)param;
	set_window_info_struct(&(scene->camera->window_info));
	set_camera_struct(scene->camera);
	// draw_black(mlx_info);
	render(scene);
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
	mlx_loop_hook(scene->mlx, &hook, scene);

	return (0);
}

int	main(int argc, char *argv[])
{
	t_scene		scene;

	ft_bzero(&scene, sizeof(t_scene));
	if (argc != 2)
		return (printf("Incorrect amount of arguments"), 1);
	if (parse_file(&scene, argv[1]) == -1)
		return (printf("Parsing error"), 1);
	if (init_mlx(&scene))
		return (1); // cleanup scene
	mlx_loop(scene.mlx);
	
}
