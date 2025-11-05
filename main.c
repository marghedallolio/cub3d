/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:11:32 by mdalloli          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/11/05 16:17:14 by francema         ###   ########.fr       */
=======
/*   Updated: 2025/11/05 16:43:39 by mdalloli         ###   ########.fr       */
>>>>>>> 2ea483b4e32f234034d670e734802e5bbe33d723
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define SCREEN_W 800
#define SCREEN_H 600
#define MAP_W 24
#define MAP_H 6

int	close_window()
{
	printf("finestra chiusa!\n");
	exit(0);
	return 0;
}

t_player init_player(void)
{
	t_player p;

	p.pos_x = 22;
	p.pos_y = 12;
	p.dir_x = -1;
	p.dir_y = 0;
	p.plane_x = 0;
	p.plane_y = 0.66; // FOV ~66°
	return (p);
}

int create_world(t_game *g)
{
	if (!libx || !p1)
		return (0);
	if (!libx->addr)
	{
		fprintf(stderr, "create_world: libx->addr is NULL\n");
		return (0);
	}
	for (int x = 0; x < SCREEN_W; x++)
	{
		double camera_x = 2.0 * x / (double)SCREEN_W - 1.0;
		double ray_dir_x = p1->dir_x + p1->plane_x * camera_x;
		double ray_dir_y = p1->dir_y + p1->plane_y * camera_x;
		int map_x = (int)floor(p1->pos_x);
		int map_y = (int)floor(p1->pos_y);
		double delta_dist_x = (ray_dir_x == 0.0) ? 1e30 : fabs(1.0 / ray_dir_x);
		double delta_dist_y = (ray_dir_y == 0.0) ? 1e30 : fabs(1.0 / ray_dir_y);
		int step_x = 0;
		int step_y = 0;
		double side_dist_x = 0.0;
		double side_dist_y = 0.0;
		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (p1->pos_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - p1->pos_x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (p1->pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - p1->pos_y) * delta_dist_y;
		}
		int hit = 0;
		int side = 0;
		// DDA: cammina finché non hit o esci dalla mappa
		while (hit == 0)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			// protezione out-of-bounds importante
			if (map_x < 0 || map_x >= MAP_W || map_y < 0 || map_y >= MAP_H)
			{
				hit = 1;
				break; // ray left the map
			}
			if (world_map[map_y][map_x] > 0)
				hit = 1;
		}
		// Calcola distanza perpendicolare (proteggi divisione)
		double perp_wall_dist;
		if (side == 0)
			perp_wall_dist = (ray_dir_x == 0.0) ? 1e-6 : (map_x - p1->pos_x + (1 - step_x) / 2.0) / ray_dir_x;
		else
			perp_wall_dist = (ray_dir_y == 0.0) ? 1e-6 : (map_y - p1->pos_y + (1 - step_y) / 2.0) / ray_dir_y;
		if (perp_wall_dist <= 1e-6)
			perp_wall_dist = 1e-6;
		int line_height = (int)(SCREEN_H / perp_wall_dist);
		int draw_start = -line_height / 2 + SCREEN_H / 2;
		if (draw_start < 0)
			draw_start = 0;
		int draw_end = line_height / 2 + SCREEN_H / 2;
		if (draw_end >= SCREEN_H)
			draw_end = SCREEN_H - 1;
		int color = (side == 1) ? 0x00AAFF : 0x0044FF;
		// scrivi la colonna nel buffer immagine (controllo bounds)
		for (int y = draw_start; y <= draw_end; y++)
		{
			if (x < 0 || x >= SCREEN_W || y < 0 || y >= SCREEN_H)
				continue;
			int pixel_offset = y * libx->l_l + x * (libx->bpp / 8);
			// ulteriore check: pixel_offset non troppo grande o negativo (facoltativo)
			if (pixel_offset < 0)
				continue;
			// finalmente scrivi (assumendo bpp >= 32)
			*(int *)(libx->addr + pixel_offset) = color;
		}
	}
	mlx_put_image_to_window(libx->mlx_ptr, libx->win_ptr, libx->img, 0, 0);
	return (1);
}

bool	init_game(t_game *g)
{
	t_mlx	libx;

	if (!init_libx(&libx))
		return (1);
}

int	main(int argc, char **argv)
{
	t_game	g;


	(void)argv;
	if (argc != 2)
		printf("Usage: ./cub3d <map.cup>\n\n");
	if (!init_game(&g))
	create_world(&g);
	mlx_hook(g.libx.win_ptr, 17, 0, close_window, NULL);
	mlx_loop(g.libx.mlx_ptr);
	ft_bzero(&g, sizeof(t_game));
	game.floor.r = -1;
	game.ceiling.r = -1;
<<<<<<< HEAD
	parse_file(argv[1], &g);
=======
	ft_printf("Starting parse_file...\n");
	parse_file(argv[1], &game);
	ft_printf("Parsing fatto\n");
>>>>>>> 2ea483b4e32f234034d670e734802e5bbe33d723
	return (0);
}

// int	main(int argc, char **argv)
// {
// 	t_game	game;

// 	if (argc != 2)
// 		print_error("Usage: ./cub3d <map.cup>");
// 	ft_bzero(&game, sizeof(t_game));
// 	game.floor.r = -1;
// 	game.ceiling.r = -1;
// 	parse_file(argv[1], &game);
// 	ft_printf("Parsing fatto");
// 	return (0);
// }
