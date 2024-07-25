/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rilliano <rilliano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 03:22:37 by ppezzull          #+#    #+#             */
/*   Updated: 2024/07/23 16:33:02 by rilliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(t_data *data)
{
	int	i;
	int	redir;
	int	pipe;

	i = 0;
	redir = 0;
	pipe = 0;
	if (!data->args || !data->args[0])
		return ;
	while (data->args[i])
	{
		if (is_token(data, i) && ft_strncmp(data->args[i], "|", 2) != 0)
			redir = 1;
		else if (ft_strncmp(data->args[i], "|", 2) == 0)
			pipe = 1;
		i++;
	}
	if (pipe)
		exec_pipe(data);
	else if (redir)
		exec_redirection(data);
	else
		exec_builtin(data);
}

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
	char	**envp;
	int		err;

	if (check_bin(data))
		return ;
	err = 0;
	paths = ft_split(get_env("PATH", data), ':');
	envp = env_to_array(data->env);
	if ((data->args[0][0] == '.' && data->args[0][1] == '/')
		|| data->args[0][0] == '/')
		err = exec_bin_with_path(data, envp);
	else if (execve(data->args[0], data->args, envp) == -1)
		err = exec_bin_paths(data, paths, envp);
	free_array(envp);
	if (!err)
	{
		ft_error(data, data->args[0], "command not found");
		data->status = 127;
	}
	free_array(paths);
}

int	exec_bin_with_path(t_data *data, char **envp)
{
	data->pid = fork();
	if (data->pid == 0)
	{
		execve(data->args[0], data->args, envp);
		WIFEXITED(data->status);
		exit(data->status);
	}
	wait_and_save_exit_status(data);
	if (data->status == 0)
		return (1);
	return (0);
}

int	exec_bin_paths(t_data *data, char **paths, char **envp)
{
	char		*cmd;
	int			i;
	struct stat	path_stat;

	i = 0;
	while (paths[i])
	{
		cmd = ft_strjoin(paths[i], "/");
		cmd = ft_append_str(cmd, data->args[0]);
		data->pid = fork();
		if (data->pid == 0)
		{
			execve(cmd, data->args, envp);
			exit(EXIT_FAILURE);
		}
		wait_and_save_exit_status(data);
		if (stat(cmd, &path_stat) == 0)
		{
			free(cmd);
			return (1);
		}
		free(cmd);
		i++;
	}
	return (0);
}
