/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_mapping.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egrisel <egrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 12:47:08 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/12/11 16:38:17 by egrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "consts.h"
#include "structs.h"

// get_uv_value()
// {

// }

//if in "black square return color" else return white
t_color	uv_checkerboard(t_uv uv, t_color color)
{
	const int	u2 = uv.u * CHECKER_U_NUM;
	const int	v2 = uv.v * CHECKER_V_NUM;

	if ((u2 + v2) % 2 == 0)
		return (color);
	else
		return ((t_color){.r = 255, .g = 255, .b = 255});
}
