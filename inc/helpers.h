/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:08:58 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/12/23 15:54:42 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPERS_H
# define HELPERS_H

# include "structs.h"

char		**ft_split_set(char const *s, char const *set);
void		*ft_free_split(char **ret);
double		ft_atof(const char *str);
char		*ft_ftoa(double val);

long long	get_time_in_ms(void);
long long	get_timestamp(long long start_time);

void		cleanup_scene(t_scene *scene);

int			init_mlx(t_scene *scene);
void		init_settings(t_scene *scene);
void		set_window_info_struct(t_window_info *window_info);
void		set_fov_scale(t_window_info *window_info, t_camera *camera);

void		update_framename(t_scene *scene);

void		handle_inputs(mlx_key_data_t keydata, void *param);

#endif
