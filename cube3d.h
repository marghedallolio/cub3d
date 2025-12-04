/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:11:29 by mdalloli          #+#    #+#             */
/*   Updated: 2025/12/04 15:42:17 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <sys/time.h>
# include "libft/libft.h"
# include "mlx/mlx.h"

//GAME CONSTANTs
# define ESC 65307
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363
# define UP_ARROW 65362
# define DOWN_ARROW 65364
# define W 119
# define A 97
# define S 115
# define D 100
# define W_W 1280
# define W_H 768
# define MOV_SPEED 0.03
# define ROT_SPEED 0.03
# define TABLE_SIZE 3600
# define PI 3.141592653589793

//ERR_MSGs
# define E_ARG "ERROR:\nInvalid n of arguments.\n"
# define E_ALLOC "ERROR:\nMalloc.\n"
# define CLR_SYN "ERROR:\nColor syntax error.\n"
# define CLR_VAL "ERROR:\nInvalid color value.\n"
# define ELE_EMPTY "ERROR:\nOne or more element's value not set.\n"
# define ELE_VAL "ERROR:\nInvalid element value.\n"
# define ELE_INV "ERROR:\nUnexpected element at line %d.\n"
# define FILE_OPEN "ERROR:\nOpen error "
# define FILE_READ "ERROR:\nRead error"
# define FILE_EMPTY "ERROR:\nEmpty file as argument.\n"
# define FILE_FORM "ERROR:\nInvalid file format, expected %s format.\n"
# define MAP_MSTART "ERROR:\nMultiple starting positions.\n"
# define MAP_INV "ERROR:\nUnknown character in map.\n"
# define MAP_EMPTY "ERROR:\nEmpty line in map.\n"
# define MAP_NULL "ERROR:\nNo map found.\n"
# define MAP_NSTART "ERROR:\nNo starting position was set.\n"
# define MAP_INC "ERROR:\nMap is not incased.\n"
# define ERR_WIN "ERROR:\nNew window creation failed.\n"
# define ERR_IMG "ERROR:\nNew image creation failed.\n"
# define ERR_IMG_CONV "ERROR:\nFile to image conversion failed.\n"

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_fps
{
	double	last_time;
	double	fps;
	int		frame_count;
}	t_fps;

typedef struct s_info_map
{
	char	*n_path;
	char	*s_path;
	char	*e_path;
	char	*w_path;
	char	*f_color;
	char	*c_color;
	int		e_set;
	char	facing;
	double	p_x;
	double	p_y;
}	t_info_map;

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

typedef struct s_draw
{
	t_img	*texture;
	int		tex_x;
	int		tex_y;
	double	tex_pos;
	int		color;
	double	step;
}	t_draw;

typedef struct s_tex
{
	t_img	*n_tex;
	t_img	*s_tex;
	t_img	*w_tex;
	t_img	*e_tex;
	int		f_color;
	int		c_color;
}	t_tex;

typedef struct s_vctr
{
	double	x;
	double	y;
}	t_vctr;

typedef struct s_ray
{
	t_vctr		p_pos;
	t_vctr		p_dir;
	t_vctr		plane;
	t_vctr		ray_dir;
	t_vctr		delta_dist;
	t_vctr		side_dist;
	double		cam_len;
	double		move_speed;
	double		perpen_dist;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	int			side;
	int			draw_start;
	int			draw_end;
	int			draw_len;
	double		sin_arr[TABLE_SIZE];
	double		cos_arr[TABLE_SIZE];
	int			table_size;
}	t_ray;

typedef struct s_game
{
	t_tex		tex;
	t_ray		ray;
	t_fps		fps;
	t_img		*frame;
	void		*mlx_ptr;
	void		*win_ptr;
	char		**file;
	char		**map;
	int			map_w;
	int			map_h;
	int			key_mask;
	int			mov_key;
	int			rot_key;
}	t_game;

// PARSING
bool	get_file_info(char **file, t_game *g, t_info_map *info);
bool	extract_file_info(t_info_map *info, t_game *g);
char	*clean_value(char *line);
int		convert_color(char *s);
bool	is_empty(char *str);
bool	parse_tex(t_game *g, t_info_map *info);
bool	map_parse(t_game *g, t_info_map *info);
char	**add_line(char **mat, char *line);
void	clean_up(t_game *g);
bool	bool_fill(char **map, t_game *g, int y, int x);
bool	invalid_char(char *s, t_game *g);
void	copy_row(char *r, char *s, int y, t_info_map *info);
char	**file_coping(char *path);
bool	args_check(int ac, char **av);
bool	check_format(char *path, char *format);

//DRAWING
void	perform_dda(t_ray *ray, t_game *g);
void	compute_projection(t_game *g);
void	draw_wall_column(t_game *g, int x);
t_img	*get_texture(t_game *g);
void	drawing_loop(t_draw *temp, t_game *g, int x);
int		get_texture_x_coordinate(t_draw *temp, t_game *g);
void	draw_remaining_background(t_game *g, int x);
void	prepare_ray(t_ray *ray, int x);
double	get_time_in_seconds(void);

// INIT GAME
bool	init_game(t_game *g, char **av, int ac);
bool	init_vector(t_info_map *info, t_ray *ray);

// MOVEMENTS
void	check_for_movement(t_game *g);
int		handle_key_press(int keycode, t_game *g);
int		handle_key_release(int keycode, t_game *g);

//SRCs
int		close_window(t_game *g);

#endif
