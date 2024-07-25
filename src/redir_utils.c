/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rilliano <rilliano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 03:22:37 by ppezzull          #+#    #+#             */
/*   Updated: 2024/07/21 19:57:43 by rilliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_file_permissions(char *file, int flags)
{
	int	fd;

	fd = open(file, flags, 0644);
	if (fd < 0)
	{
		perror("Permission denied");
		return (-1);
	}
	close(fd);
	return (0);
}

void	reformat_redir_args(t_data *data, int index)
{
	free(data->args[index]);
	data->args[index] = ft_calloc(1, 1);
	free(data->args[index + 1]);
	data->args[index + 1] = ft_calloc(1, 1);
	remove_null_args(data);
	if (!data->args[0])
	{
		free(data->args);
		data->args = NULL;
	}
}

void	exec_here_input(t_data *data, int index)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		data->line = ft_append_str(data->line, "\n");
		data->line = ft_append_str(data->line, line);
		if (ft_strncmp(line, data->args[index + 1],
				ft_strlen(data->args[index + 1]) + 1) == 0)
		{
			data->line = ft_append_str(data->line, "\n");
			free(line);
			break ;
		}
		free(line);
	}
}
