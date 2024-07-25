/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_format.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rilliano <rilliano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 03:22:37 by ppezzull          #+#    #+#             */
/*   Updated: 2024/07/22 15:18:39 by rilliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	data_env_format(t_data *data)
{
	int		i;
	char	*quote;
	char	*key_pos;
	char	*env;

	i = 0;
	while (data->args[i])
	{
		env = NULL;
		quote = get_quote(data->args[i]);
		key_pos = get_key_pos(data->args[i]);
		if (key_pos)
			env = get_env(key_pos, data);
		if (!quote || *quote != '\'')
			replace_env(data, i, key_pos, env);
		quote = get_quote(data->args[i]);
		if (quote && *quote && ft_strchr(quote + 1, *quote))
			remove_quotes(data, i, *quote);
		i++;
	}
	remove_null_args(data);
}

int	check_quote(const char *line, int index, int open, char quote)
{
	if (line[index] == quote && !open && (line[index + 1] && ft_strchr(line
				+ index + 1, quote)))
		return (1);
	return (0);
}

char	*get_quote(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\"' && ft_strchr(arg + i + 1, '\"'))
			return (arg + i);
		else if (arg[i] == '\'' && ft_strchr(arg + i + 1, '\''))
			return (arg + i);
		i++;
	}
	return (NULL);
}

void	remove_quotes(t_data *data, int arg_index, char quote)
{
	char	*new_arg;
	int		j;
	int		k;

	new_arg = ft_calloc(ft_strlen(data->args[arg_index]) - 2 + 1, sizeof(char));
	j = 0;
	k = 0;
	while (data->args[arg_index][j])
	{
		if (data->args[arg_index][j] != quote)
		{
			new_arg[k] = data->args[arg_index][j];
			k++;
		}
		j++;
	}
	free(data->args[arg_index]);
	data->args[arg_index] = new_arg;
}

char	*formatted_arg_allocation(char *arg, int env_len, int key_len)
{
	int		len;
	char	*new_arg;

	len = ft_strlen(arg) + env_len - key_len;
	new_arg = ft_calloc(len + 1, sizeof(char));
	return (new_arg);
}
