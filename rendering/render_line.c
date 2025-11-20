/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 11:22:15 by francema          #+#    #+#             */
/*   Updated: 2025/11/20 16:25:10 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static t_img *select_texture(t_game *g, t_ray *ray)
{
    if (ray->side == 0) // muro verticale
    {
        if (ray->ray_dir_x > 0)
            return g->textures.west;     // muro Ovest
        else
            return g->textures.east;     // muro Est
    }
    else                // muro orizzontale
    {
        if (ray->ray_dir_y > 0)
            return g->textures.north;    // muro Nord
        else
            return g->textures.south;    // muro Sud
    }
}

static void put_line_to_img(t_game *g, t_ray *ray, int x, int start, int end)
{
    t_img   *tex;
    double  wall_x;
    int     tex_x;
    int     tex_y;
    int     y;
    char    *dst;
    char    *src;
    double  step;
    double  tex_pos;

    tex = select_texture(g, ray);

    // posizione esatta dove colpisce il muro
    if (ray->side == 0)
        wall_x = g->p1->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
    else
        wall_x = g->p1->pos_x + ray->perp_wall_dist * ray->ray_dir_x;

    wall_x -= floor(wall_x);

    tex_x = (int)(wall_x * (double)tex->img_w);
    if ((ray->side == 0 && ray->ray_dir_x > 0)
        || (ray->side == 1 && ray->ray_dir_y < 0))
        tex_x = tex->img_w - tex_x - 1;

    step = 1.0 * tex->img_h / (end - start);
    tex_pos = (start - SCREEN_H / 2 + (end - start) / 2) * step;

    y = start;
    while (y < end)
    {
        tex_y = (int)tex_pos & (tex->img_h - 1);
        tex_pos += step;

        src = tex->addr + tex_y * tex->l_l + tex_x * (tex->bpp / 8);
        dst = g->frame.addr + y * g->frame.l_l + x * (g->frame.bpp / 8);

        *(unsigned int *)dst = *(unsigned int *)src;
        y++;
    }
}

void	draw_vertical_line(t_game *g, t_ray *ray, int x)
{
	int	line_height;
	int	start;
	int	end;
	
	line_height = (int)(SCREEN_H / ray->perp_wall_dist);
	start = -line_height / 2 + SCREEN_H / 2;
	end = line_height / 2 + SCREEN_H / 2;
	if (start < 0)
		start = 0;
	if (end >= SCREEN_H)
		end = SCREEN_H - 1;
	put_line_to_img(g, ray, x, start, end);
}
