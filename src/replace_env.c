/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rilliano <rilliano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 03:22:37 by ppezzull          #+#    #+#             */
/*   Updated: 2024/07/21 20:11:20 by rilliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_lens(int *env_len, int *key_len, char *key_pos, char *env)
{
	if (env)
		*env_len = ft_strlen(env);
	else
		*env_len = 0;
	if (key_pos && *(key_pos + 1) != ' ')
		*key_len = get_key_len(key_pos);
	else
		*key_len = 0;
}

char	*get_new_arg(t_data *data, int arg_index, char *key_pos, char *env)
{
	char	*new_arg;
	int		j;
	int		k;
	int		env_len;
	int		key_len;

	get_lens(&env_len, &key_len, key_pos, env);
	new_arg = formatted_arg_allocation(data->args[arg_index], env_len, key_len);
	k = 0;
	j = 0;
	while (data->args[arg_index][j])
	{
		if (data->args[arg_index][j] == '$' && key_pos)
		{
			while (env && *env)
				new_arg[k++] = *(env++);
			j += key_len;
			key_pos = NULL;
		}
		else
			new_arg[k++] = data->args[arg_index][j++];
	}
	return (new_arg);
}

void	replace_env(t_data *data, int arg_index, char *key_pos, char *env)
{
	char	*new_arg;

	new_arg = get_new_arg(data, arg_index, key_pos, env);
	free(data->args[arg_index]);
	data->args[arg_index] = new_arg;
	if (ft_strchr(data->args[arg_index], '$')
		&& get_key_pos(data->args[arg_index])
		&& get_env(get_key_pos(data->args[arg_index]), data))
		replace_env(data, arg_index, get_key_pos(data->args[arg_index]),
			get_env(get_key_pos(data->args[arg_index]), data));
}
