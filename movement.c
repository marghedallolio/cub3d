/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:59:01 by francema          #+#    #+#             */
/*   Updated: 2025/12/04 15:55:31 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	set_dir(t_ray *ray, double *dir_x, double *dir_y, int keycode)
{
	if (keycode == W)
	{
		*dir_x = ray->p_dir.x;
		*dir_y = ray->p_dir.y;
	}
	else if (keycode == S)
	{
		*dir_x = -ray->p_dir.x;
		*dir_y = -ray->p_dir.y;
	}
	else if (keycode == A)
	{
		*dir_x = -ray->plane.x;
		*dir_y = -ray->plane.y;
	}
	else if (keycode == D)
	{
		*dir_x = ray->plane.x;
		*dir_y = ray->plane.y;
	}
}

void	move(t_ray *ray, t_game *g, int keycode)
{
	double	dir_x;
	double	dir_y;
	double	new_x;
	double	new_y;

	dir_x = 0;
	dir_y = 0;
	set_dir(ray, &dir_x, &dir_y, keycode);
	new_x = ray->p_pos.x + dir_x * ray->move_speed;
	new_y = ray->p_pos.y + dir_y * ray->move_speed;
	if (g->map[(int)ray->p_pos.y][(int)new_x] != '1')
		ray->p_pos.x = new_x;
	if (g->map[(int)new_y][(int)ray->p_pos.x] != '1')
		ray->p_pos.y = new_y;
}

void	key_rotate(t_ray *ray, double rot)
{
	double	old_dir;
	double	old_plane;
	int		rot_index;
	double	c;
	double	s;

	rot_index = (int)((rot / (2.0 * PI)) * ray->table_size);
	rot_index = (rot_index + ray->table_size) % ray->table_size;
	c = ray->cos_arr[rot_index];
	s = ray->sin_arr[rot_index];
	old_dir = ray->p_dir.x;
	old_plane = ray->plane.x;
	ray->p_dir.x = ray->p_dir.x * c - ray->p_dir.y * s;
	ray->p_dir.y = old_dir * s + ray->p_dir.y * c;
	ray->plane.x = ray->plane.x * c - ray->plane.y * s;
	ray->plane.y = old_plane * s + ray->plane.y * c;
}

void	check_for_movement(t_game *g)
{
	int	mask;

	if (mask & (1 << 0))
		move(&g->ray, g, W);
	if (mask & (1 << 1))
		move(&g->ray, g, S);
	if (mask & (1 << 2))
		move(&g->ray, g, A);
	if (mask & (1 << 3))
		move(&g->ray, g, D);
	if (mask & (1 << 4))
		key_rotate(&g->ray, -ROT_SPEED);
	if (mask & (1 << 5))
		key_rotate(&g->ray, ROT_SPEED);
}


int	handle_key_press(int keycode, t_game *g)
{
	int mask = 0;

	if (keycode == ESC)
		return (close_window(g), 0);
	mask |= (keycode == W) * (1 << 0);
	mask |= (keycode == S) * (1 << 1);
	mask |= (keycode == A) * (1 << 2);
	mask |= (keycode == D) * (1 << 3);
	mask |= (keycode == LEFT_ARROW) * (1 << 4);
	mask |= (keycode == RIGHT_ARROW) * (1 << 5);
	g->key_mask |= mask;
	return 0;
}


int	handle_key_release(int keycode, t_game *g)
{
	int mask = 0;

	mask |= (keycode == W) * (1 << 0);
	mask |= (keycode == S) * (1 << 1);
	mask |= (keycode == A) * (1 << 2);
	mask |= (keycode == D) * (1 << 3);
	mask |= (keycode == LEFT_ARROW) * (1 << 4);
	mask |= (keycode == RIGHT_ARROW) * (1 << 5);
	g->key_mask &= ~mask;
	return 0;
}

