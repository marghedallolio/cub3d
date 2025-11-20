/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 13:01:05 by francema          #+#    #+#             */
/*   Updated: 2025/11/19 15:39:06 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	close_window()
{
	printf("finestra chiusa!\n");
	ft_malloc(0, 1);
	exit(0);
	return 0;
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

	parse_file(av, g);
	libx = (t_mlx *)ft_malloc(sizeof(t_mlx) * 1, 0);
	if (!libx)
		return (false);
	p1 = (t_player *)ft_malloc(sizeof(t_player) * 1, 0);
	if (!p1)
	{
		ft_malloc(0, 1);
		return (false);
	}
	if (!init_player(p1) || !init_libx(libx))
		return (false);
	ft_printf("Starting parse_file...\n");
	ft_printf("Parsing fatto\n");
	return (true);
}

int	main(int argc, char **argv)
{
	t_game	g;

	(void)argv;
	if (argc != 2)
		printf("Usage: ./cube3d <map.cup>\n\n");
	if (!init_game(&g, argv[1]))
		return (STDERR_FILENO);
	if (!render_game(&g))
		return (STDERR_FILENO);
	mlx_hook(g.libx->win_ptr, 17, 0, close_window, NULL);
	mlx_loop(g.libx->mlx_ptr);
	ft_bzero(&g, sizeof(t_game));
	ft_malloc(0, 1);
	return (EXIT_SUCCESS);
}

