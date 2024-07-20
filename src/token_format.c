#include "minishell.h"

char	*token_format(char *line)
{
	int		s_quote;
	int		d_quote;
	int		i;
	int		len;
	char	*new_line;

	if (get_line_len(line) == ft_strlen(line))
		return (line);
	s_quote = 0;
	d_quote = 0;
	i = 0;
	len = 0;
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
	return (new_line);
}

void	format_proc(char *line, char *new_line, int *i, int *len)
{
	if (*i > 0 && line[*i - 1] != ' ')
		new_line[(*len)++] = ' ';
	if (line[*i] == '|')
	{
		while (line[*i] == '|')
			new_line[(*len)++] = line[(*i)++];
	}
	else
	{
		while (line[*i] == '<' || line[*i] == '>')
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
	if (*i > 0 && line[*i - 1] != ' ')
		(*len)++;
	if (line[*i] == '|')
	{
		while (line[*i] == '|')
		{
			(*i)++;
			(*len)++;
		}
	}
	else
	{
		while (line[*i] == '<' || line[*i] == '>')
		{
			(*i)++;
			(*len)++;
		}
	}
	if (line[*i] && line[*i] != ' ')
		(*len)++;
}

int	check_quote(const char *line, int index, int open, char quote)
{
	if (line[index] == quote && !open && (line[index + 1] && ft_strchr(line
				+ index + 1, quote)))
		return (1);
	return (0);
}