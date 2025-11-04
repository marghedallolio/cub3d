/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:11:29 by mdalloli          #+#    #+#             */
/*   Updated: 2025/10/29 15:47:45 by mdalloli         ###   ########.fr       */
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

typedef struct s_player
{
	double	x;
	double	y;
	char	dir;
}	t_player;

typedef struct s_game
{
	t_textures	textures;
	t_color		floor;
	t_color		ceiling;
	t_map		map;
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