/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 13:01:05 by francema          #+#    #+#             */
/*   Updated: 2025/11/19 15:15:41 by mdalloli         ###   ########.fr       */
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
	mlx_loop_hook(g.libx->mlx_ptr, raycast, &g);
	mlx_loop(g.libx->mlx_ptr);
	ft_bzero(&g, sizeof(t_game));
	ft_malloc(0, 1);
	return (EXIT_SUCCESS);
}

