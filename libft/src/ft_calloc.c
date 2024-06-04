/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rilliano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:53:45 by rilliano          #+#    #+#             */
/*   Updated: 2023/02/03 16:16:26 by rilliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*arr;
	size_t	tot;
	size_t	i;

	tot = size * count;
	if (size != 0 && tot / size != count)
		return (0);
	else if (count != 0 && tot / count != size)
		return (0);
	arr = (void *)malloc(tot);
	if (!arr)
		return (0);
	i = 0;
	while (i < tot)
	{
		*(char *)(arr + i) = 0;
		i++;
	}
	return (arr);
}
