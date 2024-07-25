/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rilliano <rilliano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 03:22:37 by ppezzull          #+#    #+#             */
/*   Updated: 2024/07/23 18:23:33 by rilliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_pipe(t_data *data)
{
	split_pipes(data);
	handle_pipes(data);
	wait_and_save_exit_status(data);
	while (wait(NULL) > 0)
	{
	}
	free_array(data->pipes_cmd);
	data->pipes_cmd = NULL;
	data->pipe_num = 1;
}

void	handle_pipes(t_data *data)
{
	int	i;
	int	fd[2];

	i = 0;
	while (i < data->pipe_num)
	{
		if (i < data->pipe_num - 1)
		{
			if (pipe(fd) == -1)
				handle_pipe_error("pipe error");
		}
		else
		{
			fd[0] = -1;
			fd[1] = -1;
		}
		handle_fork(data, i, fd);
		i++;
	}
}

void	handle_fork(t_data *data, int i, int fd[2])
{
	data->pid = fork();
	if (data->pid == -1)
		handle_pipe_error("fork error");
	if (data->pid == 0)
		execute_child_process(data, i, fd);
	else
		set_fd_pipe(data, fd);
}

void	execute_child_process(t_data *data, int i, int fd[2])
{
	char	**envp;
	t_data	child_data;

	set_input_output(data, i, fd);
	envp = env_to_array(data->env);
	init_data(&child_data, envp);
	child_data.line = ft_strdup(data->pipes_cmd[i]);
	parse_line(&child_data);
	free_data(&child_data);
	free_array(envp);
	exit(child_data.status);
}
