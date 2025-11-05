/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:11:29 by mdalloli          #+#    #+#             */
/*   Updated: 2025/11/05 16:19:06 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "libft/libft.h"

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_textures
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
}	t_textures;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img;
	void	*addr;
	int		bpp;
	int		l_l;
	int		endian;
	int		img_w;
	int		img_h;
} t_mlx;

typedef struct s_player
{
	double pos_x;
	double pos_y;
	double dir_x;
	double dir_y;
	double plane_x;
	double plane_y;
}	t_player;

typedef struct s_ray
{
	double ray_dir_x;
	double ray_dir_y;
	int map_x;
	int map_y;
	double side_dist_x;
	double side_dist_y;
	double delta_dist_x;
	double delta_dist_y;
	double perp_wall_dist;
	int step_x;
	int step_y;
	int hit;
	int side;
}	t_ray;

typedef struct s_game
{
	t_textures	textures;
	t_color		floor;
	t_color		ceiling;
	t_map		map;
	t_mlx		libx;
	t_player	player;
	int			map_started;
}	t_game;

// PARSING
t_color parse_color(char *str);
int		parse_file(char *filename, t_game *game);
void	parse_line(char *line, t_game *game);
int		is_empty_line(char *line);
void	free_split(char **split);
void	validate_map(t_game *game);
void	add_map_line(t_game *game, char *line);

// ERRORS
void	print_error(char *msg);

#endif
