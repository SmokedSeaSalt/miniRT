/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 15:13:35 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/12/23 15:28:10 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "rendering.h"
#include "MLX42.h"
#include <stdlib.h>

void	free_lights(t_lights *lights)
{
	t_lights	*current_light;
	t_lights	*next_light;

	current_light = lights;
	while (current_light != NULL)
	{
		next_light = current_light->next;
		free(current_light);
		current_light = next_light;
	}
	return ;
}

void	cleanup_textures(t_texture_list *node)
{
	t_texture_list	*current;
	t_texture_list	*next;

	current = node;
	while (current != NULL)
	{
		next = current->next;
		mlx_delete_texture(current->png);
		free(current);
		current = next;
	}
	return ;
}

/// @brief general cleanup function that will free all malloced values.
/// @param scene
void	cleanup_scene(t_scene *scene)
{
	t_object	*current;
	t_object	*next;

	free(scene->ambient);
	free(scene->camera);
	current = scene->objects;
	while (current != NULL)
	{
		next = current->next;
		free(current->data);
		free(current);
		current = next;
	}
	cleanup_textures(scene->textures);
	scene->window_info.fpscounter = 0;
	update_fpscounter(scene);
	mlx_delete_image(scene->mlx, scene->g_img);
	mlx_terminate(scene->mlx);
}
