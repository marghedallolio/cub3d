/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:11:29 by mdalloli          #+#    #+#             */
/*   Updated: 2025/11/20 18:29:32 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "libft/libft.h"
# include "mlx/mlx.h"
# define SCREEN_W 800
# define SCREEN_H 600
# define MAP_W 24
# define MAP_H 6

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct s_img
{
	void	*img;
	void	*addr;
	int		bpp;
	int		l_l;
	int		endian;
	int		img_w;
	int		img_h;
}	t_img;

typedef struct s_textures
{
	t_img	*north;
	t_img	*south;
	t_img	*west;
	t_img	*east;
}	t_textures;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_ray
{
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
}	t_ray;

typedef struct s_game
{
	t_textures	textures;
	t_color		floor;
	t_color		ceiling;
	t_map		map;
	t_player	*p1;
	t_img		frame;
	int			map_started;
	void		*mlx_ptr;
	void		*win_ptr;
}	t_game;

// PARSING
t_color	parse_color(char *str);
int		parse_file(char *filename, t_game *game);
void	parse_line(char *line, t_game *game);
int		is_empty_line(char *line);
void	free_split(char **split);
void	validate_map(t_game *game);
void	add_map_line(t_game *game, char *line);
int		is_player_char(char c);
void	init_player_direction(t_player **p, char c);
void	find_player(t_game *game);

// INIT
bool	init_player(t_player *p);
bool	init_libx(t_game *g);
bool	init_game(t_game *g, char *av);
bool	init_map(t_map *m);

// RAYCASTING
int		raycast(t_game *game);
void	compute_wall_distance(t_ray *ray, t_player *p);

// RENDERING
/* bool	render_game(t_game *g); */
void	draw_vertical_line(t_game *g, t_ray *ray, int x);

// ERRORS
void	print_error(char *msg);

#endif
