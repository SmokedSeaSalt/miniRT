/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egrisel <egrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 10:04:11 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/09/30 11:24:02 by egrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "parsing.h"
#include "consts.h"

static void	hook(void *param)
{
	t_scene	*scene;

	scene = (t_scene*)param;
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

	if (argc != 2)
		return (printf("Incorrect amount of arguments"), 1);
	if (parse_file(&scene, argv[1]) == -1)
		return (printf("Parsing error"), 1);
	if (init_mlx(&scene))
		return (1); // cleanup scene
	mlx_loop(scene.mlx);
	
}
