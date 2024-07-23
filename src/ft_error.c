/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rilliano <rilliano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 03:22:37 by ppezzull          #+#    #+#             */
/*   Updated: 2024/07/22 20:27:46 by rilliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(t_data *data, char *arg, char *error)
{
	ft_putstr_fd("minishell: ", 2);
	if (arg)
	{
		if (ft_strncmp(data->args[0], "export", 7) == 0)
			ft_putchar_fd('`', 2);
		ft_putstr_fd(arg, 2);
		if (ft_strncmp(data->args[0], "export", 7) == 0)
			ft_putchar_fd('\'', 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(error, 2);
	if (data->status == 0)
		data->status = 1;
}

int	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

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
	int		i;
	char	*token;
	char	*error;

	i = 0;
	token = NULL;
	while (data->args[i])
	{
		if (is_token(data, i) && ((!data->args[i + 1] || is_token(data, i + 1)) || i == 0))
		{
			if (!data->args[i + 1] && i > 0)
				token = ft_strjoin("", "newline");
			else if (data->args[i + 1] && i > 0 && (ft_strncmp(data->args[i], "|", 2) != 0 || ft_strncmp(data->args[i], "<", 2) == 0))
				token = data->args[i + 1];
			else if (i == 0 && (ft_strncmp(data->args[i], "|", 2) == 0 || ft_strncmp(data->args[i], "<", 2) == 0))
				token = data->args[i];
			if (token)
			{
				error = ft_strjoin("syntax error near unexpected token `", token);
				error = ft_append_str(error, "\'");
				ft_error(data, NULL, error);
				free(token);
				free(error);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	is_token(t_data *data, int i)
{
	if (ft_strncmp(data->args[i], ">", 2) == 0 || ft_strncmp(data->args[i], ">>", 3) == 0
	|| ft_strncmp(data->args[i], "<", 2) == 0 || ft_strncmp(data->args[i], "<<", 3) == 0
	|| ft_strncmp(data->args[i], "|", 2) == 0)
			return (1);
	return (0);
}
