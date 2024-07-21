/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rilliano <rilliano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 03:22:37 by ppezzull          #+#    #+#             */
/*   Updated: 2024/07/21 19:58:24 by rilliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	ft_putendl_fd(cwd, 1);
	free(cwd);
}

void	ft_cd(t_data *data)
{
	char	*path;

	if (data->args[2])
		ft_error(data, NULL, "too many arguments");
	else
	{
		if (data->args[1])
			path = data->args[1];
		else
			path = get_env("$HOME", data);
		if (chdir(path) == -1)
		{
			ft_error(data, path, "No such file or directory");
			return ;
		}
	}
	update_pwd(data);
}

void	ft_env(t_data *data)
{
	t_list	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (((char *)tmp->content)[1] != '\0'
			&& *((char **)tmp->content)[2] == '0')
		{
			ft_putstr_fd(((char **)tmp->content)[0], 1);
			ft_putchar_fd('=', 1);
			ft_putendl_fd(((char **)tmp->content)[1], 1);
		}
		tmp = tmp->next;
	}
}

void	ft_unset(t_data *data)
{
	int		i;
	char	*key;

	i = 1;
	while (data->args[i])
	{
		key = ft_strtrim(data->args[i], " ");
		unset_env(key, data);
		i++;
	}
}

void	ft_exit(t_data *data)
{
	if (data->args[1])
	{
		if (data->args[2])
		{
			ft_error(data, NULL, "too many arguments");
			data->status = 1;
		}
		else if (!ft_isnumber(data->args[1]))
		{
			ft_error(data, data->args[1], "numeric argument required");
			data->status = 2;
		}
		else
		{
			data->status = ft_atoi(data->args[1]);
			exit(data->status);
		}
	}
	data->exit = 1;
}
