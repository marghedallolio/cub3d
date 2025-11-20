/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 15:15:43 by mdalloli          #+#    #+#             */
/*   Updated: 2025/11/20 18:19:15 by mdalloli         ###   ########.fr       */
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
	g->win_ptr = mlx_new_window(g->mlx_ptr, SCREEN_W, SCREEN_H, "CUB3D");
	if (!g->win_ptr)
	{
		mlx_destroy_display(g->mlx_ptr);
		free(g->mlx_ptr);
		return (false);
	}
	g->frame.img = mlx_new_image(g->mlx_ptr, SCREEN_W, SCREEN_H);
    if (!g->frame.img)
    {
        mlx_destroy_window(g->mlx_ptr, g->win_ptr);
        mlx_destroy_display(g->mlx_ptr);
        free(g->mlx_ptr);
        return (false);
    }
    g->frame.addr = mlx_get_data_addr(g->frame.img,
        &g->frame.bpp, &g->frame.l_l, &g->frame.endian);
	return (true);
}

/* bool init_textures(t_game *g)
{
    g->textures.north = (t_img *)ft_malloc(sizeof(t_img), 0);
    g->textures.south = (t_img *)ft_malloc(sizeof(t_img), 0);
    g->textures.west  = (t_img *)ft_malloc(sizeof(t_img), 0);
    g->textures.east  = (t_img *)ft_malloc(sizeof(t_img), 0);
    if (!g->textures.north || !g->textures.south
        || !g->textures.west || !g->textures.east)
        return (print_error("Failed to allocate textures"), 0);
    g->textures.north->img = mlx_xpm_file_to_image(g->mlx_ptr,
                                "textures/north.xpm",
                                &g->textures.north->img_w,
                                &g->textures.north->img_h);
    g->textures.south->img = mlx_xpm_file_to_image(g->mlx_ptr,
                                "textures/south.xpm",
                                &g->textures.south->img_w,
                                &g->textures.south->img_h);
    g->textures.west->img = mlx_xpm_file_to_image(g->mlx_ptr,
                                "textures/west.xpm",
                                &g->textures.west->img_w,
                                &g->textures.west->img_h);
    g->textures.east->img = mlx_xpm_file_to_image(g->mlx_ptr,
		"textures/east.xpm", &g->textures.east->img_w, &g->textures.east->img_h);
    if (!g->textures.north->img || !g->textures.south->img
        || !g->textures.west->img || !g->textures.east->img)
        return (print_error("Failed to load textures"), 0);
    return (true);
} */

/* Inizializza tutte le componenti del gioco: player, mappa, parsing e MiniLibX.
Restituisce false in caso di errore durante l’inizializzazione. */
/* Inizializza tutte le componenti del gioco: player, mappa, parsing e MiniLibX.
   Restituisce false in caso di errore durante l’inizializzazione. */
bool init_game(t_game *g, char *av)
{
    t_player *p;

    // Alloca il player
    p = (t_player *)ft_malloc(sizeof(t_player), 0);
    if (!p)
    {
		printf("luop\n");
		return (false);
	}
    if (!init_player(p) || !init_map(&g->map))
    {
		printf("ciao\n");
        return (false);
    }
    g->p1 = p;
    // Inizializzazione MiniLibX
    if (!init_libx(g))
    {
		printf("meta lupo\n");
        return (false);
    }
	// Parsing del file .cub
	if (!parse_file(av, g)) // parse_line si occupa di caricare le texture
	{
		printf("kanguro\n");
		return (false);
	}

    ft_printf("Parsing completato e MLX inizializzato.\n");
    return (true);
}


