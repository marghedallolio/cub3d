/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 16:49:25 by francema          #+#    #+#             */
/*   Updated: 2025/11/21 20:05:00 by francema         ###   ########.fr       */
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
	{
		ft_printf("Error: Cannot open file %s\n", path);
		return (false);
	}
	byt_r = read(tmp_fd, buf, 1);
	if (byt_r < 0)
	{
		ft_printf("Error: Cannot read file %s\n", path);
		close(tmp_fd);
		return (false);
	}
	if (byt_r == 0)
	{
		ft_printf("Error: File %s is empty\n", path);
		close(tmp_fd);
		return (false);
	}
	close(tmp_fd);
	*fd = open(path, O_RDONLY);
	return (true);
}
