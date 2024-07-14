#include "minishell.h"

void    data_env_format(t_data *data)
{
    int     i;
    char    *first;
    char    *key_pos;
    char    *env;

    i = 0;
    while (data->args[i])
    {
        first = data->args[i];
        env = NULL;
        key_pos = ft_strchr(data->args[i], '$');
        if (key_pos)
            env = get_env(key_pos, data->env);
        if (key_pos && *first == *key_pos && env)
            replace_env(data, i, key_pos);
        else if (*first == '\"' && ft_strchr(first + 1, '\"') && key_pos && env)
            replace_double_quote(data, i, key_pos, env);
        else if ((*first == '\"' && ft_strchr(first + 1, '\"')) || (*first == '\'' && ft_strchr(first + 1, '\'')))
            replace_quote(data, i, *first);
        i++;
    }
}

void    replace_env(t_data *data, int arg_index, char *key_pos)
{
    char    *env;

    env = get_env(key_pos, data->env);
    if (env)
    {
        free(data->args[arg_index]);
        data->args[arg_index] = ft_strdup(env);
    }
}

void    replace_double_quote(t_data *data, int arg_index, char *key_pos, char *env)
{
    char    *new_arg;
    int     j;
    int     k;

    new_arg = formatted_arg_allocation(data->args[arg_index], ft_strlen(env), key_len(key_pos));
    k = 0;
    j = 0;
    while (data->args[arg_index][j])
    {
        if (data->args[arg_index][j] == '$' && key_pos)
        {
            while (*env)
                new_arg[k++] = *(env++);
            j += key_len(key_pos);
            key_pos = NULL;
        }
        else if (data->args[arg_index][j] != '\"')
            new_arg[k++] = data->args[arg_index][j++];
        else
            j++;
    }
    free(data->args[arg_index]);
    data->args[arg_index] = new_arg;
    if (ft_strchr(data->args[arg_index], '$') && get_env(ft_strchr(data->args[arg_index], '$'), data->env))
        replace_double_quote(data, arg_index, ft_strchr(data->args[arg_index], '$'), get_env(ft_strchr(data->args[arg_index], '$'), data->env));
}

void    replace_quote(t_data *data, int arg_index, char quote)
{
    char    *new_arg;
    int     j;
    int     k;

    new_arg = ft_calloc(ft_strlen(data->args[arg_index]) - 2 + 1, sizeof(char));
    j = 0;
    k = 0;
    while (data->args[arg_index][j])
    {
        if (data->args[arg_index][j] != quote)
        {
            new_arg[k] = data->args[arg_index][j];
            k++;
        }
        j++;
    }
    free(data->args[arg_index]);
    data->args[arg_index] = new_arg;
}

char    *formatted_arg_allocation(char *arg, int env_len, int key_len)
{
    int     len;
    char    *new_arg;

    len = ft_strlen(arg) + env_len - key_len;
    if (arg[0] == '\"')
        len--;
    if (arg[ft_strlen(arg)] == '\"')
        len--;
    new_arg = ft_calloc(len + 1, sizeof(char));
    return (new_arg);
}