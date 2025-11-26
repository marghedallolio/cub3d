/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 13:01:05 by francema          #+#    #+#             */
/*   Updated: 2025/11/25 18:59:26 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	close_window(void)
{
	printf("finestra chiusa!\n");
	ft_malloc(0, 1);
	exit(0);
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

int	handle_key_press(int keycode, t_game *g)
{
	if (keycode == ESC)
		close_window();
	if (keycode == W || keycode == A
		|| keycode == S || keycode == D)
		g->mov_key = keycode;
	// if (keycode == 61)
	// 	g->ray.move_speed += MOV_SPEED;
	// if (keycode == 45 && g->ray.move_speed > 0.05)
	// 	g->ray.move_speed -= MOV_SPEED;
	// if (keycode == 114)
	// 	reset(g->ray);
	if (keycode == LEFT_ARROW || keycode == RIGTH_ARROW)
		g->rot_key = keycode;
	return (0);
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

/* Determina la direzione dei passi (step_x, step_y)
e le distanze iniziali ai bordi delle celle (side_dist) per l'algoritmo DDA*/
void prepare_steps(t_ray *ray)
{
	if (ray->ray_dir.x < 0)
	{
		ray->step_x = -1;
		ray->side_dist.x = (ray->p_pos.x - ray->map_x) * ray->delta_dist.x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist.x = (ray->map_x + 1.0 - ray->p_pos.x) * ray->delta_dist.x;
	}
	if (ray->ray_dir.y < 0)
	{
		ray->step_y = -1;
		ray->side_dist.y = (ray->p_pos.y - ray->map_y) * ray->delta_dist.y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist.y = (ray->map_y + 1.0 - ray->p_pos.y) * ray->delta_dist.y;
	}
}


/*in base alla colonna x si calcola dove si colloca il raggio sul FOV,
 e la distanza x e y al prossimo muro*/
void prepare_ray(t_ray *ray, int x)
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

static void	perform_dda(t_ray *ray, t_game *g)
{
	int	hit;
	int	rendered;

	hit = 0;
	rendered = 0;
	while (hit == 0 && rendered <= 30)
	{
		// take a step
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
		// render outside
		if (ray->map_x < 0 || ray->map_x >= g->map_w
			|| ray->map_y < 0 || ray->map_y >= g->map_h)
		{
			rendered++;
			if (rendered > 30)
				ray->side = -1;
			continue ;
		}
		// Se trovi un muro, ferma il DDA
		if (g->map[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
	//WALL dist
	if (ray->side == 0)
		ray->perpen_dist = (ray->map_x - ray->p_pos.x
				+ (1 - ray->step_x) / 2) / ray->ray_dir.x;
	else
		ray->perpen_dist = (ray->map_y - ray->p_pos.y
				+ (1 - ray->step_y) / 2) / ray->ray_dir.y;
}

void	compute_projection(t_game *g)
{
	int eye_offset;

	eye_offset = g->frame->img_h / 4;
	if (g->ray.perpen_dist == 0)
	{
		g->ray.draw_len = g->frame->img_h;
		g->ray.draw_start = W_H / 2;
		g->ray.draw_end = W_H / 2;
		return ;
	}
	g->ray.draw_len = (int)(g->frame->img_h / g->ray.perpen_dist);
	g->ray.draw_start = (-g->ray.draw_len / 2) + (g->frame->img_h / 2) + eye_offset;
	if (g->ray.draw_start < 0)
	g->ray.draw_start = 0;
	g->ray.draw_end = (g->ray.draw_len / 2) + (g->frame->img_h / 2) + eye_offset;
	if (g->ray.draw_end >= g->frame->img_h)
		g->ray.draw_end = g->frame->img_h - 1;
}

void	draw_remaining_background(t_game *g, int x)
{
	int	y;
	int	offset;

	if (g->ray.draw_start < 0 || g->ray.draw_start > g->frame->img_h)
		return ;
	if (g->ray.draw_end < 0 || g->ray.draw_end > g->frame->img_h)
		return ;
	y = 0;
	while (y < g->ray.draw_start)
	{
		offset = (y * g->frame->l_l) + (x * (g->frame->bpp / 8));
		*((unsigned int *)(g->frame->addr + offset)) = g->tex.c_color;
		y++;
	}
	y = g->ray.draw_end;
	while (y < g->frame->img_h)
	{
		offset = (y * g->frame->l_l) + (x * (g->frame->bpp / 8));
		*((unsigned int *)(g->frame->addr + offset)) = g->tex.f_color;
		y++;
	}
}

t_img	*get_texture(t_game *g)
{
	if (g->ray.side == 0)
	{
		if (g->ray.ray_dir.x > 0)
			return (g->tex.W_tex);
		return (g->tex.E_tex);
	}
	if (g->ray.ray_dir.y > 0)
		return (g->tex.N_tex);
	return (g->tex.S_tex);
}

int	get_texture_x_coordinate(t_draw *temp, t_game *g)
{
	double	wall_x;
	int		tex_x;

	wall_x = 0;
	tex_x = 0;
	if (g->ray.side == 0)
		wall_x = g->ray.p_pos.y + g->ray.perpen_dist
			* g->ray.ray_dir.y;
	else
		wall_x = g->ray.p_pos.x + g->ray.perpen_dist
			* g->ray.ray_dir.x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)temp->texture->img_w);
	if (g->ray.side == 0 && g->ray.ray_dir.x > 0)
		tex_x = temp->texture->img_w - tex_x - 1;
	if (g->ray.side == 1 && g->ray.ray_dir.y < 0)
		tex_x = temp->texture->img_w - tex_x - 1;
	return (tex_x);
}

void	drawing_loop(t_draw *temp, t_game *g, int x)
{
	int	y;
	int	offset;

	y = 0;
	y = g->ray.draw_start;
	offset = 0;
	while (y < g->ray.draw_end)
	{
		temp->tex_y = (int)temp->tex_pos & (temp->texture->img_h - 1);
		temp->tex_pos += temp->step;
		temp->color = *(int *)(temp->texture->addr
				+ temp->tex_y * temp->texture->l_l
				+ temp->tex_x * (temp->texture->bpp / 8));
		offset = (y * g->frame->l_l) + (x * (g->frame->bpp / 8));
		*((unsigned int *)(g->frame->addr + offset)) = temp->color;
		y++;
	}
}

void	draw_wall_column(t_game *g, int x)
{
	t_draw	temp;

	temp = (t_draw){0};
	if (g->ray.side == -1)
		return ;
	temp.texture = get_texture(g);
	temp.tex_x = get_texture_x_coordinate(&temp, g);
	temp.step = 1.0 * temp.texture->img_h / g->ray.draw_len;
	temp.tex_pos = (g->ray.draw_start - W_H / 2
			+ g->ray.draw_len / 2) * temp.step;
	drawing_loop(&temp, g, x);
}

int	game(t_game *g)
{
	int	x;

	x = 0;
	check_for_movement(g);
	while (x < W_W)
	{
		prepare_ray(&g->ray, x);
		perform_dda(&g->ray, g);
		compute_projection(g);
		draw_remaining_background(g, x);
		draw_wall_column(g, x);
		x++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_game	g;

	g = (t_game){0};
	if (!init_game(&g, av, ac))
		return (ft_malloc(0, 1), STDERR_FILENO);
	mlx_hook(g.win_ptr, 2, 1L << 0, handle_key_press, &g);
	mlx_hook(g.win_ptr, 3, 1L << 1, handle_key_release, &g);
	mlx_hook(g.win_ptr, 17, 1L << 2, close_window, &g);
	mlx_loop_hook(g.mlx_ptr, game, &g);
	mlx_loop(g.mlx_ptr);
	return (EXIT_SUCCESS);
}
