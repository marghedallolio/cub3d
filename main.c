/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:11:32 by mdalloli          #+#    #+#             */
/*   Updated: 2025/10/29 15:20:36 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		print_error("Usage: ./cub3d <map.cup>");
	ft_bzero(&game, sizeof(t_game));
	game.floor.r = -1;
	game.ceiling.r = -1;
	parse_file(argv[1], &game);
	return (0);
}
