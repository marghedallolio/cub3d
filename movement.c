/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:59:01 by francema          #+#    #+#             */
/*   Updated: 2025/12/04 15:34:11 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	move(t_ray *ray, int keycode)
{
	if (keycode == W)
	{
		ray->p_pos.x += ray->p_dir.x * ray->move_speed;
		ray->p_pos.y += ray->p_dir.y * ray->move_speed;
	}
	else if (keycode == A)
	{
		ray->p_pos.x -= ray->plane.x * ray->move_speed;
		ray->p_pos.y -= ray->plane.y * ray->move_speed;
	}
	else if (keycode == S)
	{
		ray->p_pos.x -= ray->p_dir.x * ray->move_speed;
		ray->p_pos.y -= ray->p_dir.y * ray->move_speed;
	}
	else if (keycode == D)
	{
		ray->p_pos.x += ray->plane.x * ray->move_speed;
		ray->p_pos.y += ray->plane.y * ray->move_speed;
	}
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
	if (g->mov_key)
		move(&g->ray, g->mov_key);
	if (g->rot_key)
	{
		if (g->rot_key == LEFT_ARROW)
			key_rotate(&g->ray, -ROT_SPEED);
		if (g->rot_key == RIGTH_ARROW)
			key_rotate(&g->ray, ROT_SPEED);
	}
}

int	handle_key_press(int keycode, t_game *g)
{
	if (keycode == ESC)
		close_window(g);
	if (keycode == W || keycode == A
		|| keycode == S || keycode == D)
		g->mov_key = keycode;
	if (keycode == LEFT_ARROW || keycode == RIGTH_ARROW)
		g->rot_key = keycode;
	return (0);
}

int	handle_key_release(int keycode, t_game *g)
{
	if (keycode == W || keycode == A
		|| keycode == S || keycode == D)
		g->mov_key = 0;
	if (keycode == LEFT_ARROW || keycode == RIGTH_ARROW)
		g->rot_key = 0;
	return (0);
}
