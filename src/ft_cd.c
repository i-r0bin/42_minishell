/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppezzull <ppezzull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:52:54 by ppezzull          #+#    #+#             */
/*   Updated: 2024/07/23 17:52:57 by ppezzull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_data *data)
{
	char	*path;

	if (data->args[1] && data->args[2])
	{
		data->status = 1;
		ft_error(data, data->args[0], "too many arguments");
		return ;
	}
	path = determine_cd_path(data);
	if (chdir(path) == -1)
	{
		handle_cd_error(data, path);
		return ;
	}
	update_pwd(data);
}

char	*determine_cd_path(t_data *data)
{
	char	*path;

	if (data->args[1] && ft_strncmp(data->args[1], "-", 2) == 0
		&& get_env("$OLDPWD", data))
		path = get_env("$OLDPWD", data);
	else if (data->args[1] && ft_strncmp(data->args[1], "~", 2) != 0
		&& ft_strncmp(data->args[1], "-", 2) != 0)
		path = data->args[1];
	else if (!data->args[1] || (ft_strncmp(data->args[1], "~", 2) == 0
			|| (ft_strncmp(data->args[1], "-", 2) == 0 && !get_env("$OLDPWD",
					data))))
		path = get_env("$HOME", data);
	return (path);
}

void	handle_cd_error(t_data *data, char *path)
{
	char	*tmp;

	data->status = 1;
	tmp = ft_strjoin("cd: ", path);
	ft_error(data, tmp, "No such file or directory");
	free(tmp);
}
