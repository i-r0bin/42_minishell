#include "minishell.h"

char	**split_args(char const *line);
int     get_args_num(char const *line);
int     get_arg_size(char const *s);
int     get_null_args_num(t_data *data);
void    remove_null_args(t_data *data);

char	**split_args(char const *line)
{
    char	**args;
    int		n;
    int		j;
    int		size;
    char    *tmp;

    if (!line)
        return (0);
    n = get_args_num(line);
    args = ft_calloc(n + 1, sizeof(char *));
    tmp = (char *)line;
    j = 0;
    while (j < n)
    {
        tmp = ft_strtrim(tmp, " ");
        size = get_arg_size(tmp);
        args[j] = ft_calloc(size + 1, sizeof(char));
        ft_strlcpy(args[j], tmp, size + 1);
        tmp = tmp + size;
        j++;
    }
    args[j] = 0;
    return (args);
}

int	get_args_num(char const *line)
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
        if (line[i] == '\"' && !s_quote && (d_quote || ft_strchr(line + i + 1, '\"')))
            d_quote = d_quote ? 0 : 1;
        else if (line[i] == '\'' && !d_quote && (s_quote || (ft_strchr(line + i + 1, '\''))))
            s_quote = s_quote ? 0 : 1;
        if((!d_quote && !s_quote && line[i] != ' ') && line[i + 1] == ' ')
			n++;
		i++;
	}
	return (n);
}

int	get_arg_size(char const *s)
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
        if (s[i] == '\"' && !s_quote && (d_quote || ft_strchr(s + i + 1, '\"')))
            d_quote = d_quote ? 0 : 1;
        else if (s[i] == '\'' && !d_quote && (s_quote || ft_strchr(s + i + 1, '\'')))
            s_quote = s_quote ? 0 : 1;
        if ((!d_quote && !s_quote && s[i] != ' ') || d_quote || s_quote)
            len++;
        i++;
    }
	return (len);
}

int    get_null_args_num(t_data *data)
{
    int i;
    int null_args;

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

void    remove_null_args(t_data *data)
{
    int     i;
    int     j;
    int     null_args;
    char    **new_arr;

    null_args = get_null_args_num(data);
    if (null_args)
    {
        new_arr = ft_calloc(get_arr_len(data->args) - null_args + 1, sizeof(char *));
        i = 0;
        j = 0;
        while (data->args[i])
        {
            if (data->args[i][0])
                new_arr[j++] = ft_strdup(data->args[i]);
            i++;
        }
        free_array(data->args);
        data->args = new_arr;
    }
}