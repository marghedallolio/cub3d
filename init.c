/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 15:15:43 by mdalloli          #+#    #+#             */
/*   Updated: 2025/11/19 15:36:52 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

bool	init_map(t_map m)
{
	m.grid = 0;
	m.height = 0;
	m.width = 0;
	return (true);
}

bool	init_player(t_player *p)
{
	p->pos_x = 22;
	p->pos_y = 12;
	p->dir_x = -1;
	p->dir_y = 0;
	p->plane_x = 0;
	p->plane_y = 0.66; // FOV ~66°
	return (true);
}

bool	init_libx(t_mlx *libx)
{
	libx->mlx_ptr = mlx_init();
	if (!libx->mlx_ptr)
		return (false);
	libx->win_ptr = mlx_new_window(libx->mlx_ptr,
			SCREEN_W, SCREEN_H, "CUB3D");
	if (!libx->win_ptr)
	{
		mlx_destroy_display(libx->mlx_ptr);
		free(libx->mlx_ptr);
		return (false);
	}
	libx->img = NULL;
	libx->addr = NULL;
	return (true);
}


bool	init_game(t_game *g, char *av)
{
	t_mlx		*libx;
	t_player	*p1;

	p1 = (t_player *)ft_malloc(sizeof(t_player) * 1, 0);
	if (!init_player(p1) || !init_map(g->map))
		return (false);
	parse_file(av, g);
	libx = (t_mlx *)ft_malloc(sizeof(t_mlx) * 1, 0);
	if (!libx)
		return (false);
	if (!init_libx(libx))
		return (false);
	if (!p1)
	{
		ft_malloc(0, 1);
		return (false);
	}
	ft_printf("Starting parse_file...\n");
	ft_printf("Parsing fatto\n");
	return (true);
}
