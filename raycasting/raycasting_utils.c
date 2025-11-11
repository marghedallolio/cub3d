/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 11:07:51 by francema          #+#    #+#             */
/*   Updated: 2025/11/11 11:19:26 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	compute_wall_distance(t_ray *ray, t_player *p)
{
	// If the wall was hit on an X-side (a vertical wall),
	// we use the X-direction to calculate the perpendicular distance.
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - p->pos_x
				+ (1 - ray->step_x) / 2) / ray->ray_dir_x;
	else
		// Otherwise, the wall was hit on a Y-side (a horizontal wall),
		// so we use the Y-direction for the distance calculation.
		ray->perp_wall_dist = (ray->map_y - p->pos_y
				+ (1 - ray->step_y) / 2) / ray->ray_dir_y;
}


