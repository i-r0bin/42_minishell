#include "minishell.h"

char *get_env(char *key, t_data *data)
{
    t_list *tmp;

    tmp = data->env;
    if (*key == '$')
        key++;
    if (*key == '?')
        return (ft_itoa(data->status));
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
    t_list *env;
    char *key;
    char *value;

    key = ft_strtrim(arg, " ");
    value = ft_strchr(key, '=');
    if (value)
    {
        *value = '\0';
        value++;
        if (*value == '\0')
            value = "";
    }
    env = update_env(key, value, data);
    if (!env && value)
        add_env(key, value, data, is_global);
    free(key);
}

t_list  *update_env(char *key, char *value, t_data *data)
{
    t_list *tmp;
    char **map;

    if (!value)
        return (NULL);
    tmp = data->env;
    while (tmp)
    {
        if (ft_strncmp(key, ((char **)tmp->content)[0], ft_strlen(((char **)tmp->content)[0])) == 0)
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
    return (tmp);
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