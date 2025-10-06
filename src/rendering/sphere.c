/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 13:42:02 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/10/06 14:10:38 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "math_inc.h"

void get_hit_data_sphere(t_ray *ray, t_sphere *sphere)
{
	ray->results.normal_at = sphere_normal_at(ray, sphere);

}