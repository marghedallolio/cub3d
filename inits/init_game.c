/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 15:15:43 by mdalloli          #+#    #+#             */
/*   Updated: 2025/12/04 14:52:24 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	clear_mlx(t_game *g)
{
	if (g->win_ptr)
		mlx_destroy_window(g->mlx_ptr, g->win_ptr);
	if (g->frame->img)
		mlx_destroy_image(g->mlx_ptr, g->frame->img);
	if (g->tex.E_tex || g->tex.N_tex || g->tex.S_tex || g->tex.W_tex)
	{
		if (g->tex.N_tex->img)
			mlx_destroy_image(g->mlx_ptr, g->tex.N_tex->img);
		if (g->tex.S_tex->img)
			mlx_destroy_image(g->mlx_ptr, g->tex.S_tex->img);
		if (g->tex.E_tex->img)
			mlx_destroy_image(g->mlx_ptr, g->tex.E_tex->img);
		if (g->tex.W_tex->img)
			mlx_destroy_image(g->mlx_ptr, g->tex.W_tex->img);
	}
	if (g->mlx_ptr)
	{
		mlx_destroy_display(g->mlx_ptr);
		free(g->mlx_ptr);
	}
	ft_malloc(0, 1);
	exit(1);
}

//MLX initialization for the game window and frame image
bool	init_mlx_game(t_game *g)
{
	g->mlx_ptr = mlx_init();
	if (!g->mlx_ptr)
		return (false);
	g->frame = ft_malloc(1 * sizeof(t_img), false);
	if (!g->frame)
		return (ft_printf(E_ALLOC), false);
	g->frame->img = mlx_new_image(g->mlx_ptr, W_W, W_H);
	if (!g->frame->img)
		return (ft_printf(ERR_IMG), false);
	g->frame->addr = mlx_get_data_addr(g->frame->img,
			&g->frame->bpp, &g->frame->l_l, &g->frame->endian);
	g->frame->img_h = W_H;
	g->frame->img_w = W_W;
	return (true);
}

bool	parse(t_game *g, t_info_map *info, char **av)
{
	char	**file;

	file = file_coping(av[1]);
	if (!file)
		return (false);
	g->file = file;
	if (!get_file_info(g->file, g, info))
		return (false);
	if (!parse_tex(g, info))
		return (false);
	if (!map_parse(g, info))
		return (false);
	return (true);
}

double get_time_in_seconds(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec + tv.tv_usec / 1e6;
}

/* Inizializza tutte le componenti del gioco: player, mappa, parsing e MiniLibX.
Restituisce false in caso di errore durante l’inizializzazione. */
bool	init_game(t_game *g, char **av, int ac)
{
	t_info_map	info;

	info = (t_info_map){0};
	g->tex = (t_tex){0};
	g->ray = (t_ray){0};
	g->fps = (t_fps){0};
	g->fps.last_time = get_time_in_seconds();
	g->key_mask = 0;
	if (!args_check(ac, av))
		return (false);
	if (!init_mlx_game(g))
		return (clear_mlx(g), false);
	if (!parse(g, &info, av))
		return (clear_mlx(g), false);
	if (!init_vector(&info, &g->ray))
		return (clear_mlx(g), false);
	g->win_ptr = mlx_new_window(g->mlx_ptr, W_W, W_H, "cub3D");
	if (!g->win_ptr)
		return (ft_printf(ERR_WIN), false);
	return (true);
}
