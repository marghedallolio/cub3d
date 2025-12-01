/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vectors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:57:17 by francema          #+#    #+#             */
/*   Updated: 2025/12/01 17:36:02 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

//RAYs INIT
void	get_dir_vector(char face, t_ray *ray)
{
	if (face == 'N')
	{
		ray->p_dir.x = 0;
		ray->p_dir.y = -1;
	}
	else if (face == 'S')
	{
		ray->p_dir.x = 0;
		ray->p_dir.y = 1;
	}
	else if (face == 'E')
	{
		ray->p_dir.x = 1;
		ray->p_dir.y = 0;
	}
	else if (face == 'W')
	{
		ray->p_dir.x = -1;
		ray->p_dir.y = 0;
	}
}

/*(i * 2*PI) / 3600 radiants conversion */
void	init_lookup_table(t_ray *ray)
{
	double	angle;
	int		i;

	i = 0;
	ray->table_size = TABLE_SIZE;
	while (i < TABLE_SIZE)
	{
		angle = (i * 2.0 * PI) / TABLE_SIZE;
		ray->sin_arr[i] = sin(angle);
		ray->cos_arr[i] = cos(angle);
		i++;
	}
}

bool	init_vector(t_info_map *info, t_ray *ray)
{
	ray->p_pos = (t_vctr){0};
	ray->p_dir = (t_vctr){0};
	ray->plane = (t_vctr){0};
	ray->p_pos.x = info->p_x;
	ray->p_pos.y = info->p_y;
	get_dir_vector(info->facing, ray);
	ray->plane.x = -ray->p_dir.y * 0.66;
	ray->plane.y = ray->p_dir.x * 0.66;
	ray->move_speed = MOV_SPEED;
	init_lookup_table(ray);
	return (true);
}
