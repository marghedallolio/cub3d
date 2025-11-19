/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:11:14 by mdalloli          #+#    #+#             */
/*   Updated: 2025/11/19 14:55:25 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

/*Analizza una stringa RGB nel formato "R,G,B" e
restituisce una struttura t_color
Ogni valore deve essere compreso tra 0 e 255, altrimenti genera un errore.*/
t_color parse_color(char *str)
{
	t_color	color;
	char	**split;

	split = ft_split(str, ',');
	if (!split || !split[0] || !split[1] || !split[2])
		print_error("Invalid color format");
	color.r = ft_atoi(split[0]);
	color.g = ft_atoi(split[1]);
	color.b = ft_atoi(split[2]);
	if (color.r < 0 || color.r > 255
		|| color.g < 0 || color.g > 255
		|| color.b < 0 || color.b > 255)
		print_error("Color out of range [0,255]");
	free_split(split);
	return (color);
}
