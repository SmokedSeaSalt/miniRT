/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_name.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 15:50:59 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/12/23 15:57:00 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "libft.h"
#include "structs.h"
#include <stdlib.h>

/// @brief change the rotating moon emoji each frame.
/// @param scene
void	update_framename(t_scene *scene)
{
	static int	i = 0;
	const char	*cycle = "🌕🌔🌓🌒🌑🌘🌗🌖";
	const char	*default_title = "miniRT";
	char		*single_moon;
	char		*title_string;

	single_moon = ft_substr(cycle, i, 4);
	if (single_moon == NULL)
		return ;
	i = (i + 4) % 32;
	title_string = ft_strjoin(default_title, single_moon);
	free(single_moon);
	if (title_string == NULL)
		return ;
	mlx_set_window_title(scene->mlx, title_string);
	free(title_string);
}