/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:11:21 by mdalloli          #+#    #+#             */
/*   Updated: 2025/10/29 16:06:33 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*Estrae il percorso della texture da una linea del tipo 
"NO ./path/to/texture.xpm"
Restituisce una copia della stringa del percorso*/
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

/*Analizza una singola linea del file .cub e 
aggiorna i campi corrispondenti di t_game
Riconosce texture, colori e inizio della mappa.*/
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
