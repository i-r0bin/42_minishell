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

void	handle_fork(t_data *data, int i, int fd[2])
{
	data->pid = fork();
	if (data->pid == -1)
		handle_error("fork error");
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
