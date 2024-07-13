#include "minishell.h"

void    data_env_format(t_data *data)
{
    int i;
    char    first;
    char    *key_pos;
    char    *env;

    i = 0;
    while (data->args[i])
    {
        first = data->args[i][0];
        env = NULL;
        key_pos = ft_strchr(data->args[i], '$');
        if (key_pos)
            env = get_env(key_pos, data->env);
        if (key_pos && first == *key_pos && env)
            replace_env(data, i, key_pos);
        else if (first == '\"' && key_pos && env)
            replace_double_quote(data, i, key_pos, env);
        else if (first == '\"' || first == '\'')
            replace_quote(data, i, first);
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
    new_arg[k] = '\0';
    free(data->args[arg_index]);
    data->args[arg_index] = new_arg;
    if (ft_strchr(data->args[arg_index], '$') && get_env(ft_strchr(data->args[arg_index], '$'), data->env))
    {
        env = get_env(ft_strchr(data->args[arg_index], '$'), data->env);
        replace_double_quote(data, arg_index, ft_strchr(data->args[arg_index], '$'), env);
    }
}

int key_len(char *key_pos)
{
    int len;

    len = 0;
    while (key_pos[len] != '\0' && key_pos[len] != '/' && key_pos[len] != ' ')
        len++;
    return (len);
}

void    replace_quote(t_data *data, int arg_index, char quote)
{
    char    *new_arg;
    int     j;
    int     k;

    if (data->args[arg_index][ft_strlen(data->args[arg_index])] == quote)
        new_arg = (char *)malloc(ft_strlen(data->args[arg_index]) - 2 + 1);
    else
        new_arg = (char *)malloc(ft_strlen(data->args[arg_index]) - 1 + 1);
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
    new_arg[k] = '\0';
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
    new_arg = (char *)malloc(len + 1 * sizeof(char));
    return (new_arg);
}

char *get_env(char *key, t_list *env)
{
    t_list *tmp;

    tmp = env;
    if (*key == '$')
        key++;
    while (tmp)
    {
        if (ft_strncmp(key, ((char **)tmp->content)[0], ft_strlen(((char **)tmp->content)[0])) == 0)
            return (((char **)tmp->content)[1]);
        tmp = tmp->next;
    }
    return (NULL);
}

void    set_env(char *arg, t_data *data, char *is_global)
{
    t_list *tmp;
    char *key;
    char *value;
    char **map;

    tmp = data->env;
    key = ft_strtrim(arg, " ");
    value = ft_strchr(key, '=');
    if (value)
    {
        *value = '\0';
        value++;
        if (*value == '\0')
            value = "";
    }
    while (tmp)
    {
        if (ft_strncmp(key, ((char **)tmp->content)[0], ft_strlen(((char **)tmp->content)[0])) == 0 && value)
        {
            map = tmp->content;
            free(map[1]);
            if (value)
                map[1] = ft_strdup(value);
            else
                map[1] = NULL;
            break;
        }
        tmp = tmp->next;
    }
    if (!tmp && value)
        add_env(key, value, data, is_global);
}

void add_env(char *key, char *value, t_data *data, char *is_global)
{
    char **map;

    map = (char **)malloc(sizeof(char *) * 4);
    map[0] = ft_strdup(key);
    map[1] = ft_strdup(value);
    map[2] = ft_strdup(is_global);
    map[3] = NULL;
    ft_lstadd_back(&(data->env), ft_lstnew(map));
}

void unset_env(char *key, t_data *data)
{
    t_list  *tmp;
    t_list  *prev;
    t_list  *next;
    int     len;

    tmp = data->env;
    prev = tmp;
    len = ft_strlen(key);
    while (tmp)
    {
        if (ft_strncmp(key, ((char **)tmp->content)[0], len) == 0)
        {
            next = tmp->next;
            ft_lstdelone(tmp, &free_env_content);
            prev->next = next;
            return;
        }
        prev = tmp;
        tmp = tmp->next;
    }
}

void free_env_content(void *content)
{
    free(((char **)content)[0]);
    free(((char **)content)[1]);
    free(((char **)content)[2]);
    free((char **)content);
}
