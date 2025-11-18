/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 11:03:34 by francema          #+#    #+#             */
/*   Updated: 2025/11/18 16:49:54 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	init_ray(t_ray *ray, t_player *p, int x)
{
	double camera_x;

	// Normalizza X in coordinate camera da -1 a 1
	camera_x = 2 * x / (double)SCREEN_W - 1.0;

	// Direzione del raggio
	ray->ray_dir_x = p->dir_x + p->plane_x * camera_x;
	ray->ray_dir_y = p->dir_y + p->plane_y * camera_x;

	// In quale cella della mappa si trova il giocatore
	ray->map_x = (int)p->pos_x;
	ray->map_y = (int)p->pos_y;

	// Lunghezza dei raggi dal punto a passo successivo in X/Y
	ray->delta_dist_x = (ray->ray_dir_x == 0) ? 1e30 : fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = (ray->ray_dir_y == 0) ? 1e30 : fabs(1 / ray->ray_dir_y);

	// Setup variabili DDA
	ray->hit = 0;

	// prepare steps
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (p->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - p->pos_x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (p->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - p->pos_y) * ray->delta_dist_y;
	}
}

/** Implementa l'algoritmo DDA (Digital Differential Analyzer) per il raycasting
Avanza il raggio cella per cella nella direzione stabilita (X o Y),
scegliendo il prossimo passo in base alla distanza minima da un lato
della griglia. Si ferma quando incontra un muro ('1') oppure esce dai
limiti della mappa. Alla fine imposta:
- ray->hit = 1  (muro trovato)
- ray->side = 0 (impatto su lato verticale)
- ray->side = 1 (impatto su lato orizzontale)*/
void	perform_dda(t_ray *ray, t_map *map)
{
	ray->hit = 0;
	while (ray->hit == 0)
	{
		// Avanza nella direzione X o Y a seconda di chi è più vicino
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0; //lato verticale
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1; //lato orizzontale
		}
		// Controllo out-of-bounds per evitare crash
		if (ray->map_x < 0 || ray->map_x >= map->width
			|| ray->map_y < 0 || ray->map_y >= map->height)
		{
			ray->hit = 1;
			break ;
		}
		// Se trovi un muro, ferma il DDA
		if (map->grid[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

void	raycast(t_game *game)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < SCREEN_W)
	{
		init_ray(&ray, game->p1, x);
		perform_dda(&ray, &game->map);
		compute_wall_distance(&ray, game->p1);
		draw_vertical_line(game, &ray, x);
		x++;
	}
}
