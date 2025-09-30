/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egrisel <egrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:09:17 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/09/30 11:13:33 by egrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
//generics
#include "math_inc.h"
#include "MLX42.h"

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

//scene objects

typedef struct s_ambient
{
	float	ratio;
	t_color	color;
}	t_ambient;

typedef struct s_camera
{
	t_vec3		coords;
	t_vec3		orientation;
	int			fov;
}	t_camera;

typedef struct s_light
{
	t_vec3		coords;
	float		brightness;
	t_color		color;
}	t_light;

typedef struct s_sphere
{
	t_vec3		coords;
	float		diameter;
	t_color		color;
}	t_sphere;

typedef struct s_plane
{
	t_vec3		coords;
	t_vec3		orientation;
	t_color		color;
}	t_plane;

typedef struct s_cylinder
{
	t_vec3		coords;
	t_vec3		orientation;
	float		diameter;
	float		height;
	t_color		color;
}	t_cylinder;

typedef enum e_obj_type
{
	SPHERE,
	PLANE,
	CYLINDER
} t_obj_type;

//list of obj
typedef struct s_object
{
	t_obj_type		type;
	void			*data;
	struct s_object	*next;
} t_object;

typedef struct s_scene
{
	t_ambient	*ambient;
	t_camera	*camera;
	t_light		*light;
	t_object	*objects;
	mlx_t		*mlx;
	mlx_image_t	*g_img;
}	t_scene;

#endif
