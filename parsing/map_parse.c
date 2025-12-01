/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:22:39 by francema          #+#    #+#             */
/*   Updated: 2025/12/01 16:08:27 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

//MAP PARSING

bool	check_characters(char **map, t_game *g)//CHECK FOR INVALID CHARS IN THE MAP
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (is_empty(map[i]))
			return (ft_printf(FILE_EMPTY), false);
		if (invalid_char(map[i], g))
		{
			g->map = NULL;
			return (false);
		}
		i++;
	}
	g->map_h = i;
	return (true);
}

char	**normalize_map(char **map, t_game *g, t_info_map *parse)//NORMALIZE THE MAP TO A RECTANGULAR MATRIX FILLED WITH '0's
{
	char	**norm_map;
	int		i;

	i = 0;
	norm_map = NULL;
	norm_map = ft_malloc((g->map_h + 1) * sizeof(char *), 0);
	if (!norm_map)
		return (ft_printf(E_ALLOC), NULL);
	while (i < g->map_h)
	{
		norm_map[i] = ft_malloc((g->map_w + 1) * sizeof(char), 0);
		if (!norm_map[i])
			return (ft_printf(E_ALLOC), NULL);
		norm_map[i] = (char *)ft_memset((void *)norm_map[i], '0', g->map_w);
		norm_map[i][g->map_w] = '\0';
		copy_row(norm_map[i], map[i], i, parse);
		i++;
	}
	norm_map[i] = NULL;
	return (norm_map);
}

bool	incased(char **map, t_game *g, t_info_map *info)//CHECK IF THE MAP IS ENCLOSED USING FLOOD FILL
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!bool_fill(map, g, info->p_y, info->p_x))
		return (false);
	clean_up(g);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'V')
				map[i][j] = '0';
			j++;
		}
		i++;
	}
	return (true);
}

bool	map_parse(t_game *g, t_info_map *info)//PARSE THE MAP: CHECK CHARACTERS, NORMALIZE, CHECK ENCLOSURE
{
	if (!g->map)
		return (ft_printf(MAP_NULL), false);
	if (!check_characters(g->map, g))
		return (false);
	g->map = normalize_map(g->map, g, info);
	if (info->facing == '\0')
		return (ft_printf(MAP_NSTART), false);
	if (!incased(g->map, g, info))
		return (ft_printf(MAP_INC), false);
	return (true);
}
