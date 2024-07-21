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

char	*get_env(char *key, t_data *data)
{
	t_list	*tmp;

	tmp = data->env;
	if (*key == '$')
		key++;
	if (*key == '?')
		return (ft_itoa(data->status));
	while (tmp)
	{
		if (envcmp(key, ((char **)tmp->content)[0]) == 0)
			return (((char **)tmp->content)[1]);
		tmp = tmp->next;
	}
	return (NULL);
}

void	set_env(char *arg, t_data *data, char *is_global)
{
	t_list	*env;
	char	*key;
	char	*value;

	key = ft_strtrim(arg, " ");
	value = ft_strchr(key, '=');
	if (value)
	{
		*value = '\0';
		value++;
		if (*value == '\0')
			value = "";
	}
	env = update_env(key, value, data);
	if (!env && value)
		add_env(key, value, data, is_global);
	free(key);
}

t_list	*update_env(char *key, char *value, t_data *data)
{
	t_list	*tmp;
	char	**map;

	if (!value)
		return (NULL);
	tmp = data->env;
	while (tmp)
	{
		if (envcmp(key, ((char **)tmp->content)[0]) == 0)
		{
			map = tmp->content;
			free(map[1]);
			if (value)
				map[1] = ft_strdup(value);
			else
				map[1] = NULL;
			break ;
		}
		tmp = tmp->next;
	}
	return (tmp);
}

void	add_env(char *key, char *value, t_data *data, char *is_global)
{
	char	**map;

	map = ft_calloc(4, sizeof(char *));
	map[0] = ft_strdup(key);
	map[1] = ft_strdup(value);
	map[2] = ft_strdup(is_global);
	ft_lstadd_back(&(data->env), ft_lstnew(map));
}

void	unset_env(char *key, t_data *data)
{
	t_list	*tmp;
	t_list	*prev;
	t_list	*next;

	tmp = data->env;
	prev = tmp;
	while (tmp)
	{
		if (envcmp(key, ((char **)tmp->content)[0]) == 0)
		{
			next = tmp->next;
			ft_lstdelone(tmp, &free_env_content);
			prev->next = next;
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}
