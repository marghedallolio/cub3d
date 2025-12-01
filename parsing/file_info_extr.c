/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_info_extr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:37:21 by francema          #+#    #+#             */
/*   Updated: 2025/12/01 15:00:39 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

bool	extract_paths(t_info_map *parse)
{
	parse->n_path = clean_value(&parse->n_path[2]);
	if (!parse->n_path)
		return (false);
	parse->s_path = clean_value(&parse->s_path[2]);
	if (!parse->s_path)
		return (false);
	parse->e_path = clean_value(&parse->e_path[2]);
	if (!parse->e_path)
		return (false);
	parse->w_path = clean_value(&parse->w_path[2]);
	if (!parse->w_path)
		return (false);
	return (true);
}

bool	extract_colors(t_info_map *info, t_game *g)
{
	info->f_color = clean_value(&info->f_color[1]);
	if (!info->f_color)
		return (false);
	info->c_color = clean_value(&info->c_color[1]);
	if (!info->c_color)
		return (false);
	g->tex.f_color = convert_color(info->f_color);
	if (g->tex.f_color == -1)
		return (false);
	g->tex.c_color = convert_color(info->c_color);
	if (g->tex.c_color == -1)
		return (false);
	return (true);
}

bool	extract_file_info(t_info_map *info, t_game *g)
{
	if (!info->n_path || !info->s_path
		|| !info->e_path || !info->w_path)
	{
		ft_printf("Error: Missing texture(s)\n");
		return (false);
	}
	if (!extract_paths(info))
		return (false);
	if (!extract_colors(info, g))
		return (false);
	return (true);
}
