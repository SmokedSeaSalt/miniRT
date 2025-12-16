/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:09:17 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/12/16 16:56:05 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
//generics
# include "MLX42.h"

////////////////////////////////////////////////////////////////////////////////
// vectors																	  //
////////////////////////////////////////////////////////////////////////////////

/// @brief union for adaptable 3d vector operations(w is empty for optimization)
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
	struct
	{
		float	r;
		float	g;
		float	b;
		float	i;
	};
	float					array[4];
}	t_vec3;

/// @brief union for adaptable 4d vector operations
/// @param float v for +-*/ operations on vector	-> vec3_1.v - vec3_2.v
/// @param struct for x y z w access				-> vec3.x
/// @param float array[4] for array like access 	-> vec3.array[1]
typedef union u_vec4
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
}	t_vec4;

/// @brief union for 4x4 matrix
typedef union u_mat4
{
	struct
	{
		t_vec4	row_0;
		t_vec4	row_1;
		t_vec4	row_2;
		t_vec4	row_3;
	};
	float	array[16];
	float	m[4][4];
}	t_mat4;

/// @brief union for 3x3 matrix
typedef union u_mat3
{
	struct
	{
		t_vec3	row_0;
		t_vec3	row_1;
		t_vec3	row_2;
	};
	float	array[12];
	float	m[3][3];
}	t_mat3;

////////////////////////////////////////////////////////////////////////////////
// element members															  //
////////////////////////////////////////////////////////////////////////////////

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef enum e_obj_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	ENDCAPTOP,
	ENDCAPBOT,
}	t_obj_type;

typedef struct s_uv
{
	float	u;
	float	v;
}	t_uv;

typedef enum e_uv_type
{
	CHECKERBOARD,
	PNG,
}	t_uv_type;

typedef struct s_uv_map
{
	t_uv_type		type;
	mlx_texture_t	*png;
}	t_uv_map;

////////////////////////////////////////////////////////////////////////////////
// scene elements															  //
////////////////////////////////////////////////////////////////////////////////

typedef struct s_scene	t_scene;
typedef struct s_ray	t_ray;

typedef struct s_ambient
{
	float	ratio;
	t_color	color;
	t_vec3	intensity;
}	t_ambient;

typedef struct s_camera
{
	t_vec3			coords;
	t_vec3			orientation;
	float			fov_rad;
}	t_camera;

typedef struct s_lights
{
	t_vec3			coords;
	float			brightness;
	t_vec3			color_brightness;
	t_color			color;
	struct s_lights	*next;
}	t_lights;

typedef struct s_sphere
{
	t_vec3		coords;
	float		diameter;
	float		radius;
	t_color		color;
	t_uv_map	*uv_color;
	t_uv_map	*bump;
}	t_sphere;

typedef struct s_plane
{
	t_vec3		coords;
	t_vec3		normal;
	t_color		color;
	t_uv_map	*uv_color;
	t_uv_map	*bump;
}	t_plane;

typedef struct s_cylinder
{
	t_vec3		coords;
	t_vec3		orientation;
	float		diameter;
	float		radius;
	float		height;
	t_color		color;
	t_uv_map	*uv_color;
	t_uv_map	*bump;
}	t_cylinder;

typedef struct s_endcap
{
	t_vec3		coords;
	t_vec3		normal;
	float		diameter;
	float		radius;
	t_color		color;
	t_uv_map	*uv_color;
	t_uv_map	*bump;
}	t_endcap;

typedef struct s_object
{
	t_obj_type		type;
	void			*data;
	struct s_object	*next;
// Function pointers for object-specific operations
	int				(*is_hit)(t_ray *ray, void *object_data);
	float			(*get_hit_dist)(t_ray *ray, void *object_data);
	void			(*get_hit_data)(t_ray *ray, void *object_data,
			t_scene *scene);
}	t_object;

////////////////////////////////////////////////////////////////////////////////
// rays																		  //
////////////////////////////////////////////////////////////////////////////////

typedef struct s_pixel_result
{
	int			is_hit;
	float		hit_dist;
	t_vec3		light_intensity;
	t_vec3		specular_intensity;
	t_object	*object;
	t_vec3		hit_normal;
	t_color		obj_color;
	t_uv		uv_coords;
	t_uv_map	*uv_color;
	t_uv_map	*bump;
}	t_pixel_result;

struct s_ray
{
	t_vec3			orig;
	t_vec3			vec3;
	t_pixel_result	results;
};

////////////////////////////////////////////////////////////////////////////////
// scene																	  //
////////////////////////////////////////////////////////////////////////////////

typedef struct s_window_info
{
	int			width;
	int			height;
	float		aspect_ratio;
	float		fov_scale;
	int			render_depth;
	int			max_render_depth;
	int			render_y;
	long long	start_time;
}	t_window_info;

typedef struct s_render_info
{
	void	(*render_hit)(t_ray *ray, int x, int y, t_scene *scene);
	void	(*render_miss)(t_ray *ray, int x, int y, t_scene *scene);
	int		fpscounter;
}	t_render_info;

struct s_scene
{
	t_ambient		*ambient;
	t_camera		*camera;
	t_lights		*lights;
	t_object		*objects;
	mlx_t			*mlx;
	mlx_image_t		*g_img;
	t_render_info	render_info;
	t_window_info	window_info;
};

#endif
