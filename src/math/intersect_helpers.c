/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:49:59 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/10/03 11:55:48 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

/// @brief calculates the closest distance in FRONT of the camera
/// @param distance1
/// @param distance2
/// @return	the smallest positive distance
/// @return	if all hits are negative distance return
float	decide_closest_distance(float distance1, float distance2)
{
	if (distance1 > 0.0f &&  distance2 > 0.0f)
		return (fmin(distance1, distance2));
	else if (distance1 > 0.0f && distance2 < 0.0f)
		return (distance1);
	else if (distance2 > 0.0f && distance1 < 0.0f)
		return (distance2);
	return (distance1);
}
