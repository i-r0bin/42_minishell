#include "minishell.h"

void    data_env_format(t_data *data);
char    *get_quote(char *arg);
void    replace_env(t_data *data, int arg_index, char *key_pos, char *env);
void    remove_quotes(t_data *data, int arg_index, char quote);
char    *formatted_arg_allocation(char *arg, int env_len, int key_len);

void    data_env_format(t_data *data)
{
    int     i;
    char    *quote;
    char    *key_pos;
    char    *env;

    i = 0;
    while (data->args[i])
    {
        env = NULL;
        quote = get_quote(data->args[i]);
        key_pos = get_key_pos(data->args[i]);
        if (key_pos)
            env = get_env(key_pos, data);
        if (!quote || *quote != '\'')
            replace_env(data, i, key_pos, env);
        quote = get_quote(data->args[i]);
        if (quote && *quote && ft_strchr(quote + 1, *quote))
            remove_quotes(data, i, *quote);
        i++;
    }
    remove_null_args(data);
}

char    *get_quote(char *arg)
{
    int     i;

    i = 0;
    while (arg[i])
    {
        if (arg[i] == '\"' && ft_strchr(arg + i + 1, '\"'))
            return (arg + i);
        else if (arg[i] == '\'' && ft_strchr(arg + i + 1, '\''))
            return (arg + i);
        i++;
    }
    return (NULL);
}

void    replace_env(t_data *data, int arg_index, char *key_pos, char *env)
{
    char    *new_arg;
    int     j;
    int     k;
    int     env_len;
    int     key_len;

    env_len = env ? ft_strlen(env) : 0;
    key_len = key_pos && *(key_pos + 1) != ' ' ? get_key_len(key_pos) : 0;
    new_arg = formatted_arg_allocation(data->args[arg_index], env_len, key_len);
    k = 0;
    j = 0;
    while (data->args[arg_index][j])
    {
        if (data->args[arg_index][j] == '$' && key_pos)
        {
            while (env && *env)
                new_arg[k++] = *(env++);
            j += key_len;
            key_pos = NULL;
        }
        else
            new_arg[k++] = data->args[arg_index][j++];
    }
    free(data->args[arg_index]);
    data->args[arg_index] = new_arg;
    if (ft_strchr(data->args[arg_index], '$') && get_key_pos(data->args[arg_index]) && get_env(get_key_pos(data->args[arg_index]), data))
        replace_env(data, arg_index, get_key_pos(data->args[arg_index]), get_env(get_key_pos(data->args[arg_index]), data));
}

void    remove_quotes(t_data *data, int arg_index, char quote)
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
    new_arg = ft_calloc(len + 1, sizeof(char));
    return (new_arg);
}