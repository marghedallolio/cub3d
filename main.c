/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 13:01:05 by francema          #+#    #+#             */
/*   Updated: 2025/11/20 18:27:18 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	close_window(t_game *game)
{
	mlx_destroy_image(game->mlx_ptr, game->frame.img);
    mlx_destroy_image(game->mlx_ptr, game->textures.north);
    mlx_destroy_image(game->mlx_ptr, game->textures.south);
    mlx_destroy_image(game->mlx_ptr, game->textures.west);
    mlx_destroy_image(game->mlx_ptr, game->textures.east);
    mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	printf("finestra chiusa!\n");
	ft_malloc(0, 1);
	exit(0);
	return (0);
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
