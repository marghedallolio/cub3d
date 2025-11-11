/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 11:03:34 by francema          #+#    #+#             */
/*   Updated: 2025/11/11 11:07:27 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	raycast(t_game *game)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < SCREEN_W)
	{
		init_ray(&ray, game->p1, x);
		perform_dda(&ray, &game->map);
		compute_wall_distance(&ray, game->p1);
		draw_vertical_line(game, &ray, x);
		x++;
	}
}
