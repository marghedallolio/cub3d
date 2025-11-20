/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:11:17 by mdalloli          #+#    #+#             */
/*   Updated: 2025/11/20 18:19:47 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

/*Controlla che tutte le texture e i colori del pavimento e del soffitto
siano stati definiti correttamente, altrimenti genera un errore*/
static void	check_textures_and_colors(t_game *game)
{
	if (!game->textures.north || !game->textures.south
		|| !game->textures.west || !game->textures.east)
		print_error("Missing texture(s)");
	if (game->floor.r == -1 || game->ceiling.r == -1)
		print_error("Missing floor or ceiling color");
}

/*Legge e analizza un file .cub linea per linea, popolando la struttura t_game
Dopo il parsing verifica che texture e colori siano presenti e
chiama validate_map().*/
int	parse_file(char *filename, t_game *game)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		print_error("Cannot open file");
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] != '\n' && line[0] != '\0')
			parse_line(line, game);
//		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	check_textures_and_colors(game);
	validate_map(game);
	return (1);
}
