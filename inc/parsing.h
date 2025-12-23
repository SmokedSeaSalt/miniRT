/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:09:10 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/12/23 14:13:18 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "structs.h"

////////////////////////////////////////////////////////////////////////////////
// file_handling															  //
////////////////////////////////////////////////////////////////////////////////

int			is_valid_extension(char *str);
int			parse_file(t_scene *scene, char *filename);
int			open_file(char *filename);

////////////////////////////////////////////////////////////////////////////////
// parsing helpers															  //
////////////////////////////////////////////////////////////////////////////////

int			process_line(t_scene *scene, char *line);
int			select_element(t_scene *scene, char **line);
int			count_arguments(char **line);
int			color_out_of_range(t_color color);
int			orientation_out_of_range(t_vec3 orientation);
int			orientation_all_zero(t_vec3 orientation);
t_vec3		fill_vec3(char *x_str, char *y_str, char *z_str);
void		add_object_to_back(t_object **list, t_object *new);
int			parse_color(t_color *color, char *str);
int			parse_orig(t_vec3 *orig, char *str);
int			parse_normal_vector(t_vec3 *vec, char *str);
int			parse_ratio(float *ratio, char *str);
int			parse_fov(float *fov, char *str);

////////////////////////////////////////////////////////////////////////////////
// parse_structs															  //
////////////////////////////////////////////////////////////////////////////////

int			new_ambient_struct(t_scene *scene, char **line);
int			new_camera_struct(t_scene *scene, char **line);
int			new_cylinder_struct(t_scene *scene, char **line);
int			new_light_struct(t_scene *scene, char **line);
int			new_plane_struct(t_scene *scene, char **line);
int			new_sphere_struct(t_scene *scene, char **line);

////////////////////////////////////////////////////////////////////////////////
// parse maps																  //
////////////////////////////////////////////////////////////////////////////////

void		get_uv_map(char *line, t_uv_map *map);
void		get_bump_map(char *line, t_uv_map *map);

#endif
