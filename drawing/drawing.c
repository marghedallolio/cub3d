/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 17:09:35 by francema          #+#    #+#             */
/*   Updated: 2025/12/04 15:32:04 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	compute_projection(t_game *g)
{
	int	eye_offset;

	eye_offset = 0;
	if (g->ray.perpen_dist == 0)
	{
		g->ray.draw_len = g->frame->img_h;
		g->ray.draw_start = W_H / 2;
		g->ray.draw_end = W_H / 2;
		return ;
	}
	g->ray.draw_len = (int)(g->frame->img_h / g->ray.perpen_dist);
	g->ray.draw_start = (-g->ray.draw_len / 2) + (g->frame->img_h / 2)
		+ eye_offset;
	if (g->ray.draw_start < 0)
		g->ray.draw_start = 0;
	g->ray.draw_end = (g->ray.draw_len / 2) + (g->frame->img_h / 2)
		+ eye_offset;
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
