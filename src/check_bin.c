/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rilliano <rilliano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 03:22:37 by ppezzull          #+#    #+#             */
/*   Updated: 2024/07/23 15:17:00 by rilliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_file_status(t_data *data, struct stat *path_stat)
{
	if (stat(data->args[0], path_stat) == 0)
	{
		if (S_ISDIR(path_stat->st_mode))
		{
			ft_error(data, data->args[0], "Is a directory");
			data->status = 126;
			return (data->status);
		}
		if ((path_stat->st_mode & S_IXUSR) == 0)
		{
			ft_error(data, data->args[0], "Permission denied");
			data->status = 126;
			return (data->status);
		}
	}
	else
	{
		ft_error(data, data->args[0], "No such file or directory");
		data->status = 127;
		return (data->status);
	}
	return (0);
}

int	check_bin(t_data *data)
{
	struct stat	path_stat;

	if ((data->args[0][0] == '.' && data->args[0][1] == '/')
		|| data->args[0][0] == '/')
	{
		return (check_file_status(data, &path_stat));
	}
	return (0);
}
