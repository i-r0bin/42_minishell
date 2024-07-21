/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppezzull <ppezzull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 03:22:37 by ppezzull          #+#    #+#             */
/*   Updated: 2024/07/21 03:22:40 by ppezzull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_data *data);
int		newline_flag(char *arg);

void	ft_echo(t_data *data)
{
	int	i;
	int	n;

	n = 0;
	i = 1;
	while (data->args[i] && data->args[i][0] == '-')
	{
		if (newline_flag(data->args[i]))
		{
			n = 1;
			i++;
		}
		else
			break ;
	}
	while (data->args[i])
	{
		ft_putstr_fd(data->args[i], 1);
		if (data->args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!n)
		ft_putstr_fd("\n", 1);
}

int	newline_flag(char *arg)
{
	int i;

	i = 1;
	while (arg[i] == 'n')
		i++;
	if (i > 1 && !arg[i])
		return (1);
	return (0);
}
