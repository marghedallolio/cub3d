/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 20:04:44 by francema          #+#    #+#             */
/*   Updated: 2025/11/21 20:07:17 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

bool	check_format(char *path, char *format)
{
	int	len;

	len = 0;
	len = ft_strlen(path);
	if (len >= 4)
	{
		if (ft_strcmp(&path[len - 4], format) == 0)
			return (true);
	}
	ft_printf("Error: Invalid file format. Expected %s\n", format);
	return (false);
}

//UTILS FUNCTION
char	**add_line(char **mat, char *line)
{
	char	**new_mat;
	int		len;
	int		i;

	new_mat = NULL;
	len = 0;
	i = 0;
	if (mat)
		len = ft_matlen(mat);
	new_mat = ft_malloc((len + 2) * sizeof(char *), false);
	if (!new_mat)
		return (NULL);
	while (mat && mat[i])
	{
		new_mat[i] = mat[i];
		i++;
	}
	new_mat[i] = line;
	new_mat[i + 1] = NULL;
	return (new_mat);
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
