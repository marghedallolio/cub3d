/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:11:23 by mdalloli          #+#    #+#             */
/*   Updated: 2025/11/20 17:57:31 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

/*Aggiunge una riga alla mappa del gioco,
allocando l’array grid se non ancora esistente
Ogni chiamata inserisce una nuova riga duplicata e
incrementa l’altezza della mappa*/
void	add_map_line(t_game *game, char *line)
{
	int	i;
	int	len;

	i = 0;
	if (!line)
		return ;
	if (!game->map.grid)
	{
		game->map.grid = ft_calloc(1000, sizeof(char *));
		if (!game->map.grid)
			print_error("Memory allocation failed");
		game->map.height = 0;
	}
	i = game->map.height;
	if (i >= 1000)
		print_error("Map too large");
	game->map.grid[i] = ft_strdup(line);
	if (!game->map.grid[i])
		print_error("Memory allocation failed");
	i++;
	game->map.height++;
	len = ft_strlen(line);
	if (len > game->map.width)
		game->map.width = len;
}

/*Controlla che la mappa sia completamente chiusa da muri
Se trova spazi aperti vicino a celle percorribili o al giocatore,
genera un errore*/
/* static void	check_closed(t_game *game)
{
	int		y;
	int		x;
	size_t	len;
	char	c;

	y = 0;
	while (y < game->map.height)
	{
		if (!game->map.grid[y])
			print_error("Invalid map line");
		len = ft_strlen(game->map.grid[y]);
		x = 0;
		while (game->map.grid[y][x])
		{
			c = game->map.grid[y][x];
			if (c == '0' || is_player_char(c))
			{
				if (y == 0 || x == 0 || y == game->map.height - 1
					|| x == (int)len - 1)
					print_error("Map not closed by walls");
				if (!game->map.grid[y - 1] || !game->map.grid[y + 1]
					|| x >= (int)ft_strlen(game->map.grid[y - 1])
					|| x >= (int)ft_strlen(game->map.grid[y + 1])
					|| game->map.grid[y - 1][x] == ' '
					|| game->map.grid[y][x - 1] == ' '
					|| game->map.grid[y][x + 1] == ' '
					|| game->map.grid[y + 1][x] == ' ')
					print_error("Map not closed by walls");
			}
			x++;
		}
		y++;
	}
} */

static void	check_cell(t_game *game, int y, int x)
{
	size_t	len;

	if (game->map.grid[y][x] != '0' && !is_player_char(game->map.grid[y][x]))
		return ;
	len = ft_strlen(game->map.grid[y]);
	if (y == 0 || x == 0 || y == game->map.height - 1
		|| x == (int)len - 1)
		print_error("Map not closed by walls");
	if (!game->map.grid[y - 1] || !game->map.grid[y + 1])
		print_error("Map not closed by walls");
	if (x >= (int)ft_strlen(game->map.grid[y - 1])
		|| x >= (int)ft_strlen(game->map.grid[y + 1]))
		print_error("Map not closed by walls");
	if (game->map.grid[y - 1][x] == ' ' || game->map.grid[y][x - 1] == ' '
		|| game->map.grid[y][x + 1] == ' '
		|| game->map.grid[y + 1][x] == ' ')
		print_error("Map not closed by walls");
}

static void	check_closed(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map.height)
	{
		if (!game->map.grid[y])
			print_error("Invalid map line");
		x = 0;
		while (game->map.grid[y][x])
		{
			check_cell(game, y, x);
			x++;
		}
		y++;
	}
}

/*Valida la mappa completa assicurandosi che ci sia un giocatore e
che sia chiusa da muri*/
void	validate_map(t_game *game)
{
	find_player(game);
	check_closed(game);
}
