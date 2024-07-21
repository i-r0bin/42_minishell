/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppezzull <ppezzull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 03:22:37 by ppezzull          #+#    #+#             */
/*   Updated: 2024/07/21 03:22:40 by ppezzull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_here_documents(t_data *data, int index);

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

void	exec_here_documents(t_data *data, int index)
{
	int		fd[2];
	int		prev_fd;

	if (data->args[index + 1] == NULL)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `newline'",
			2);
		return ;
	}
	prev_fd = dup(1);
	pipe(fd);
	dup2(0, fd[0]);
	exec_here_input(data, index);
	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
	free(data->args[index]);
	data->args[index] = ft_calloc(1, 1);
	free(data->args[index + 1]);
	data->args[index + 1] = ft_calloc(1, 1);
	remove_null_args(data);
	exec_cmd(data);
	dup2(prev_fd, 1);
	close(prev_fd);
}