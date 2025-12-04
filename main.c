/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 13:01:05 by francema          #+#    #+#             */
/*   Updated: 2025/12/04 16:03:02 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	draw_fps(t_game *g)
{
	char	buffer[32];
	int		fps_int;
	int		fps_dec;
	int		index;
	int		temp[10];
	int		i;

	fps_int = (int)g->fps.fps;
	fps_dec = (int)((g->fps.fps - fps_int) * 10);
	index = 0;
	buffer[index++] = 'F';
	buffer[index++] = 'P';
	buffer[index++] = 'S';
	buffer[index++] = ':';
	buffer[index++] = ' ';
	if (fps_int == 0)
		buffer[index++] = '0';
	else
	{
		i = 0;
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
	int				x;
	static double	now;
	static double	delta;

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
		return (STDERR_FILENO);
	mlx_hook(g.win_ptr, 2, 1L << 0, handle_key_press, &g);
	mlx_hook(g.win_ptr, 3, 1L << 1, handle_key_release, &g);
	mlx_hook(g.win_ptr, 17, 1L << 2, close_window, &g);
	mlx_loop_hook(g.mlx_ptr, game, &g);
	mlx_loop(g.mlx_ptr);
	return (EXIT_SUCCESS);
}
