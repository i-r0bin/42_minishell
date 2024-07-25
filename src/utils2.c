/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rilliano <rilliano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 03:22:37 by ppezzull          #+#    #+#             */
/*   Updated: 2024/07/23 18:34:51 by rilliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quote(const char *line, int index, int open, char quote)
{
	if (line[index] == quote && !open && (line[index + 1] && ft_strchr(line
				+ index + 1, quote)))
		return (1);
	return (0);
}

void	handle_pipe_error(const char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
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
