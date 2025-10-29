/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:51:32 by mdalloli          #+#    #+#             */
/*   Updated: 2025/10/29 16:06:58 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*Stampa un messaggio di errore su stderr con prefisso "Error\n"
e termina il programma con codice di uscita EXIT_FAILURE.*/
void	print_error(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putchar_fd('\n', 2);
	exit(EXIT_FAILURE);
}
