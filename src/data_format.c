/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rilliano <rilliano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 03:22:37 by ppezzull          #+#    #+#             */
/*   Updated: 2024/07/22 19:55:28 by rilliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_line(t_data *data)
{
	int	i;

	i = 0;
	while (data->line[i] == ' ')
		i++;
	if (!data->line[i])
		return ;
	data->cmd = ft_strtrim(data->line, " ");
	data->cmd = token_format(data->cmd);
	if (data->cmd && data->cmd[0])
		data->args = split_args(data->cmd);
	if (check_token_error(data))
		return ;
	data_env_format(data);
	if (data->args && data->args[0])
		exec_cmd(data);
}

char	**split_args(char const *line)
{
	char	**args;
	int		n;
	int		j;
	int		size;
	char	*tmp;

	if (!line)
		return (0);
	n = get_args_num(line);
	args = ft_calloc(n + 1, sizeof(char *));
	tmp = (char *)line;
	j = 0;
	while (j < n)
	{
		while (*tmp == ' ')
			tmp++;
		size = get_arg_size(tmp);
		args[j] = ft_calloc(size + 1, sizeof(char));
		ft_strlcpy(args[j], tmp, size + 1);
		tmp += size;
		j++;
	}
	return (args);
}

int	get_args_num(char const *line)
{
	int	i;
	int	n;
	int	s_quote;
	int	d_quote;

	i = 0;
	n = 1;
	s_quote = 0;
	d_quote = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\"' && !s_quote)
			d_quote = check_quote(line, i, d_quote, '\"');
		else if (line[i] == '\'' && !d_quote)
			s_quote = check_quote(line, i, s_quote, '\'');
		if ((!d_quote && !s_quote && line[i] != ' ') && line[i + 1] == ' ')
			n++;
		i++;
	}
	return (n);
}

int	get_arg_size(char const *s)
{
	int	s_quote;
	int	d_quote;
	int	i;
	int	len;

	s_quote = 0;
	d_quote = 0;
	i = 0;
	len = 0;
	while (s[i] && (s[i] != ' ' || d_quote || s_quote))
	{
		if (s[i] == '\"' && !s_quote)
			d_quote = check_quote(s, i, d_quote, '\"');
		else if (s[i] == '\'' && !d_quote)
			s_quote = check_quote(s, i, s_quote, '\'');
		if ((!d_quote && !s_quote && s[i] != ' ') || d_quote || s_quote)
			len++;
		i++;
	}
	return (len);
}

int	get_null_args_num(t_data *data)
{
	int	i;
	int	null_args;

	i = 0;
	null_args = 0;
	while (data->args[i])
	{
		if (!data->args[i][0])
			null_args++;
		i++;
	}
	return (null_args);
}
