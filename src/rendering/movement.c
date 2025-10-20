/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 11:26:56 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/10/20 14:38:21 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "consts.h"
#include "structs.h"
#include "math_inc.h"

/// @brief move the camera in the orientation axis.
/// @param camera		camera struct to adjust
/// @param direction	1 for forwards, -1 for backwards
void move_cam_direction(t_camera *camera, int direction)
{
	camera->coords.v = camera->coords.v + \
(camera->orientation.v * (float)direction * STEP_SIZE);
}

/// @brief move the camera in the orientation axis.
/// @param camera		camera struct to adjust
/// @param direction	1 for right, -1 for left
void move_horizontal(t_camera *camera, int direction)
{
	t_vec3	move_dir;
	t_vec3	world_up;

	world_up = vec3_new(0, 0, 1);
	if (direction == 1)
		move_dir = vec3_cross(world_up, camera->orientation);
	else
		move_dir = vec3_cross(camera->orientation, world_up);
	move_dir = vec3_normalize(move_dir);
	camera->coords.v = camera->coords.v + \
(move_dir.v * STEP_SIZE);
}

void rotate_camera_up_down(t_camera *camera, int direction)
{
	t_vec3	tmp;

	tmp = camera->orientation;
	tmp.z = tmp.z + ((float)direction * UPDOWN_ROT);
	tmp = vec3_normalize(tmp);
	camera->orientation = tmp;
}