/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:24:34 by francema          #+#    #+#             */
/*   Updated: 2025/12/04 15:35:38 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

//FLOOD FILL ALGORITHM TO CHECK IF THE MAP IS ENCLOSED
bool	bool_fill(char **map, t_game *g, int y, int x)
{
	if (y < 0 || y >= g->map_h || x < 0 || x >= g->map_w)
		return (false);
	if (map[y][x] != '0')
		return (true);
	map[y][x] = 'V';
	return (bool_fill(map, g, y + 1, x)
		&& bool_fill(map, g, y - 1, x)
		&& bool_fill(map, g, y, x + 1)
		&& bool_fill(map, g, y, x - 1));
}

//CLEAN UP THE MAP FROM '0's TO SPACES AFTER FLOOD FILL
void	clean_up(t_game *g)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (g->map[i])
	{
		j = 0;
		while (g->map[i][j])
		{
			if (g->map[i][j] == '0')
				g->map[i][j] = ' ';
			j++;
		}
		i++;
	}
}

//COPY A ROW FROM THE ORIGINAL MAP TO THE NORMALIZED MAP
void	copy_row(char *r, char *s, int y, t_info_map *info)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\n' && s[i] != '\r')
	{
		if (ft_strchr("NSEW", s[i]))
		{
			info->facing = s[i];
			info->p_x = i + 0.5;
			info->p_y = y + 0.5;
			r[i] = '0';
		}
		else if (!ft_ispace(s[i]))
			r[i] = s[i];
		i++;
	}
}

//CHECK FOR MULTIPLE PLAYER START POSITIONS
bool	multiple_start(char c)
{
	static bool	start;

	if (ft_strchr("NSWE", c))
	{
		if (start)
			return (true);
		else
			start = true;
	}
	return (false);
}

//SEARCH INVALID CHARS/PATTERNS(DUBLE START)
bool	invalid_char(char *s, t_game *g)
{
	int	i;
	int	line_len;

	i = 0;
	line_len = 0;
	while (s[i])
	{
		if (multiple_start(s[i]))
			return (ft_printf(MAP_MSTART), true);
		if (!ft_strchr("01NSWE \t\n\r\v\f", s[i]))
			return (ft_printf(MAP_INV), true);
		if (s[i] != '\n' && s[i] != '\r')
			line_len++;
		i++;
	}
	if (g->map_w < line_len)
		g->map_w = line_len;
	return (false);
}
