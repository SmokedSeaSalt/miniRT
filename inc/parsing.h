/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:09:10 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/10/06 11:58:18 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "structs.h"

int		is_valid_extension(char *str);
int		parse_file(t_scene *scene, char *filename);
int		open_file(char *filename);
int		process_line(t_scene *scene, char *line);
int		select_element(t_scene *scene, char **line);

int		count_arguments(char **line);
int		color_out_of_range(t_color color);
int		orientation_out_of_range(t_vec3 orientation);
int		orientation_all_zero(t_vec3 orientation);
t_color	fill_color(char *r_str, char *g_str, char *b_str);
t_vec3	fill_vec3(char *x_str, char *y_str, char *z_str);
void	add_object_to_back(t_object **list, t_object *new);

int		new_ambient_struct(t_scene *scene, char **line);
int		new_camera_struct(t_scene *scene, char **line);
int		new_cylinder_struct(t_scene *scene, char **line);
int		new_light_struct(t_scene *scene, char **line);
int		new_plane_struct(t_scene *scene, char **line);
int		new_sphere_struct(t_scene *scene, char **line);

#endif
