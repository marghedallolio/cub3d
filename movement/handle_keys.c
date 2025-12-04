/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 15:57:30 by mdalloli          #+#    #+#             */
/*   Updated: 2025/12/04 15:59:17 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	handle_key_press(int keycode, t_game *g)
{
	int	mask;

	mask = 0;
	if (keycode == ESC)
		return (close_window(g), 0);
	mask |= (keycode == W) * (1 << 0);
	mask |= (keycode == S) * (1 << 1);
	mask |= (keycode == A) * (1 << 2);
	mask |= (keycode == D) * (1 << 3);
	mask |= (keycode == LEFT_ARROW) * (1 << 4);
	mask |= (keycode == RIGHT_ARROW) * (1 << 5);
	g->key_mask |= mask;
	return (0);
}

int	handle_key_release(int keycode, t_game *g)
{
	int	mask;

	mask = 0;
	mask |= (keycode == W) * (1 << 0);
	mask |= (keycode == S) * (1 << 1);
	mask |= (keycode == A) * (1 << 2);
	mask |= (keycode == D) * (1 << 3);
	mask |= (keycode == LEFT_ARROW) * (1 << 4);
	mask |= (keycode == RIGHT_ARROW) * (1 << 5);
	g->key_mask &= ~mask;
	return (0);
}
