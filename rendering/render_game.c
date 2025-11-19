/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 11:24:11 by francema          #+#    #+#             */
/*   Updated: 2025/11/19 17:22:14 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

bool	render_game(t_game *g)
{
	if (!g->img)
		return (false);
	if (mlx_put_image_to_window(g->mlx_ptr,
			g->win_ptr, g->libx->img, 0, 0) != 1)
	{
		printf("quya\n");
		mlx_destroy_image(g->mlx_ptr, g->libx->img);
		g->libx->img = NULL;
		return (false);
	}
	printf("o qua\n");
	// mlx_destroy_image(g->libx->mlx_ptr, g->libx->img);
	// g->libx->img = NULL;
	return (true);
}
