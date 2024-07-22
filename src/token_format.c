/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rilliano <rilliano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 03:22:37 by ppezzull          #+#    #+#             */
/*   Updated: 2024/07/22 19:51:13 by rilliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_token_format(int *s_quote, int *d_quote, int *i, int *len)
{
	*s_quote = 0;
	*d_quote = 0;
	*i = 0;
	*len = 0;
}

char	*token_format(char *line)
{
	int		s_quote;
	int		d_quote;
	int		i;
	int		len;
	char	*new_line;

	if (get_line_len(line) == ft_strlen(line))
		return (line);
	init_token_format(&s_quote, &d_quote, &i, &len);
	new_line = ft_calloc(get_line_len(line) + 1, sizeof(char));
	while (line[i] != '\0')
	{
		if (line[i] == '\"' && !s_quote)
			d_quote = check_quote((char const *)line, i, d_quote, '\"');
		else if (line[i] == '\'' && !d_quote)
			s_quote = check_quote((char const *)line, i, s_quote, '\'');
		if (!d_quote && !s_quote && (line[i] == '<' || line[i] == '>'
				|| line[i] == '|'))
			format_proc(line, new_line, &i, &len);
		else if (line[i])
			new_line[len++] = line[i++];
	}
	free(line);
	return (new_line);
}

void	format_proc(char *line, char *new_line, int *i, int *len)
{
	char	token;

	token = line[*i];
	if (*i > 0 && line[*i - 1] != ' ')
		new_line[(*len)++] = ' ';
	if (token == '|')
		new_line[(*len)++] = line[(*i)++];
	else if (token == '<' || token == '>')
	{
		new_line[(*len)++] = line[(*i)++];
		if (line[*i] && line[*i] == token)
			new_line[(*len)++] = line[(*i)++];
	}
	if (line[*i] && line[*i] != ' ')
		new_line[(*len)++] = ' ';
}

size_t	get_line_len(char *line)
{
	int		i;
	size_t	len;
	int		s_quote;
	int		d_quote;

	i = 0;
	len = 0;
	s_quote = 0;
	d_quote = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\"' && !s_quote)
			d_quote = check_quote(line, i, d_quote, '\"');
		else if (line[i] == '\'' && !d_quote)
			s_quote = check_quote(line, i, s_quote, '\'');
		if (!d_quote && !s_quote && (line[i] == '<' || line[i] == '>'
				|| line[i] == '|'))
			format_len(line, &i, &len);
		i++;
		len++;
	}
	return (len);
}

void	format_len(char *line, int *i, size_t *len)
{
	char	token;
	
	token = line[*i];
	if (*i > 0 && line[*i - 1] != ' ')
		(*len)++;
	if (token == '|')
	{
		(*i)++;
		(*len)++;
	}
	else if (token == '<' || token == '>')
	{
		(*i)++;
		(*len)++;
		if (line[*i] && line[*i] == token)
		{
			(*i)++;
			(*len)++;
		}
	}
	if (line[*i] && line[*i] != ' ')
		(*len)++;
}
