/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 16:02:44 by mdalloli          #+#    #+#             */
/*   Updated: 2025/12/04 16:02:59 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	free_images(t_game *g)
{
	if (g->frame)
		mlx_destroy_image(g->mlx_ptr, g->frame->img);
	if (g->tex.n_tex)
		mlx_destroy_image(g->mlx_ptr, g->tex.n_tex->img);
	if (g->tex.s_tex)
		mlx_destroy_image(g->mlx_ptr, g->tex.s_tex->img);
	if (g->tex.e_tex)
		mlx_destroy_image(g->mlx_ptr, g->tex.e_tex->img);
	if (g->tex.w_tex)
		mlx_destroy_image(g->mlx_ptr, g->tex.w_tex->img);
}

int	close_window(t_game *g)
{
	ft_printf("finestra chiusa!\n");
	if (g->win_ptr)
		mlx_destroy_window(g->mlx_ptr, g->win_ptr);
	free_images(g);
	mlx_destroy_display(g->mlx_ptr);
	free(g->mlx_ptr);
	ft_malloc(0, 1);
	exit(0);
	return (0);
}