/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rilliano <rilliano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 03:22:37 by ppezzull          #+#    #+#             */
/*   Updated: 2024/07/21 21:17:11 by rilliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	exec_pipe_cmd(t_data *data, char *cmd)
{
	int	i;
	int	redir;

	data->line = ft_strdup(cmd);
	data->cmd = ft_strtrim(data->line, " ");
	if (data->cmd && data->cmd[0])
		data->args = split_args(data->cmd);
	data_env_format(data);
	if (data->args && data->args[0])
	{
		i = 0;
		redir = 0;
		while (data->args[i])
		{
			if ((data->args[i][0] == '<' || data->args[i][0] == '>')
				&& (!data->args[i][1] || data->args[i][1] == '<'
					|| data->args[i][1] == '>'))
				redir = 1;
			i++;
		}
		if (redir)
			exec_redirection(data);
		else
			exec_builtin(data);
	}
}
