/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 11:24:11 by francema          #+#    #+#             */
/*   Updated: 2025/11/20 18:28:58 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

/* bool	render_game(t_game *g)
{
	if (!g->frame.img)
		return (false);
	if (mlx_put_image_to_window(g->mlx_ptr, g->win_ptr,
			g->frame.img, 0, 0) != 1)
	{
		mlx_destroy_image(g->mlx_ptr, g->frame.img);
		g->frame.img = NULL;
		return (false);
	}
	return (true);
} */
