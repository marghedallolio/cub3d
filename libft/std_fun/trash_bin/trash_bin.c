/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash_bin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:06:44 by francema          #+#    #+#             */
/*   Updated: 2025/11/03 15:22:59 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	error_handling(t_list **lis)
{
	ft_lstclear(lis, free);
	*lis = NULL;
}

void	*ft_malloc(size_t size, bool BIG_RED_BUTTON)
{
	static t_list	*lis = NULL;
	t_list			*tmp;
	void			*new;

	if (BIG_RED_BUTTON)
	{
		error_handling(&lis);
		return (NULL);
	}
	new = malloc(size);
	if (!new)
	{
		error_handling(&lis);
		return (NULL);
	}
	tmp = ft_lstnew(new);
	if (!tmp)
	{
		free(new);
		error_handling(&lis);
		return (NULL);
	}
	ft_lstadd_back(&lis, tmp);
	return (new);
}
