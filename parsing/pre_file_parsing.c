/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_file_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:05:13 by francema          #+#    #+#             */
/*   Updated: 2025/11/25 19:08:31 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

bool	openable(char *path, int *fd)
{
	int		tmp_fd;
	char	buf[1];
	ssize_t	byt_r;

	tmp_fd = 0;
	tmp_fd = open(path, O_RDONLY);
	if (tmp_fd < 0)
		return (perror(FILE_OPEN), false);
	byt_r = read(tmp_fd, buf, 1);
	if (byt_r < 0)
		return (perror(FILE_READ), close(tmp_fd), false);
	if (byt_r == 0)
		return (ft_printf(FILE_EMPTY), close(tmp_fd), false);
	close(tmp_fd);
	*fd = open(path, O_RDONLY);
	return (true);
}

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
		return (ft_printf(E_ALLOC), NULL);
	while (mat && mat[i])
	{
		new_mat[i] = mat[i];
		i++;
	}
	new_mat[i] = line;
	new_mat[i + 1] = NULL;
	return (new_mat);
}

char	**file_coping(char *path)
{
	char	**file;
	char	*line;
	int		fd;

	fd = 0;
	file = NULL;
	line = NULL;
	if (!openable(path, &fd))
		return (false);
	line = get_next_line(fd);
	while (line)
	{
		file = add_line(file, line);
		if (!file)
			return (close(fd), NULL);
		line = get_next_line(fd);
	}
	return (file);
}

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
	ft_printf(FILE_FORM, format);
	return (false);
}

bool	args_check(int ac, char **av)
{
	if (ac != 2)
		return (printf("%s", E_ARG), false);
	if (!check_format(av[1], ".cub"))
		return (false);
	return (true);
}
