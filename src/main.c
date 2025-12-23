/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 10:04:11 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/12/23 15:51:20 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "parsing.h"
#include "consts.h"
#include "rendering.h"
#include "libft.h"
#include <math.h>
#include <stdio.h> //to use printf
#include <stdlib.h> //to use free
#include "math_inc.h"
#include "helpers.h"

int	main(int argc, char *argv[])
{
	t_scene		scene;

	ft_bzero(&scene, sizeof(t_scene));
	if (argc != 2)
		return (printf("Error\nIncorrect amount of arguments"), 1);
	if (parse_file(&scene, argv[1]) == -1)
		return (1);
	if (init_mlx(&scene))
		return (cleanup_scene(&scene), 1);
	init_settings(&scene);
	mlx_loop(scene.mlx);
	cleanup_scene(&scene);
}
