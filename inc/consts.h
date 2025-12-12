/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consts.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egrisel <egrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 11:14:45 by egrisel           #+#    #+#             */
/*   Updated: 2025/12/12 15:25:04 by egrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTS_H
# define CONSTS_H

# ifndef WIDTH
#  define WIDTH 1920
# endif

# ifndef SCREEN_FPS
#  define SCREEN_FPS 60
# endif

# ifndef HEIGHT
#  define HEIGHT 1080
# endif

# define PI 3.14159265358979323846f

# ifndef Z_ROTATION_RAD
#  define Z_ROTATION_RAD 0.175
# endif

# ifndef UPDOWN_ROT
#  define UPDOWN_ROT 0.1
# endif

# ifndef STEP_SIZE
#  define STEP_SIZE 0.1f
# endif

# ifndef CHECKER_U_NUM
#  define CHECKER_U_NUM 10
# endif

# ifndef CHECKER_V_NUM
#  define CHECKER_V_NUM 10
# endif

# ifndef PLANE_UV_WIDTH
#  define PLANE_UV_WIDTH 5
# endif

# ifndef PLANE_UV_HEIGHT
#  define PLANE_UV_HEIGHT 5
# endif


# define N_ARGS_ERR "Incorrect amount or arguments"
# define RANGE_ERR "Out of range"
# define VEC_0_ERR "Orientation can not be all zero"
# define N_ELEMENTS_ERR "Does not support multiple elements"

#endif