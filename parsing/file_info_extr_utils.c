/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_info_extr_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:44:16 by francema          #+#    #+#             */
/*   Updated: 2025/11/24 19:34:45 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

char	*clean_value(char *line)
{
	char	*r;
	int		i;
	int		j;

	r = NULL;
	i = 0;
	j = 0;
	i = (int)ft_skip_spaces(line, i);
	if (line[i] == '\0')
		return (ft_printf(ELE_EMPTY), NULL);
	r = &line[i];
	while (!ft_ispace(line[i]) && line[i] != '\0')
		i++;
	j = ft_skip_spaces(&line[i], j);
	if (line[i + j] != '\0')
		return (ft_printf(ELE_VAL), NULL);
	line[i] = '\0';
	return (r);
}

//COLOR EXTRACTION UTILS
//checks if the syntax is correct
bool	check_color_syntax(char *s)
{
	bool	comma;
	int		i;

	comma = false;
	i = 0;
	if (s[i] == ',')
		return (false);
	while (s[i])
	{
		if (s[i] == ',')
		{
			if (comma)
				return (false);
			comma = true;
		}
		else
			comma = false;
		i++;
	}
	if (comma)
		return (false);
	return (true);
}

bool	is_int(char *s)
{
	if (!*s)
		return (false);
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (false);
		s++;
	}
	return (true);
}

//checks if the color is made by digits and is in the right range
bool	check_int(char **rgbs, int *r, int *g, int *b)
{
	int	i;

	i = 0;
	if (ft_matlen((void **)rgbs) != 3)
		return (false);
	while (rgbs[i])
	{
		if (!is_int(rgbs[i]))
			return (false);
		i++;
	}
	*r = ft_atoi(rgbs[0]);
	*g = ft_atoi(rgbs[1]);
	*b = ft_atoi(rgbs[2]);
	if (*r < 0 || *r > 255
		|| *g < 0 || *g > 255
		|| *b < 0 || *b > 255)
		return (false);
	return (true);
}

int	convert_color(char *s)
{
	int		r;
	int		g;
	int		b;
	char	**rgbs;//rgb components

	r = 0;
	g = 0;
	b = 0;
	if (!check_color_syntax(s))
		return (ft_printf(CLR_SYN), -1);
	rgbs = ft_split(s, ',');
	if (!rgbs)
		return (ft_printf(E_ALLOC), -1);
	if (!check_int(rgbs, &r, &g, &b))
		return (ft_printf(CLR_VAL), -1);
	return ((r << 16) | (g << 8) | b);
}
