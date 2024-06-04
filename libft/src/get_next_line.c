/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rilliano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 13:47:15 by rilliano          #+#    #+#             */
/*   Updated: 2023/11/10 22:32:13 by rilliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_next(char *prev, int len)
{
	char	*n_line;
	int		i;

	if (!prev[len])
	{
		free(prev);
		return (NULL);
	}
	n_line = ft_calloc((ft_strlen(prev) - len + 1), sizeof(char));
	i = 0;
	while (prev[len + i])
	{
		n_line[i] = prev[len + i];
		i++;
	}
	free(prev);
	return (n_line);
}

char	*ft_line(char *start, int len)
{
	char	*line;
	int		i;

	line = ft_calloc(len + 1, sizeof(char));
	i = 0;
	while (i < len)
	{
		line[i] = start[i];
		i++;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*start[FOPEN_MAX];
	char		*line;
	int			len;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	start[fd] = ft_read_file(fd, start[fd]);
	len = 0;
	if (!start[fd] || !start[fd][len])
		return (NULL);
	while (start[fd][len] != '\0' && start[fd][len] != '\n')
		len++;
	len += (start[fd][len] == '\n');
	line = ft_line(start[fd], len);
	start[fd] = ft_next(start[fd], len);
	return (line);
}
