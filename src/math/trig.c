/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trig.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:47:46 by egrisel           #+#    #+#             */
/*   Updated: 2025/10/21 16:17:41 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "consts.h"

/// @brief calculate rad from degree.
/// @param angle_in_deg
/// @return	angle in rad.
float	deg_to_rad(int angle_in_deg)
{
	return (angle_in_deg * PI / 180.0f);
}
