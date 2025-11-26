/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:20:23 by francema          #+#    #+#             */
/*   Updated: 2025/11/25 19:16:27 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

//TEXTURE PARSING
t_img	*load_tex_info(void *mlx_ptr, char *path)
{
	t_img	*tex;
	int		tmp_fd;

	tmp_fd = 0;
	tmp_fd = open(path, O_RDONLY);
	tex = NULL;
	if (tmp_fd < 0)
		return (ft_printf(FILE_OPEN), perror(path), NULL);
	close(tmp_fd);
	tex = ft_malloc(sizeof(t_img) * 1, 0);
	if (!tex)
		return (ft_printf(E_ALLOC), close(tmp_fd), NULL);
	tex->img = mlx_xpm_file_to_image(mlx_ptr, path, &tex->img_w, &tex->img_h);
	if (!tex->img)
		return (ft_printf(ERR_IMG_CONV), NULL);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->l_l, &tex->endian);
	return (tex);
}

bool	parse_tex(t_game *g, t_info_map *info)
{
	if (!check_format(info->n_path, ".xpm")
		|| !check_format(info->s_path, ".xpm")
		|| !check_format(info->e_path, ".xpm")
		|| !check_format(info->w_path, ".xpm"))
		return (false);
	g->tex.N_tex = load_tex_info(g->mlx_ptr, info->n_path);
	g->tex.S_tex = load_tex_info(g->mlx_ptr, info->s_path);
	g->tex.E_tex = load_tex_info(g->mlx_ptr, info->e_path);
	g->tex.W_tex = load_tex_info(g->mlx_ptr, info->w_path);
	if (!g->tex.N_tex || !g->tex.S_tex
		|| !g->tex.E_tex || !g->tex.W_tex)
		return (false);
	return (true);
}
