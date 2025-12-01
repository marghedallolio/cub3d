/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 20:04:44 by francema          #+#    #+#             */
/*   Updated: 2025/12/01 17:43:14 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

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
		len = ft_matlen((void **)mat);
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

//UTILS FUN
bool	is_empty(char *str)
{
	int	i;

	i = 0;
	i = (int)ft_skip_spaces(str, i);
	if (str[i] == '\0')
		return (true);
	return (false);
}
