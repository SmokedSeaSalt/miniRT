/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:09:54 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/09/19 12:38:25 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "parsing.h"
#include "libft.h"

//TODO
//add checking for multiple where only one may exist
//error handling
//make unit tests

//todo in new_x_struct.
//malloc the struct, fill it
//fill succesfull -> add to back object list
//fill failed -> dont add to list (maybe even exit? or just ignore that obj)
select_element(t_scene *scene, char **line)
{
	if (ft_strncmp(line[1], "A", ft_strlen(line[1])) == 0)
		return(new_ambient_struct(scene, line));
	if (ft_strncmp(line[1], "C", ft_strlen(line[1])) == 0)
		return(new_camera_struct(scene, line));
	if (ft_strncmp(line[1], "L", ft_strlen(line[1])) == 0)
		return(new_light_struct(scene, line));
	if (ft_strncmp(line[1], "sp", ft_strlen(line[1])) == 0)
		return(new_sphere_struct(scene, line));
	if (ft_strncmp(line[1], "pl", ft_strlen(line[1])) == 0)
		return(new_plane_struct(scene, line));
	if (ft_strncmp(line[1], "cy", ft_strlen(line[1])) == 0)
		return(new_cylinder_struct(scene, line));
	printf("Parsing: Element %s not found", line[1]);
	return(1);
}

