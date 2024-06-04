/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rilliano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 17:52:39 by rilliano          #+#    #+#             */
/*   Updated: 2023/01/20 18:05:50 by rilliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*copy(char const *src, char *dst, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		*dst = src[i];
		dst++;
		i++;
	}
	return (dst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		s1_len;
	int		s2_len;
	char	*jo;

	if (!s1 && !s2)
		return (0);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	jo = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!jo)
		return (0);
	jo = copy(s1, jo, s1_len);
	jo = copy(s2, jo, s2_len);
	*jo = '\0';
	return (jo - s1_len - s2_len);
}
