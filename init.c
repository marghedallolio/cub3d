/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 15:15:43 by mdalloli          #+#    #+#             */
/*   Updated: 2025/11/20 15:45:46 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/*init della mappa*/
bool	init_map(t_map *m)
{
	if (!m)
		return (false);
	m->grid = NULL;
	m->height = 0;
	m->width = 0;
	return (true);
}

/*init del player*/
bool	init_player(t_player *p)
{
	if (!p)
		return (false);
	p->pos_x = 22;
	p->pos_y = 12;
	p->dir_x = -1;
	p->dir_y = 0;
	p->plane_x = 0;
	p->plane_y = 0.66;
	return (true);
}

/* Inizializza la libreria MiniLibX e crea la finestra di gioco
Ritorna false se l’inizializzazione fallisce. */
bool	init_libx(t_game *g)
{
	g->mlx_ptr = mlx_init();
	if (!g->mlx_ptr)
		return (false);
	g->win_ptr = mlx_new_window(g->mlx_ptr,
			SCREEN_W, SCREEN_H, "CUB3D");
	if (!g->win_ptr)
	{
		mlx_destroy_display(g->mlx_ptr);
		free(g->mlx_ptr);
		return (false);
	}
/* 	libx->img = mlx_new_image(libx->mlx_ptr, SCREEN_W, SCREEN_H);
	libx->addr = mlx_get_data_addr(libx->img, &libx->bpp, &libx->l_l, &libx->endian); */
	return (true);
}

/* Inizializza tutte le componenti del gioco: player, mappa, parsing e MiniLibX.
Restituisce false in caso di errore durante l’inizializzazione. */
bool	init_game(t_game *g, char *av)
{
	//t_mlx		*g_libx;
	t_player	*p;

	p = (t_player *)ft_malloc(sizeof(t_player) * 1, 0);
	if (!p)
	{
		ft_malloc(0, 1);
		return (false);
	}
	if (!init_player(p) || !init_map(&(g->map)))
		return (false);
	g->p1 = p;
	parse_file(av, g);
	//g_libx = (t_mlx *)ft_malloc(sizeof(t_mlx) * 1, 0);
	/* if (!g_libx)
		return (false); */
	if (!init_libx(g))
		return (false);
	//g->libx = g_libx;
	ft_printf("Starting parse_file...\n");
	ft_printf("Parsing fatto\n");
	return (true);
}
