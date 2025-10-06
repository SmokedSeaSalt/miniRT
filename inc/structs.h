/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:09:17 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/10/06 13:36:07 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
//generics
# include "MLX42.h"

/// @brief union for adaptable vector operations
/// @param float v for +-*/ operations on vector	-> vec3_1.v - vec3_2.v
/// @param struct for x y z access					-> vec3.x
/// @param float array[4] for array like access 	-> vec3.array[1]
typedef union u_vec3
{
	float v	__attribute__	((vector_size(16)));
	struct
	{
		float	x;
		float	y;
		float	z;
		float	w;
	};
	float					array[4];
}	t_vec3;

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

typedef struct s_window_info
{
	int		width;
	int		height;
	float	aspect_ratio;
}	t_window_info;

typedef struct s_camera
{
	t_vec3			coords;
	t_vec3			orientation;
	float			fov_rad;
	float			fov_scale;
	t_window_info	window_info;
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
	float		radius;
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
	float		radius;
	float		height;
	t_color		color;
}	t_cylinder;

typedef enum e_obj_type
{
	SPHERE,
	PLANE,
	CYLINDER
}	t_obj_type;

typedef struct s_pixel_result
{
	int				is_hit;
	float			hit_dist;
	struct s_object	*object;
	t_vec3			normal_at;
}	t_pixel_result;

typedef struct s_ray
{
	t_vec3			orig;
	t_vec3			vec3;
	t_pixel_result	results;
}	t_ray;

//list of obj
typedef struct s_object
{
	t_obj_type		type;
	void			*data;
	struct s_object	*next;
// Function pointers for object-specific operations
	int				(*is_hit)(t_ray *ray, void *object_data);
	float			(*get_hit_dist)(t_ray *ray, void *object_data);
	void			(*get_hit_data)(t_ray *ray, void *object_data);
}	t_object;

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
