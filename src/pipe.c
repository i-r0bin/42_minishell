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

void	split_pipes(t_data *data)
{
	int	len;
	int	i;

	i = 0;
	while (data->args[i])
	{
		if (ft_strncmp(data->args[i], "|", 2) == 0)
			data->pipe_num++;
		i++;
	}
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

void	exec_pipe(t_data *data)
{
	int		fd[2];
	int		prev_fd;
	int		i;
	t_data	child_data;
	pid_t	pid;

	split_pipes(data);
	prev_fd = -1;
	i = 0;
	while (i < data->pipe_num)
	{
		if (i < data->pipe_num - 1)
		{
			if (pipe(fd) == -1)
			{
				perror("pipe error");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			fd[0] = -1;
			fd[1] = -1;
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork error");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (i < data->pipe_num - 1)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
			}
			if (fd[0] != -1)
				close(fd[0]);
			init_data(&child_data, data->env_arr);
			child_data.line = ft_strdup(data->pipes_cmd[i]);
			parse_line(&child_data);
			free_data(&child_data);
			free(data->pipes_cmd);
			exit(EXIT_SUCCESS);
		}
		else
		{
			if (prev_fd != -1)
				close(prev_fd);
			if (fd[1] != -1)
				close(fd[1]);
			prev_fd = fd[0];
		}
		i++;
	}
	while (wait(NULL) > 0)
	{
	}
}
