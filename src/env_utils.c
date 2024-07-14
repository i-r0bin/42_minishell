#include "minishell.h"

int key_len(char *key_pos)
{
    int len;

    len = 0;
    while (key_pos[len] != '\0' && key_pos[len] != '/' && key_pos[len] != ' ')
        len++;
    return (len);
}

void free_env_node(void *env)
{
    free_env_content(env);
    free(env);
}

void free_env_content(void *content)
{
    free(((char **)content)[0]);
    free(((char **)content)[1]);
    free(((char **)content)[2]);
    free(((char **)content)[3]);
}

char    **env_to_array(t_list *env)
{
    char    **array;
    int     i;
    t_list  *tmp;

    i = 0;
    tmp = env;
    array = (char **)malloc(sizeof(char *) * (ft_lstsize(env) + 1));
    while (tmp)
    {
        array[i] = ft_strjoin(((char **)tmp->content)[0], "=");
        array[i] = ft_strjoin(array[i], ((char **)tmp->content)[1]);
        i++;
        tmp = tmp->next;
    }
    array[i] = NULL;
    return (array);
}