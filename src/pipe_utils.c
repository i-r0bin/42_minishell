/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rilliano <rilliano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 03:22:37 by ppezzull          #+#    #+#             */
/*   Updated: 2024/07/23 18:18:44 by rilliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_pipes(t_data *data)
{
	int	len;
	int	i;

	get_pipe_len(data);
	data->pipes_cmd = ft_calloc(data->pipe_num + 1, sizeof(char *));
	i = 0;
	len = 0;
	while (data->args[i])
	{
		if (ft_strncmp(data->args[i], "|", 2) == 0 && i > 0)
			len++;
		else if (!data->pipes_cmd[len])
			data->pipes_cmd[len] = ft_strdup(data->args[i]);
		else
		{
			data->pipes_cmd[len] = ft_append_str(data->pipes_cmd[len], " ");
			data->pipes_cmd[len] = ft_append_str(data->pipes_cmd[len],
					data->args[i]);
		}
		i++;
	}
}

void	get_pipe_len(t_data *data)
{
	int	i;

	i = 0;
	while (data->args[i])
	{
		if (ft_strncmp(data->args[i], "|", 2) == 0)
			data->pipe_num++;
		i++;
	}
}

void	set_input_output(t_data *data, int i, int fd[2])
{
	if (data->fd_pipe[0] != -1)
	{
		dup2(data->fd_pipe[0], STDIN_FILENO);
		close(data->fd_pipe[0]);
	}
	if (i < data->pipe_num - 1)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	if (fd[0] != -1)
		close(fd[0]);
}

void	set_fd_pipe(t_data *data, int fd[2])
{
	if (data->fd_pipe[0] != -1)
		close(data->fd_pipe[0]);
	if (fd[1] != -1)
		close(fd[1]);
	data->fd_pipe[0] = fd[0];
	data->fd_pipe[1] = fd[1];
}
