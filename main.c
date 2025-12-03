/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 13:01:05 by francema          #+#    #+#             */
/*   Updated: 2025/12/03 17:45:10 by francema         ###   ########.fr       */
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

void draw_fps(t_game *g)
{
	char buffer[32];
	int fps_int = (int)g->fps.fps;
	int fps_dec = (int)((g->fps.fps - fps_int) * 10);
	int index = 0;

	buffer[index++] = 'F';
	buffer[index++] = 'P';
	buffer[index++] = 'S';
	buffer[index++] = ':';
	buffer[index++] = ' ';
	if (fps_int == 0)
		buffer[index++] = '0';
	else
	{
		int temp[10], i = 0;
		while (fps_int > 0)
		{
			temp[i++] = fps_int % 10;
			fps_int /= 10;
		}
		while (i-- > 0)
			buffer[index++] = '0' + temp[i];
	}
	buffer[index++] = '.';
	buffer[index++] = '0' + fps_dec;
	buffer[index] = '\0';
	mlx_string_put(g->mlx_ptr, g->win_ptr, 10, 10, 0xFFFFFF, buffer);
}

int	game(t_game *g)
{
	int	x;
	static double now;
	static double delta;

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
	g->fps.frame_count++;
	now = get_time_in_seconds();
	delta = now - g->fps.last_time;
	if (delta >= 1.0)
	{
		g->fps.fps = g->fps.frame_count / delta;
		g->fps.frame_count = 0;
		g->fps.last_time = now;
	}
	draw_fps(g);
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
