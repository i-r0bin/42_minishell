/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rilliano <rilliano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 03:22:37 by ppezzull          #+#    #+#             */
/*   Updated: 2024/07/23 17:16:20 by rilliano         ###   ########.fr       */
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
	signal(SIGQUIT, signal_handler);
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
		free(data.line);
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
	else if (signum == SIGQUIT)
	{
		signal(SIGQUIT, SIG_IGN);
		if (wait(NULL) >= 0)
		{
			ft_putendl_fd("Quit (core dumped)", 1);
			signal(SIGQUIT, SIG_DFL);
			raise(SIGQUIT);
		}
		signal(SIGQUIT, SIG_IGN);
	}
}
