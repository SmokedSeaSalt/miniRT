/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 11:14:25 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/10/24 11:23:09 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "helpers.h"
#include "structs.h"
#include "MLX42.h"
#include <stdlib.h>

/// @brief update and display the fps counter
/// @brief when scene.render_info.fpscounter flag is set.
/// @param scene
void	update_fpscounter(t_scene *scene)
{
	static	mlx_image_t *fps_image = NULL;
	char	*fps_str;

	if (fps_image)
	{
		mlx_delete_image(scene->mlx, fps_image);
		fps_image = NULL;
	}
	if (scene->render_info.fpscounter == 1)
	{
		fps_str = ft_ftoa(1 / scene->mlx->delta_time);
		if (fps_str == NULL)
			return ;
		fps_image = mlx_put_string(scene->mlx, fps_str, 25, 25);
		free(fps_str);
	}
}

//void update_debugwindow(t_scene *scene)
//{
//	static	mlx_image_t *fps_image[8] = NULL;


//}