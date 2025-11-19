/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:11:23 by mdalloli          #+#    #+#             */
/*   Updated: 2025/11/19 14:55:38 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

/*Imposta la direzione del player (dir_x, dir_y) 
in base al carattere trovato nella mappa e imposta il vettore camera 
(plane_x, plane_y) per il raycasting*/
void	init_player_direction(t_player **p, char c)
{
	(*p)->dir_x = 0;
	(*p)->dir_y = 0;
	(*p)->plane_x = 0;
	(*p)->plane_y = 0;

	if (c == 'N')
	{
		(*p)->dir_y = -1;
		(*p)->plane_x = 0.66;
	}
	else if (c == 'S')
	{
		(*p)->dir_y = 1;
		(*p)->plane_x = -0.66;
	}
	else if (c == 'E')
	{
		(*p)->dir_x = 1;
		(*p)->plane_y = 0.66;
	}
	else if (c == 'W')
	{
		(*p)->dir_x = -1;
		(*p)->plane_y = -0.66;
	}
}

/*Aggiunge una riga alla mappa del gioco,
allocando l’array grid se non ancora esistente
Ogni chiamata inserisce una nuova riga duplicata e
incrementa l’altezza della mappa*/
void add_map_line(t_game *game, char *line)
{
	static int i = 0;

	if (!line)
		return;

	if (!game->map.grid)
	{
		game->map.grid = ft_calloc(1000, sizeof(char *));
		if (!game->map.grid)
			print_error("Memory allocation failed");
		game->map.height = 0;
		i = 0; // Reset the counter when allocating new grid
	}

	if (i >= 1000)
		print_error("Map too large");

	game->map.grid[i] = ft_strdup(line);
	if (!game->map.grid[i])
		print_error("Memory allocation failed");
	i++;
	game->map.height++;
}

/*Restituisce 1 se il carattere rappresenta una
direzione del giocatore (N, S, E o W), altrimenti restituisce 0.*/
static int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

/*Cerca la posizione iniziale del giocatore nella mappa e
la salva nella struttura t_game
Genera un errore se non viene trovata o se ce ne sono più di una.*/
static void	find_player(t_game *game)
{
	int	y;
	int	x;
	int	found = 0;

	y = -1;
	while (++y < game->map.height)
	{
		x = -1;
		while (game->map.grid[y][++x])
		{
			if (is_player_char(game->map.grid[y][x]))
			{
				if (found)
					print_error("Multiple player positions");
				found = 1;
				game->p1->pos_x = x + 0.5;
				game->p1->pos_y = y + 0.5;
				init_player_direction(&game->p1, game->map.grid[y][x]);
			}
		}
	}
	if (!found)
		print_error("No player position found");
}

/*Controlla che la mappa sia completamente chiusa da muri
Se trova spazi aperti vicino a celle percorribili o al giocatore, genera un errore*/
static void check_closed(t_game *game)
{
	int y;
	int x;
	size_t len;

	y = 0;
	while (y < game->map.height)
	{
		if (!game->map.grid[y])
			print_error("Invalid map line");

		len = ft_strlen(game->map.grid[y]);
		x = 0;
		while (game->map.grid[y][x])
		{
			char c = game->map.grid[y][x];
			if (c == '0' || is_player_char(c))
			{
				// Check if we're at map boundaries
				if (y == 0 || x == 0 || y == game->map.height - 1 || x == (int)len - 1)
					print_error("Map not closed by walls");

				// Check if adjacent cells exist and are valid
				if (!game->map.grid[y - 1] || !game->map.grid[y + 1] ||
					x >= (int)ft_strlen(game->map.grid[y - 1]) ||
					x >= (int)ft_strlen(game->map.grid[y + 1]) ||
					game->map.grid[y - 1][x] == ' ' ||
					game->map.grid[y][x - 1] == ' ' ||
					game->map.grid[y][x + 1] == ' ' ||
					game->map.grid[y + 1][x] == ' ')
					print_error("Map not closed by walls");
			}
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
