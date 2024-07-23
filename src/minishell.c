/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rilliano <rilliano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 03:22:37 by ppezzull          #+#    #+#             */
/*   Updated: 2024/07/23 14:46:11 by rilliano         ###   ########.fr       */
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
		free(data.line);
	}
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
