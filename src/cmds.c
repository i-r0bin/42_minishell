/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rilliano <rilliano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 03:22:37 by ppezzull          #+#    #+#             */
/*   Updated: 2024/07/23 16:32:46 by rilliano         ###   ########.fr       */
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

void	ft_env(t_data *data)
{
	t_list	*tmp;

	if (data->args[1])
	{
		data->status = 1;
		ft_error(data, data->args[0], "too many arguments");
		return ;
	}
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

int	validate_exit_args(t_data *data)
{
	int	status;

	status = 0;
	if (data->args[1])
	{
		if (data->args[2])
		{
			ft_error(data, NULL, "too many arguments");
			status = 1;
		}
		else if (!ft_isnumber(data->args[1]))
		{
			ft_error(data, data->args[1], "numeric argument required");
			status = 2;
		}
		else
		{
			status = ft_atoi(data->args[1]);
		}
	}
	return (status);
}

void	ft_exit(t_data *data)
{
	int	status;

	status = validate_exit_args(data);
	if (status != 1)
	{
		free_data(data);
		ft_putendl_fd("exit", 1);
		exit(status);
	}
}
