/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 11:24:11 by francema          #+#    #+#             */
/*   Updated: 2025/11/11 12:11:01 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

bool	render_game(t_game *g)
{
	if (!g->libx->img)
		return (false);
	if (mlx_put_image_to_window(g->libx->mlx_ptr,
			g->libx->win_ptr, g->libx->img, 0, 0) != 1)
	{
		mlx_destroy_image(g->libx->mlx_ptr, g->libx->img);
		g->libx->img = NULL;
		return (false);
	}
	mlx_destroy_image(g->libx->mlx_ptr, g->libx->img);
	g->libx->img = NULL;
	return (true);
}
