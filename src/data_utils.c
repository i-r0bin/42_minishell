/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rilliano <rilliano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 03:22:37 by ppezzull          #+#    #+#             */
/*   Updated: 2024/07/23 15:47:53 by rilliano         ###   ########.fr       */
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
}

void	reset_data(t_data *data)
{
	if (data->line)
		free(data->line);
	if (data->cmd)
		free(data->cmd);
	if (data->args)
		free_array(data->args);
	data->line = NULL;
	data->cmd = NULL;
	data->args = NULL;
}

void	free_data(t_data *data)
{
	if (data->line)
		free(data->line);
	if (data->cmd)
		free(data->cmd);
	if (data->args)
		free_array(data->args);
	if (data->env)
	{
		ft_lstclear(&data->env, &free_env_node);
		free(data->env);
	}
	if (data->pipes_cmd)
		free_array(data->pipes_cmd);
}

void	remove_null_args(t_data *data)
{
	int		i;
	int		j;
	int		null_args;
	char	**new_arr;

	null_args = get_null_args_num(data);
	if (null_args)
	{
		new_arr = ft_calloc(get_arr_len(data->args) - null_args + 1,
				sizeof(char *));
		i = 0;
		j = 0;
		while (data->args[i])
		{
			if (data->args[i][0])
				new_arr[j++] = ft_strdup(data->args[i]);
			i++;
		}
		free_array(data->args);
		data->args = new_arr;
	}
}

void	free_env_node(void *env)
{
	free_env_content(env);
	free(env);
}
