/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rilliano <rilliano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 03:22:37 by ppezzull          #+#    #+#             */
/*   Updated: 2024/07/23 16:30:35 by rilliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_dir(t_data *data, char *dir)
{
	struct stat	path_stat;

	if ((dir[0] == '.' && dir[1] == '/') || dir[0] == '/' || ft_isalpha(dir[0]))
	{
		if (stat(dir, &path_stat) != 0)
		{
			ft_error(data, dir, "No such file or directory");
			data->status = 1;
			return (data->status);
		}
	}
	else if (ft_isdigit(dir[0]))
	{
		ft_error(data, dir, "No such file or directory");
		data->status = 1;
		return (data->status);
	}
	else if (!ft_isalpha(dir[0]) && dir[0] != '$')
	{
		ft_error(data, dir, "No such file or directory");
		data->status = 2;
		return (data->status);
	}
	return (0);
}

int	check_token_error(t_data *data)
{
	int	i;

	i = 0;
	while (data->args[i])
	{
		if (is_token(data, i))
		{
			if (handle_token_error(data, i))
				return (1);
		}
		i++;
	}
	return (0);
}

int	is_token(t_data *data, int i)
{
	if (ft_strncmp(data->args[i], ">", 2) == 0 || ft_strncmp(data->args[i],
			">>", 3) == 0 || ft_strncmp(data->args[i], "<", 2) == 0
		|| ft_strncmp(data->args[i], "<<", 3) == 0 || ft_strncmp(data->args[i],
			"|", 2) == 0)
		return (1);
	return (0);
}

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
		|| data->args[0][0] == '/' || !get_env("PATH", data))
	{
		return (check_file_status(data, &path_stat));
	}
	return (0);
}
