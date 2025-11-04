/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:11:23 by mdalloli          #+#    #+#             */
/*   Updated: 2025/10/30 15:01:31 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*Aggiunge una riga alla mappa del gioco, 
allocando l’array grid se non ancora esistente
Ogni chiamata inserisce una nuova riga duplicata e 
incrementa l’altezza della mappa*/
void	add_map_line(t_game *game, char *line)
{
	static int	i = 0;

	if (!game->map.grid)
	{
		game->map.grid = ft_calloc(1000, sizeof(char *));
		game->map.height = 0;
	}
	game->map.grid[i++] = ft_strdup(line);
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
				game->player.x = x + 0.5;
				game->player.y = y + 0.5;
				game->player.dir = game->map.grid[y][x];
			}
		}
	}
	if (!found)
		print_error("No player position found");
}

/*Controlla che la mappa sia completamente chiusa da muri
Se trova spazi aperti vicino a celle percorribili o al giocatore, genera un errore*/
static void	check_closed(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			char c = game->map.grid[y][x];
			if (c == '0' || is_player_char(c))
			{
				if (y == 0 || x == 0
					|| !game->map.grid[y + 1]
					|| x >= (int)ft_strlen(game->map.grid[y + 1])
					|| game->map.grid[y - 1][x] == ' '
					|| game->map.grid[y][x - 1] == ' '
					|| game->map.grid[y][x + 1] == ' ')
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
