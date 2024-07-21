/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rilliano <rilliano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 03:22:37 by ppezzull          #+#    #+#             */
/*   Updated: 2024/07/21 19:14:00 by rilliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_here_input(t_data *data, int index)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		data->line = ft_append_str(data->line, "\n");
		data->line = ft_append_str(data->line, line);
		if (ft_strncmp(line, data->args[index + 1],
				ft_strlen(data->args[index + 1]) + 1) == 0)
		{
			data->line = ft_append_str(data->line, "\n");
			free(line);
			break ;
		}
		free(line);
	}
}

int	exec_here_documents(t_data *data, int index)
{
	int		fd[2];
	int		prev_fd;

	if (data->args[index + 1] == NULL)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `newline'",
			2);
		return (1);
	}
	prev_fd = dup(1);
	pipe(fd);
	dup2(0, fd[0]);
	exec_here_input(data, index);
	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
	reformat_redir_args(data, index);
	exec_cmd(data);
	dup2(prev_fd, 1);
	close(prev_fd);
	return (1);
}
