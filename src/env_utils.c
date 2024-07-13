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
