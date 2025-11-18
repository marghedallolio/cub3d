/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 11:22:15 by francema          #+#    #+#             */
/*   Updated: 2025/11/11 11:22:56 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	draw_vertical_line(t_game *game, t_ray *ray, int x)
{
	int	line_height;
	int	start;
	int	end;
	int	color;

	line_height = (int)(SCREEN_H / ray->perp_wall_dist);
	start = -line_height / 2 + SCREEN_H / 2;
	end = line_height / 2 + SCREEN_H / 2;
	if (start < 0)
		start = 0;
	if (end >= SCREEN_H)
		end = SCREEN_H - 1;
	color = (ray->side == 1) ? 0xAAAAAA : 0xFFFFFF;
	put_line_to_img(game->libx, x, start, end, color); //mancante
}
