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

void	handle_pipe_error(const char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

int	handle_token_error(t_data *data, int i)
{
	char	*token;
	char	*error;

	token = NULL;
	if ((!data->args[i + 1] || is_token(data, i + 1)) || i == 0)
	{
		if (!data->args[i + 1] && (i > 0 || (i == 0
					&& ft_strncmp(data->args[i], "|", 2) != 0)))
			token = ft_strjoin("newline", "\'");
		else if (ft_strncmp(data->args[i], "|", 2) == 0 && ((data->args[i + 1]
					&& ft_strncmp(data->args[i + 1], "|", 2) == 0) || i == 0))
			token = ft_strjoin(ft_strdup(data->args[i]), "\'");
		else if (ft_strncmp(data->args[i], "|", 2) != 0
			&& data->args[i + 1] && is_token(data, i + 1))
			token = ft_strjoin(ft_strdup(data->args[i + 1]), "\'");
		if (token)
		{
			error = ft_strjoin("syntax error near unexpected token `", token);
			ft_error(data, NULL, error);
			free(token);
			free(error);
			return (1);
		}
	}
	return (0);
}
