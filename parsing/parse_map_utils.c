/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 15:16:29 by mdalloli          #+#    #+#             */
/*   Updated: 2025/11/20 15:18:40 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

/*Restituisce 1 se il carattere rappresenta una
direzione del giocatore (N, S, E o W), altrimenti restituisce 0.*/
int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

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

/*Cerca la posizione iniziale del giocatore nella mappa e
la salva nella struttura t_game
Genera un errore se non viene trovata o se ce ne sono più di una.*/
void	find_player(t_game *game)
{
	int	y;
	int	x;
	int	found;

	found = 0;
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
