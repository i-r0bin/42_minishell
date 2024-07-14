#include "minishell.h"

int	args_num(char const *line)
{
	int	i;
	int	n;
    int s_quote;
    int d_quote;

	i = 0;
	n = 1;
    s_quote = 0;
    d_quote = 0;
	while (line[i] != '\0')
	{
        if (line[i] == '\"' && !s_quote && ft_strchr(line + i + 1, '\"'))
            d_quote = d_quote ? 0 : 1;
        else if (line[i] == '\'' && !d_quote && ft_strchr(line + i + 1, '\''))
            s_quote = s_quote ? 0 : 1;
        if((!d_quote && !s_quote && line[i] != ' ') && (line[i + 1] == ' ' || line[i + 1] == '>' || line[i + 1] == '<' || (line[i + 1] == '|' && line[i + 2] != '|')))
			n++;
        else if(!d_quote && !s_quote && (line[i] == '>' || line[i] == '<'))
        {
            while (line[i] == '>' || line[i] == '<')
                i++;
            n++;
        }
        else if (!d_quote && !s_quote && line[i] == '|' && line[i + 1] != '|')
        {
            i++;
            n++;
        }
		i++;
	}
	return (n);
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
        if (s[i] == '\"' && !s_quote && ft_strchr(s + i + 1, '\"'))
            d_quote = d_quote ? 0 : 1;
        else if (s[i] == '\'' && !d_quote && ft_strchr(s + i + 1, '\''))
            s_quote = s_quote ? 0 : 1;
        if ((!d_quote && !s_quote && s[i] != ' ') || d_quote || s_quote)
            len++;
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
    args = ft_calloc(n + 1, sizeof(char *));
    tmp = (char *)line;
    j = 0;
    while (j < n)
    {
        tmp = ft_strtrim(tmp, " ");
        size = arg_size(tmp);
        args[j] = ft_calloc(size + 1, sizeof(char));
        ft_strlcpy(args[j], tmp, size + 1);
        tmp = tmp + size;
        j++;
    }
    args[j] = 0;
    return (args);
}