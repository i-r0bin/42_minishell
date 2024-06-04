#include "minishell.h"

int	args_num(char const *line)
{
	int	i;
	int	n;
    int open_quote;

	i = 0;
	n = 0;
    open_quote = 0;
	while (line[i] != '\0')
	{
        if (line[i] == '\"' && (i = 0 || line[i] == '\''))
            open_quote = open_quote ? 0 : 1;
		if (!open_quote && line[i] != ' ' && (line[i + 1] == ' ' || line[i + 1] == '\0'))
			n++;
		i++;
	}
	return (n);
}

void    handle_quotes(char const *line, int *i, char quote)
{
    int j;

    j = *i;
    if (line[j] == quote && (j = 0 || line[j - 1] == ' '))
    {
        j++;
        while (line[j] != quote)
            j++;
    }
    if (line[j] == quote)
        *i = j;
}

int	arg_size(char const *s)
{
	int s_quote;
    int d_quote;
    int	len;

    s_quote = 0;
    d_quote = 0;
	len = 0;
	while (s[len])
    {
        if (s[len] == '\"')
            d_quote = d_quote ? 0 : len;
        else if (s[len] == '\'')
            s_quote = s_quote ? 0 : len;
        if (!d_quote && !s_quote && s[len] != ' ')
            len++;
        else if (d_quote && (!s_quote || d_quote < s_quote) && s[len] != '\"')
            len++;
        else if (s_quote && (!d_quote || s_quote < d_quote) && s[len] != '\'')
            len++;
        
    }
	return (len);
}

char	**split_cmd(char const *line)
{
    char	**args;
    int		n;
    int		j;
    int		size;

    if (!line)
        return (0);
    n = args_num(line);
    args = (char **)malloc((n + 1) * sizeof(char *));
    if (!args)
        return (0);
    j = 0;
    while (j < n)
    {
        line = ft_strtrim(line, " ");
        size = arg_size(line);
        args[j] = (char *)malloc((size + 1) * sizeof(char));
        if (!args[j])
            return (0);
        args[j] = ft_strlcpy(args[j], line, size + 1);
        line = line + size;
        j++;
    }
    args[j] = 0;
    return (args);
}