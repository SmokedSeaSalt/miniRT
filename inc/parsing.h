/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:09:10 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/09/18 17:17:36 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

int	count_arguments(char **line);
int	color_out_of_range(t_color color);
int	orientation_out_of_range(t_vec3 orientation);
int orientation_all_zero(t_vec3 orientation);
t_color fill_color(char *r_str, char *g_str, char *b_str);
t_vec3 fill_vec3(char *x_str, char *y_str, char *z_str);

#endif
