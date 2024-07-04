#include "minishell.h"

void check_env(t_data *data)
{
    int i;
    int j;
    int avoid;
    int full_arg;
    char *env;
    char *tmp;

    i = 0;
    avoid = 0;
    full_arg = 0;
    while (data->args[i])
    {
        j = 0;
        while(data->args[i][j])
        {
            if (data->args[i][j] == '\'' && !full_arg)
                avoid = avoid ? 0 : 1;
            else if (data->args[i][j] == '\"')
                full_arg = full_arg ? 0 : 1;
            else if (!avoid && data->args[i][j] == '$')
            {
                if (data->args[i][j + 1] == '?')
                    env = ft_itoa(data->status);
                else
                    env = get_env(&(data->args)[i][j], data->env);
                if (!full_arg)
                    tmp = (char *)malloc(j + ft_strlen(env) + 1);
                else
                {
                    while (data->args[i][j] != '\0' && data->args[i][j] != '/')
                    {
                        if (data->args[i][j] == '$')
                            j++;
                    }
                        j++;
                    if (data->args[i][j] == '/')
                        j++;
                    tmp = (char *)malloc(j + ft_strlen(env) + 1);
                }
                    tmp = (char *)malloc(j + ft_strlen(env) + 1);
                data->args[i][j] = '\0';
                tmp = ft_strjoin(data->args[i], env);
                free(data->args[i]);
                data->args[i] = tmp;
            }
            j++;
        }
        i++;
    }
}

char *get_env(char *key, t_list *env)
{
    t_list *tmp;
    int len;

    tmp = env;
    len = 0;
    if (*key == '$')
        key++;;
    while (key[len] != '\0' && key[len] != '/' && key[len] != ' ')
        len++;
    while (tmp)
    {
        if (ft_strncmp(key, ((char **)tmp->content)[0], len) == 0)
            return (((char **)tmp->content)[1]);
        tmp = tmp->next;
    }
    return (NULL);
}

void    set_env(char *arg, t_list *env, char *is_global)
{
    t_list *tmp;
    char *key;
    char *value;
    char **map;

    tmp = env;
    key = ft_strtrim(arg, " ");
    value = ft_strchr(key, '=');
    if (value)
    {
        *value = '\0';
        value++;
        if (!value)
            value = "";
    }
    while (tmp)
    {
        if (ft_strncmp(key, ((char **)tmp->content)[0], ft_strlen(key)) == 0)
        {
            map = tmp->content;
            free(map[1]);
            map[1] = ft_strdup(value);
            break;
        }
        tmp = tmp->next;
    }
    if (!tmp)
        add_env(key, value, env, is_global);
}

void add_env(char *key, char *value, t_list *env, char *is_global)
{
    char **map;

    map = (char **)malloc(sizeof(char *) * 3);
    map[0] = ft_strdup(key);
    map[1] = ft_strdup(value);
    map[2] = ft_strdup(is_global);
    ft_lstadd_back(&env, ft_lstnew(map));
}

void unset_env(char *key, t_list *env)
{
    t_list *tmp;
    int len;

    tmp = env;
    len = ft_strlen(key);
    if (tmp && ft_strncmp(key, ((char **)tmp->content)[0], len) == 0)
    {
        env = tmp->next;
        ft_lstdelone(tmp, &free_env_content);
        return;
    }
    while (tmp->next)
    {
        if (ft_strncmp(key, ((char **)tmp->content)[0], len) == 0)
        {
            tmp->next = tmp->next->next;
            ft_lstdelone(tmp->next, &free_env_content);
            return;
        }
        tmp = tmp->next;
    }
}

void free_env_content(void *env)
{
    free(((char **)((t_list *)env)->content)[0]);
    free(((char **)((t_list *)env)->content)[1]);
    free(((char **)((t_list *)env)->content)[2]);
    free(((t_list *)env)->content);
}
