/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consts.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 11:14:45 by egrisel           #+#    #+#             */
/*   Updated: 2025/11/06 14:29:29 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTS_H
# define CONSTS_H

# ifndef WIDTH
#  define WIDTH 1920
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

# define N_ARGS_ERR "Incorrect amount or arguments"
# define RANGE_ERR "Out of range"
# define VEC_0_ERR "Orientation can not be all zero"
# define N_ELEMENTS_ERR "Does not support multiple elements"

#endif