/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rilliano <rilliano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 03:22:37 by ppezzull          #+#    #+#             */
/*   Updated: 2024/07/23 20:09:43 by rilliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)ac;
	(void)av;
	init_data(&data, env);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		data.line = readline("minishell$ ");
		if (!data.line)
			break ;
		if (data.line[0] != '\0')
		{
			parse_line(&data);
			if (data.cmd && data.cmd[0])
				add_history(data.line);
		}
		reset_data(&data);
	}
	free_data(&data);
	ft_putendl_fd("exit", 1);
	exit(0);
	return (0);
}

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		if (wait(NULL) < 0)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
}

void	reset_data(t_data *data)
{
	if (data->line)
		free(data->line);
	if (data->cmd)
		free(data->cmd);
	if (data->args)
		free_array(data->args);
	data->line = NULL;
	data->cmd = NULL;
	data->args = NULL;
}
