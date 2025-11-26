/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 15:15:43 by mdalloli          #+#    #+#             */
/*   Updated: 2025/11/25 19:15:47 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

//RAYs INIT
void	get_dir_vector(char face, t_ray *ray)
{
	if (face == 'N')
	{
		ray->p_dir.x = 0;
		ray->p_dir.y = -1;
	}
	else if (face == 'S')
	{
		ray->p_dir.x = 0;
		ray->p_dir.y = 1;
	}
	else if (face == 'E')
	{
		ray->p_dir.x = 1;
		ray->p_dir.y = 0;
	}
	else if (face == 'W')
	{
		ray->p_dir.x = -1;
		ray->p_dir.y = 0;
	}
}
/*(i * 2*PI) / 3600 radiants conversion */
void	init_lookup_table(t_ray *ray)
{
	double	angle;
	int		i;

	i = 0;
	ray->table_size = TABLE_SIZE;
	while (i < TABLE_SIZE)
	{
		angle = (i * 2.0 * PI) / TABLE_SIZE;
		ray->sin_arr[i] = sin(angle);
		ray->cos_arr[i] = cos(angle);
		i++;
	}
}

bool	get_vector(t_info_map *info, t_ray *ray)
{
	ray->p_pos = (t_vctr){0};
	ray->p_dir = (t_vctr){0};
	ray->plane = (t_vctr){0};
	ray->p_pos.x = info->p_x;
	ray->p_pos.y = info->p_y;
	get_dir_vector(info->facing, ray);
	ray->plane.x = -ray->p_dir.y * 0.66;
	ray->plane.y = ray->p_dir.x * 0.66;
	ray->move_speed = MOV_SPEED;
	init_lookup_table(ray);
	return (true);
}

//MLX initialization for the game window and frame image
bool	init_mlx_game(t_game *g)
{
	g->mlx_ptr = mlx_init();
	if (!g->mlx_ptr)
		return (false);
	g->win_ptr = mlx_new_window(g->mlx_ptr, W_W, W_H, "cub3D");
	if (!g->win_ptr)
		return (ft_printf(ERR_WIN), false);
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

/* Inizializza tutte le componenti del gioco: player, mappa, parsing e MiniLibX.
Restituisce false in caso di errore durante l’inizializzazione. */
bool	init_game(t_game *g, char **av, int ac)
{
	t_info_map	info;
	t_tex		tex;
	t_ray		ray;


	info = (t_info_map){0};
	tex = (t_tex){0};
	ray = (t_ray){0};
	g->tex = tex;
	g->ray = ray;
	if (!args_check(ac, av))
		return (false);
	if (!init_mlx_game(g))
		return (false);
	if (!parse(g, &info, av))
		return (false);
	if (!get_vector(&info, &g->ray))
		return (false);
	return (true);
}
