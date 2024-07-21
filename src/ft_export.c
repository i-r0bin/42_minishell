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

void	ft_export(t_data *data);
void	print_export(t_data *data);
void	write_exp_var(t_list *var);
t_list	*get_next_sorted_var(t_list *env, char *last);
int		export_error(t_data *data, char *arg);
void	set_env_exp(char *key, t_data *data); // non serve

void	ft_export(t_data *data)
{
	int	i;

	i = 1;
	if (!data->args[1])
		print_export(data);
	while (data->args[i])
	{
		if (!export_error(data, data->args[i]))
			set_env(((char **)data->args)[i], data, "1");
		i++;
	}
}

void	print_export(t_data *data)
{
	t_list	*tmp;
	char	*last;
	int		c;

	tmp = NULL;
	last = NULL;
	c = 0;
	while (c < ft_lstsize(data->env))
	{
		tmp = get_next_sorted_var(data->env, last);
		if (!tmp)
			break ;
		last = ((char **)tmp->content)[0];
		write_exp_var(tmp);
		c++;
	}
}

void	write_exp_var(t_list *var)
{
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(((char **)var->content)[0], 1);
	if (((char **)var->content)[1])
	{
		ft_putstr_fd("=\"", 1);
		if (*((char **)var->content)[1] != '\0')
			ft_putstr_fd(((char **)var->content)[1], 1);
		ft_putendl_fd("\"", 1);
	}
	else
		ft_putchar_fd('\n', 1);
}

t_list	*get_next_sorted_var(t_list *env, char *last)
{
	t_list	*tmp;
	t_list	*min;

	min = NULL;
	tmp = env;
	while (tmp)
	{
		if (!last || ft_strncmp(((char **)tmp->content)[0],
			last, ft_strlen(last) + 1) > 0)
		{
			if (!min || ft_strncmp(((char **)tmp->content)[0],
				((char **)min->content)[0],
				ft_strlen(((char **)min->content)[0]) + 1) < 0)
				min = tmp;
		}
		tmp = tmp->next;
	}
	return (min);
}

int	export_error(t_data *data, char *arg)
{
	int	i;
	int	error;

	error = 0;
	if (arg[0] == '=' || ft_isdigit(arg[0]))
	{
		ft_error(data, arg, "not a valid identifier");
		error = 1;
	}
	else if (ft_strchr(arg, '-'))
	{
		i = 0;
		while (arg[i] != '=' && arg[i] != '\0')
		{
			if (arg[i] == '-')
			{
				ft_error(data, arg, "not a valid identifier");
				error = 1;
				break ;
			}
			i++;
		}
	}
	return (error);
}
