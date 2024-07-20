/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rilliano <rilliano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:14:37 by rilliano          #+#    #+#             */
/*   Updated: 2024/07/20 14:05:37 by rilliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	isit(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		end;

	if (!s1 || !set)
		return (0);
	i = 0;
	end = ft_strlen(s1) - 1;
	while (s1[i] && isit(s1[i], set))
		i++;
	while (end > 0 && isit(s1[end], set))
		end--;
	if (i <= end)
	{
		end += 1;
		str = ft_substr(s1, i, (end - i));
		return (str);
	}
	str = malloc(sizeof(char));
	if (!str)
		return (0);
	str[0] = 0;
	return (str);
}
