/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rilliano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 17:31:15 by rilliano          #+#    #+#             */
/*   Updated: 2023/01/23 19:26:02 by rilliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*sub;

	if (!s)
		return (0);
	if (len >= ft_strlen(s))
		len = ft_strlen(s);
	sub = (char *)malloc((len + 1) * sizeof(char));
	if (!sub)
		return (0);
	i = 0;
	j = 0;
	while (s[i] != '\0' && j < len)
	{
		if (i >= start)
		{
			sub[j] = s[i];
			j++;
		}
		i++;
	}
	sub[j] = '\0';
	return (sub);
}
