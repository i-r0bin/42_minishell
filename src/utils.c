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

int		get_arr_len(char **arr);
void	free_array(char **array);
void	free_env_node(void *env);
void	free_env_content(void *content);

int	get_arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

char	*ft_append_str(char *s1, char *s2)
{
	char	*tmp;

	tmp = s1;
	s1 = ft_strjoin(s1, s2);
	free(tmp);
	return (s1);
}

void	free_array(char **array)
{
	char	**tmp;

	tmp = array;
	if (tmp)
	{
		while (*tmp)
			free(*tmp++);
		free(array);
	}
}

void	free_env_node(void *env)
{
	free_env_content(env);
	free(env);
}

void	free_env_content(void *content)
{
	free(((char **)content)[0]);
	free(((char **)content)[1]);
	free(((char **)content)[2]);
	free(((char **)content)[3]);
}
