/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:11:21 by mdalloli          #+#    #+#             */
/*   Updated: 2025/10/29 15:41:51 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*get_path(char *line)
{
	char	**split;
	char	*path;

	split = ft_split(line, ' ');
	if (!split || !split[1])
		print_error("Invalid texture path");
	path = ft_strdup(split[1]);
	free_split(split);
	return (path);
}

void	parse_line(char *line, t_game *game)
{
	if (is_empty_line(line))
		return ;
	else if (ft_strncmp(line, "NO ", 3) == 0)
		game->textures.north = get_path(line);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		game->textures.south = get_path(line);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		game->textures.west = get_path(line);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		game->textures.east = get_path(line);
	else if (ft_strncmp(line, "F ", 2) == 0)
		game->floor = parse_color(line + 2);
	else if (ft_strncmp(line, "C ", 2) == 0)
		game->ceiling = parse_color(line + 2);
	else
	{
		game->map_started = 1;
		add_map_line(game, line);
	}
}
