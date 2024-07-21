/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rilliano <rilliano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 03:22:37 by ppezzull          #+#    #+#             */
/*   Updated: 2024/07/21 19:13:48 by rilliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_file_permissions(char *file, int flags)
{
	int	fd;

	fd = open(file, flags, 0644);
	if (fd < 0)
	{
		perror("Permission denied");
		return (-1);
	}
	close(fd);
	return (0);
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

void	reformat_redir_args(t_data *data, int index)
{
	free(data->args[index]);
	data->args[index] = ft_calloc(1, 1);
	free(data->args[index + 1]);
	data->args[index + 1] = ft_calloc(1, 1);
	remove_null_args(data);
}
