/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rilliano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 16:05:59 by rilliano          #+#    #+#             */
/*   Updated: 2023/01/30 16:16:27 by rilliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	len_int(long int n)
{
	int			len;
	long int	b;

	b = n;
	len = 0;
	if (b < 0)
	{
		b *= -1;
		len++;
	}
	else if (b == 0)
		return (1);
	while (b > 0)
	{
		b /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char		*strn;
	int			i;
	long int	b;

	b = (long int)n;
	i = len_int(b);
	strn = (char *)malloc((i + 1) * sizeof(char));
	if (!strn)
		return (0);
	strn[i--] = '\0';
	if (b == 0)
		strn[0] = '0';
	else if (b < 0)
	{
		b *= -1;
		strn[0] = '-';
	}
	while (b > 0)
	{
		strn[i] = (b % 10) + 48;
		b /= 10;
		i--;
	}
	return (strn);
}
