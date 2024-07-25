/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rilliano <rilliano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 03:22:37 by ppezzull          #+#    #+#             */
/*   Updated: 2024/07/21 19:57:25 by rilliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_redirection(t_data *data)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (data->args[i])
	{
		if (ft_strncmp(data->args[i], ">", 2) == 0)
			res = output_redirection(data, i);
		else if (ft_strncmp(data->args[i], ">>", 3) == 0)
			res = append_redirection(data, i);
		else if (ft_strncmp(data->args[i], "<", 2) == 0)
		{
			if (check_dir(data, data->args[i + 1]))
				return ;
			res = input_redirection(data, i);
			return ;
		}
		else if (ft_strncmp(data->args[i], "<<", 3) == 0)
			res = exec_here_documents(data, i);
		if (res != 0)
			return ;
		i++;
	}
}

int	input_redirection(t_data *data, int index)
{
	int	fd;
	int	prev_fd;

	prev_fd = dup(0);
	fd = open(data->args[index + 1], O_RDONLY);
	dup2(fd, 0);
	close(fd);
	reformat_redir_args(data, index);
	exec_cmd(data);
	dup2(prev_fd, 0);
	close(prev_fd);
	return (1);
}

int	output_redirection(t_data *data, int index)
{
	int	fd;
	int	prev_fd;

	if (check_file_permissions(data->args[index + 1],
			O_WRONLY | O_CREAT | O_TRUNC) < 0)
	{
		data->status = 1;
		return (1);
	}
	prev_fd = dup(1);
	fd = open(data->args[index + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(fd, 1);
	close(fd);
	reformat_redir_args(data, index);
	exec_cmd(data);
	dup2(prev_fd, 1);
	close(prev_fd);
	return (1);
}

int	append_redirection(t_data *data, int index)
{
	int	fd;
	int	prev_fd;

	if (check_file_permissions(data->args[index + 1],
			O_WRONLY | O_CREAT | O_APPEND) < 0)
	{
		data->status = 1;
		return (1);
	}
	prev_fd = dup(1);
	fd = open(data->args[index + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup2(fd, 1);
	close(fd);
	reformat_redir_args(data, index);
	exec_cmd(data);
	dup2(prev_fd, 1);
	close(prev_fd);
	return (1);
}

int	exec_here_documents(t_data *data, int index)
{
	int	fd[2];
	int	prev_fd;

	if (data->args[index + 1] == NULL)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `newline'",
			2);
		return (1);
	}
	prev_fd = dup(1);
	pipe(fd);
	dup2(0, fd[0]);
	exec_here_input(data, index);
	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
	reformat_redir_args(data, index);
	exec_cmd(data);
	dup2(prev_fd, 1);
	close(prev_fd);
	return (1);
}
