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

void	exec_builtin(t_data *data);
void	exec_bin(t_data *data);
int		exec_bin_path(t_data *data, char **paths);
void	exec_pipe(t_data *data);
void	exec_redirection(t_data *data);

void	exec_builtin(t_data *data)
{
	if (ft_strncmp(data->args[0], "exit", 5) == 0)
		ft_exit(data);
	else if (ft_strncmp(data->args[0], "cd", 3) == 0)
		ft_cd(data);
	else if (ft_strncmp(data->args[0], "pwd", 4) == 0)
		ft_pwd();
	else if (ft_strncmp(data->args[0], "echo", 5) == 0)
		ft_echo(data);
	else if (ft_strncmp(data->args[0], "export", 7) == 0)
		ft_export(data);
	else if (ft_strncmp(data->args[0], "unset", 6) == 0)
		ft_unset(data);
	else if (ft_strncmp(data->args[0], "env", 4) == 0)
		ft_env(data);
	else
		exec_bin(data);
}

void	exec_bin(t_data *data)
{
	char	**paths;
	int		err;

	if (!get_env("PATH", data))
	{
		ft_error(data, data->args[0], "command not found");
		return ;
	}
	if (check_bin(data))
		return ;
	err = 0;
	paths = ft_split(get_env("PATH", data), ':');
	if (execve(data->args[0], data->args, env_to_array(data->env)) == -1)
		err = exec_bin_path(data, paths);
	if (!err)
	{
		ft_error(data, data->args[0], "command not found");
		data->status = 127;
	}
	free_array(paths);
}

int	exec_bin_path(t_data *data, char **paths)
{
	char		*cmd;
	int			pid;
	int			i;
	struct stat	path_stat;

	i = 0;
	while (paths[i])
	{
		cmd = ft_strjoin(ft_strjoin(paths[i], "/"), data->args[0]);
		pid = fork();
		if (pid == 0)
		{
			execve(cmd, data->args, env_to_array(data->env));
			exit(EXIT_FAILURE);
		}
		else
		{
			wait_and_save_exit_status(data);
			if (stat(cmd, &path_stat) == 0)
				return (1);
			i++;
		}
	}
	return (0);
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
		if (pid == 0) // Child process
		{
			if (prev_fd != -1) // Not the first command
			{
				dup2(prev_fd, STDIN_FILENO); // Get input from previous pipe
				close(prev_fd);
			}
			if (i < data->pipe_num - 1) // Not the last command
			{
				dup2(fd[1], STDOUT_FILENO); // Output to current pipe
				close(fd[1]);
			}
			if (fd[0] != -1)
				close(fd[0]);
			init_data(&child_data, data->env_arr);
			child_data.line = ft_strdup(data->pipes_cmd[i]);
			parse_line(&child_data);
			// Free resources for the child
			free_data(&child_data);
			free(data->pipes_cmd);
			exit(EXIT_SUCCESS);
		}
		else // Parent process
		{
			if (prev_fd != -1)
				close(prev_fd);
			if (fd[1] != -1)
				close(fd[1]);
			prev_fd = fd[0];
		}
		i++;
	}
	// Wait for all child processes
	while (wait(NULL) > 0)
	{
	}
}

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

void	exec_redirection(t_data *data)
{
	int i;

	i = 0;
	while (data->args[i])
	{
		if (ft_strncmp(data->args[i], ">", 2) == 0)
		{
			output_redirection(data, i);
			return ;
		}
		else if (ft_strncmp(data->args[i], ">>", 3) == 0)
		{
			append_redirection(data, i);
			return ;
		}
		else if (ft_strncmp(data->args[i], "<", 2) == 0)
		{
			if (check_dir(data, data->args[i + 1]))
				return ;
			input_redirection(data, i);
			return ;
		}
		else if (ft_strncmp(data->args[i], "<<", 3) == 0)
		{
			exec_here_documents(data, i);
			return ;
		}
		i++;
	}
}
