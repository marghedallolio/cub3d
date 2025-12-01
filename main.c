/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 13:01:05 by francema          #+#    #+#             */
/*   Updated: 2025/12/01 17:27:21 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	free_images(t_game *g)
{
	if (g->frame)
		mlx_destroy_image(g->mlx_ptr, g->frame->img);
	if (g->tex.N_tex)
		mlx_destroy_image(g->mlx_ptr, g->tex.N_tex->img);
	if (g->tex.S_tex)
		mlx_destroy_image(g->mlx_ptr, g->tex.S_tex->img);
	if (g->tex.E_tex)
		mlx_destroy_image(g->mlx_ptr, g->tex.E_tex->img);
	if (g->tex.W_tex)
		mlx_destroy_image(g->mlx_ptr, g->tex.W_tex->img);
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

int	game(t_game *g)
{
	int	x;

	x = 0;
	check_for_movement(g);
	while (x < W_W)
	{
		prepare_ray(&g->ray, x);
		perform_dda(&g->ray, g);
		compute_projection(g);
		draw_remaining_background(g, x);
		draw_wall_column(g, x);
		x++;
	}
	mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, g->frame->img, 0, 0);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	g;

	g = (t_game){0};
	if (!init_game(&g, av, ac))
		return (close_window(&g), STDERR_FILENO);
	mlx_hook(g.win_ptr, 2, 1L << 0, handle_key_press, &g);
	mlx_hook(g.win_ptr, 3, 1L << 1, handle_key_release, &g);
	mlx_hook(g.win_ptr, 17, 1L << 2, close_window, &g);
	mlx_loop_hook(g.mlx_ptr, game, &g);
	mlx_loop(g.mlx_ptr);
	return (EXIT_SUCCESS);
}
