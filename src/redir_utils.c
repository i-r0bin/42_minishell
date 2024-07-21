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

void	input_redirection(t_data *data, int index);
void	output_redirection(t_data *data, int index);
void	append_redirection(t_data *data, int index);
// void	remove_redir_args(t_data *data, int index);

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

void	input_redirection(t_data *data, int index)
{
	int	fd;
	int	prev_fd;

	prev_fd = dup(0);
	fd = open(data->args[index + 1], O_RDONLY);
	dup2(fd, 0);
	close(fd);
	free(data->args[index]);
	data->args[index] = ft_calloc(1, 1);
	free(data->args[index + 1]);
	data->args[index + 1] = ft_calloc(1, 1);
	remove_null_args(data);
	exec_cmd(data);
	dup2(prev_fd, 0);
	close(prev_fd);
}

void	output_redirection(t_data *data, int index)
{
	int	fd;
	int	prev_fd;

	if (check_file_permissions(data->args[index + 1],
			O_WRONLY | O_CREAT | O_TRUNC) < 0)
	{
		data->status = 1;
		return ;
	}
	prev_fd = dup(1);
	fd = open(data->args[index + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(fd, 1);
	close(fd);
	free(data->args[index]);
	data->args[index] = ft_calloc(1, 1);
	free(data->args[index + 1]);
	data->args[index + 1] = ft_calloc(1, 1);
	remove_null_args(data);
	exec_cmd(data);
	dup2(prev_fd, 1);
	close(prev_fd);
}

void	append_redirection(t_data *data, int index)
{
	int	fd;
	int	prev_fd;

	if (check_file_permissions(data->args[index + 1],
			O_WRONLY | O_CREAT | O_APPEND) < 0)
	{
		data->status = 1;
		return ;
	}
	prev_fd = dup(1);
	fd = open(data->args[index + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup2(fd, 1);
	close(fd);
	free(data->args[index]);
	data->args[index] = ft_calloc(1, 1);
	free(data->args[index + 1]);
	data->args[index + 1] = ft_calloc(1, 1);
	remove_null_args(data);
	exec_cmd(data);
	dup2(prev_fd, 1);
	close(prev_fd);
}

// void	remove_redir_args(t_data *data, int index)
// {
// 	while (data->args[index + 2])
// 	{
// 		data->args[index] = data->args[2 + index];
// 		index++;
// 	}
// 	data->args[index++] = NULL;
// 	data->args[index] = NULL;
// }
