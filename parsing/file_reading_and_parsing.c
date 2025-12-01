/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reading_and_parsing.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 16:49:25 by francema          #+#    #+#             */
/*   Updated: 2025/11/24 19:35:27 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static bool	get_element(char *line, t_info_map *info, int nc)
{
	char	*temp;

	temp = ft_strdup(line);
	if (!temp)
		return (ft_printf(E_ALLOC), false);
	temp[nc] = '\0';
	if (nc == 2 && ft_strcmp(temp, "NO") == 0 && !info->n_path)
		info->n_path = line;
	else if (nc == 2 && ft_strcmp(temp, "SO") == 0 && !info->s_path)
		info->s_path = line;
	else if (nc == 2 && ft_strcmp(temp, "EA") == 0 && !info->e_path)
		info->e_path = line;
	else if (nc == 2 && ft_strcmp(temp, "WE") == 0 && !info->w_path)
		info->w_path = line;
	else if (nc == 1 && line[0] == 'F' && !info->f_color)
		info->f_color = line;
	else if (nc == 1 && line[0] == 'C' && !info->c_color)
		info->c_color = line;
	else
		return (false);
	info->e_set++;
	return (true);
}

bool	parse_line(char *line, t_info_map *info, int idx)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	i = ft_skip_spaces(line, i);
	if (line[i] == '\0')
		return (false);
	while (line[i +j] != '\0' && !ft_ispace(line[i + j]))
		j++;
	if (j > 2 || !get_element(&line[i], info, j))
		return (ft_printf(ELE_INV, idx + 1), false);
	return (true);
}

bool	is_empty(char *str)//UTILS FUN
{
	int	i;

	i = 0;
	i = (int)ft_skip_spaces(str, i);
	if (str[i] == '\0')
		return (true);
	return (false);
}

bool	get_file_info(char **file, t_game *g, t_info_map *info)
{
	int	i;

	i = 0;
	while (file[i])
	{
		if (!is_empty(file[i]))
		{
			if (info->e_set == 6)//all elements set, map starts
			{
				g->map = &file[i];
				break;
			}
			if (!parse_line(file[i], info, i))
				return (false);
		}
		i++;
	}
	if (!extract_file_info(info, g))
		return (false);
	return (true);
}


