/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 17:06:33 by francema          #+#    #+#             */
/*   Updated: 2025/12/01 17:40:04 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

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
		temp->tex_y = (int)temp->tex_pos % temp->texture->img_h;
		if (temp->tex_y < 0)
			temp->tex_y += temp->texture->img_h;
		temp->tex_pos += temp->step;
		temp->color = *(int *)(temp->texture->addr
				+ temp->tex_y * temp->texture->l_l
				+ temp->tex_x * (temp->texture->bpp / 8));
		offset = (y * g->frame->l_l) + (x * (g->frame->bpp / 8));
		*((unsigned int *)(g->frame->addr + offset)) = temp->color;
		y++;
	}
}
