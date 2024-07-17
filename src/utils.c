#include "minishell.h"

int     get_arr_len(char **arr);
void    free_array(char **array);
void    free_env_node(void *env);
void    free_env_content(void *content);

int get_arr_len(char **arr)
{
    int i;

    i = 0;
    while (arr[i])
        i++;
    return (i);
}

void    free_array(char **array)
{
    char    **tmp;

    tmp = array;
    if (tmp)
    {
        while(*tmp)
            free(*tmp++);
        free(array);
    }
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