/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rilliano <rilliano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 03:22:37 by ppezzull          #+#    #+#             */
/*   Updated: 2024/07/21 19:45:45 by rilliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(t_data *data, char **env)
{
	data->env = NULL;
	while (env && *env)
	{
		set_env(*env, data, "0");
		env++;
	}
	data->line = NULL;
	data->cmd = NULL;
	data->args = NULL;
	data->pipes_cmd = NULL;
    data->pipe_num = 1;
	data->fd_pipe[0] = -1;
	data->fd_pipe[1] = -1;
	data->status = 0;
	data->pid = 0;
	data->exit = 0;
}

void	parse_line(t_data *data)
{
	data->cmd = ft_strtrim(data->line, " ");
	data->cmd = token_format(data->cmd);
	if (data->cmd && data->cmd[0])
		data->args = split_args(data->cmd);
	if (check_token_error(data))
		return ;
	data_env_format(data);
	if (data->args && data->args[0])
		exec_cmd(data);
}

void	exec_cmd(t_data *data)
{
	int	i;
	int	redir;
	int	pipe;

	i = 0;
	redir = 0;
	pipe = 0;
	while (data->args[i])
	{
		if ((data->args[i][0] == '<' || data->args[i][0] == '>')
			&& (!data->args[i][1] || data->args[i][1] == '<'
				|| data->args[i][1] == '>'))
			redir = 1;
		if (data->args[i][0] == '|')
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

void	wait_and_save_exit_status(t_data *data)
{
	int	status;

	waitpid(data->pid, &status, 0);
	if (WIFEXITED(status))
		data->status = WEXITSTATUS(status);
}

void	free_data(t_data *data)
{
	if (data->cmd)
		free(data->cmd);
	if (data->args)
		free(data->args);
	if (data->env)
	{
		ft_lstclear(&data->env, &free_env_node);
		free(data->env);
	}
	if (data->pipes_cmd)
		free(data->pipes_cmd);
}
