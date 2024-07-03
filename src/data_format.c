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
        if (line[i] == '\"' || line[i] == '\'')
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
    int i;
    int	len;

    s_quote = 0;
    d_quote = 0;
    i = 0;
	len = 0;
	while (s[i] && (s[i] != ' ' || d_quote || s_quote))
    {
        if (s[i] == '\"' && !s_quote)
            d_quote = d_quote ? 0 : 1;
        else if (s[i] == '\'' && !d_quote)
            s_quote = s_quote ? 0 : 1;
        else if ((!d_quote && !s_quote && s[i] != ' ') || d_quote || s_quote)
        {
            if (s[i] == '$' && !s_quote)
            {
                len += ft_strlen(get_env(s[i], data->env));
                while (s[i + 1] != '\0' && s[i + 1] != '/' && s[i + 1] != ' ')
                    i++;
            }
            else
                len++;
        }
        i++;
    }
	return (len);
}

char	**split_cmd(char const *line)
{
    char	**args;
    int		n;
    int		j;
    int		size;
    char    *tmp;

    if (!line)
        return (0);
    n = args_num(line);
    args = (char **)malloc((n + 1) * sizeof(char *));
    if (!args)
        return (0);
    tmp = line;
    j = 0;
    while (j < n)
    {
        tmp = ft_strtrim(tmp, " ");
        size = arg_size(tmp);
        args[j] = (char *)malloc((size + 1) * sizeof(char));
        if (!args[j])
            return (0);
        if (tmp[0] == '\"' || tmp[0] == '\'')
            handle_quotes(tmp, &size, tmp[0]);
        args[j] = ft_strlcpy(args[j], tmp, size + 1);
        tmp = tmp + size;
        j++;
    }
    args[j] = 0;
    return (args);
}