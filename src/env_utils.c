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
                    env = get_env(data->args[i][j], data->env);
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
        if (ft_strncmp(key, &tmp->content[0], len) == 0)
            return (&tmp->content[1]);
        tmp = tmp->next;
    }
    return (NULL);
}

void set_env(char *key, char *value, t_list *env)
{
    t_list *tmp;
    int len;
    char **map;

    tmp = env;
    len = ft_strlen(key);
    while (tmp)
    {
        if (ft_strncmp(key, &tmp->content[0], len) == 0)
        {
            map = tmp->content;
            free(map[1]);
            map[1] = (char *)malloc(ft_strlen(value) + 1);
            ft_strlcpy(map[1], value, ft_strlen(value) + 1);
            break;
        }
        tmp = tmp->next;
    }
    if (!tmp)
        add_env(key, value, env);
}

void add_env(char *key, char *value, t_list *env)
{
    char **map;

    map = (char **)malloc(sizeof(char *) * 2);
    map[0] = (char *)malloc(ft_strlen(key) + 1);
    ft_strlcpy(map[0], key, ft_strlen(key) + 1);
    if (value)
    {
        map[1] = ft_calloc(ft_strlen(value) + 1, sizeof(char));
        ft_strlcpy(map[1], key, ft_strlen(value) + 1);
    }
    else
        map[1] = NULL;
    ft_lstadd_back(&env, ft_lstnew(map));
}

void unset_env(char *key, t_list *env)
{
    t_list *tmp;
    int len;

    tmp = env;
    len = ft_strlen(key);
    if (tmp && ft_strncmp(key, &tmp->content[0], len) == 0)
    {
        env = tmp->next;
        ft_lstdelone(tmp, free_env_content);
        return;
    }
    while (tmp->next)
    {
        if (ft_strncmp(key, &tmp->next->content[0], len) == 0)
        {
            tmp->next = tmp->next->next;
            ft_lstdelone(tmp->next, free_env_content);
            return;
        }
        tmp = tmp->next;
    }
}

void free_env_content(t_list *env)
{
    free(&env->content[0]);
    free(&env->content[1]);
    free(env->content);
}
