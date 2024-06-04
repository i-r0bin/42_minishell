/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rilliano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:35:52 by rilliano          #+#    #+#             */
/*   Updated: 2023/11/10 22:36:58 by rilliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_join(char *s1, char *s2, int len)
{
	char	*jo;
	int		s1len;

	if (!s1)
		s1 = ft_calloc(1, 1);
	if (!s1 || !s2)
		return (NULL);
	s1len = ft_strlen(s1);
	jo = ft_calloc(s1len + len + 1, sizeof(char));
	ft_memcpy(jo, s1, s1len);
	ft_memcpy((jo + s1len), s2, len);
	free(s1);
	return (jo);
}

char	*ft_read_file(int fd, char *start)
{
	char	*buffer;
	int		bytes;

	buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	while (1)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == 0)
			break ;
		if (bytes == -1)
		{
			free(buffer);
			return (NULL);
		}
		start = ft_join(start, buffer, bytes);
		if (buffer[bytes] == '\n')
			break ;
	}
	free(buffer);
	return (start);
}
