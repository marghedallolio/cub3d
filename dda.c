/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 17:00:53 by francema          #+#    #+#             */
/*   Updated: 2025/12/04 15:33:34 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/* Determina la direzione dei passi (step_x, step_y)
e le distanze iniziali ai bordi delle celle (side_dist) per l'algoritmo DDA*/
void	prepare_steps(t_ray *ray)
{
	if (ray->ray_dir.x < 0)
	{
		ray->step_x = -1;
		ray->side_dist.x = (ray->p_pos.x - ray->map_x) * ray->delta_dist.x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist.x = (ray->map_x + 1.0 - ray->p_pos.x)
			* ray->delta_dist.x;
	}
	if (ray->ray_dir.y < 0)
	{
		ray->step_y = -1;
		ray->side_dist.y = (ray->p_pos.y - ray->map_y) * ray->delta_dist.y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist.y = (ray->map_y + 1.0 - ray->p_pos.y)
			* ray->delta_dist.y;
	}
}

/*in base alla colonna x si calcola dove si colloca il raggio sul FOV,
 e la distanza x e y al prossimo muro*/
void	prepare_ray(t_ray *ray, int x)
{
	ray->cam_len = ((x * 2.0) / W_W) - 1.0;
	ray->ray_dir.x = ray->p_dir.x + ray->plane.x * ray->cam_len;
	ray->ray_dir.y = ray->p_dir.y + ray->plane.y * ray->cam_len;
	ray->map_x = (int)ray->p_pos.x;
	ray->map_y = (int)ray->p_pos.y;
	if (ray->ray_dir.x == 0)
		ray->delta_dist.x = 1e30;
	else
		ray->delta_dist.x = fabs(1 / ray->ray_dir.x);
	if (ray->ray_dir.y == 0)
		ray->delta_dist.y = 1e30;
	else
		ray->delta_dist.y = fabs(1 / ray->ray_dir.y);
	prepare_steps(ray);
}

void	take_step(t_ray *ray)
{
	if (ray->side_dist.x < ray->side_dist.y)
	{
		ray->side_dist.x += ray->delta_dist.x;
		ray->map_x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->side_dist.y += ray->delta_dist.y;
		ray->map_y += ray->step_y;
		ray->side = 1;
	}
}

void	perform_dda(t_ray *ray, t_game *g)
{
	int	hit;
	int	rendered;

	hit = 0;
	rendered = 0;
	while (hit == 0 && rendered <= 30)
	{
		take_step(ray);
		if (ray->map_x < 0 || ray->map_x >= g->map_w
			|| ray->map_y < 0 || ray->map_y >= g->map_h)
		{
			rendered++;
			if (rendered > 30)
				ray->side = -1;
			continue ;
		}
		if (g->map[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
	if (ray->side == 0)
		ray->perpen_dist = (ray->map_x - ray->p_pos.x
				+ (1 - ray->step_x) / 2) / ray->ray_dir.x;
	else
		ray->perpen_dist = (ray->map_y - ray->p_pos.y
				+ (1 - ray->step_y) / 2) / ray->ray_dir.y;
}
