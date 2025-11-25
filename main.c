/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 13:01:05 by francema          #+#    #+#             */
/*   Updated: 2025/11/25 14:35:42 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	close_window(t_game *g)
{
	if (g->textures.north && g->textures.north->img)
		mlx_destroy_image(g->mlx_ptr, g->textures.north->img);
	if (g->textures.south && g->textures.south->img)
		mlx_destroy_image(g->mlx_ptr, g->textures.south->img);
	if (g->textures.west && g->textures.west->img)
		mlx_destroy_image(g->mlx_ptr, g->textures.west->img);
	if (g->textures.east && g->textures.east->img)
		mlx_destroy_image(g->mlx_ptr, g->textures.east->img);

	if (g->frame.img)
		mlx_destroy_image(g->mlx_ptr, g->frame.img);

	if (g->win_ptr)
		mlx_destroy_window(g->mlx_ptr, g->win_ptr);

	if (g->mlx_ptr)
	{
		mlx_destroy_display(g->mlx_ptr);
		free(g->mlx_ptr);
	}
	exit(0);
}


int	main(int argc, char **argv)
{
	t_game	g;

	(void)argv;
	if (argc != 2)
		printf("Usage: ./cube3d <map.cup>\n\n");
	if (!init_game(&g, argv[1]))
	{
		printf("dio negro\n");
		mlx_destroy_image(g.mlx_ptr, g.frame.img);
		ft_malloc(0, 1);
		return (STDERR_FILENO);
	}
	/* if (!render_game(&g))
	{
		printf("entra qua\n");
		ft_malloc(0, 1);
		return (STDERR_FILENO);
	} */
	mlx_hook(g.win_ptr, 17, 0, close_window, &g);
	mlx_loop_hook(g.mlx_ptr, raycast, &g);
	mlx_loop(g.mlx_ptr);
	/* mlx_destroy_image(g.mlx_ptr, g.textures.east);
	mlx_destroy_image(g.mlx_ptr, g.textures.west);
	mlx_destroy_image(g.mlx_ptr, g.textures.north);
	mlx_destroy_image(g.mlx_ptr, g.textures.south);
	mlx_destroy_image(g.mlx_ptr, g.frame.img); */
	ft_malloc(0, 1);
	return (EXIT_SUCCESS);
}
