/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rilliano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:28:18 by rilliano          #+#    #+#             */
/*   Updated: 2023/01/30 20:45:31 by rilliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	n_words(char const *s, char c)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			n++;
		i++;
	}
	return (n);
}

int	getlen_w(char const *s, char c)
{
	int	len;

	len = 0;
	while (s[len] != '\0' && s[len] != c)
		len++;
	return (len);
}

char	*cpy(char const *ptr, char *dst, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		dst[i] = ptr[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

const char	*skip_c(const char *s, char c)
{
	while (*s == c)
		s++;
	return (s);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		n;
	int		j;
	int		size;

	if (!s)
		return (0);
	n = n_words(s, c);
	arr = (char **)malloc((n + 1) * sizeof(char *));
	if (!arr)
		return (0);
	j = 0;
	while (j < n)
	{
		s = skip_c(s, c);
		size = getlen_w(s, c);
		arr[j] = (char *)malloc((size + 1) * sizeof(char));
		if (!arr[j])
			return (0);
		arr[j] = cpy(s, arr[j], size);
		s = s + size;
		j++;
	}
	arr[j] = 0;
	return (arr);
}
