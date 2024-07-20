#include "minishell.h"

int     get_key_len(char *key_pos);
char    *get_key_pos(char *arg);
char    **env_to_array(t_list *env);
int     envcmp(const char *s, const char *env);

int get_key_len(char *key_pos)
{
    int len;

    len = 0;
    if (*(key_pos + 1) == '?')
        return (2);
    while (key_pos[len] != '\0' && key_pos[len] != '/' && key_pos[len] != ' ' && key_pos[len] != '\"' && key_pos[len] != '\'')
        len++;
    return (len);
}

char    *get_key_pos(char *arg)
{
    int     i;

    i = 0;
    while (arg[i])
    {
        if (arg[i] == '$' && arg[i + 1] != ' ' && arg[i + 1] != '\0' && arg[i + 1] != '\"' && arg[i + 1] != '\'')
            return (arg + i);
        i++;
    }
    return (NULL);
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
        array[i] = ft_append_str(array[i], ((char **)tmp->content)[1]);
        i++;
        tmp = tmp->next;
    }
    array[i] = NULL;
    return (array);
}

int	envcmp(const char *s, const char *env)
{
	size_t	i;

	i = 0;
	while (env[i] != '\0')
	{
		if (s[i] != env[i])
			return ((unsigned char)s[i] - (unsigned char)env[i]);
		i++;
	}
	if (s[i] != '\0' && s[i] != ' ' && s[i] != '/' && s[i] != '\"')
		return ((unsigned char)s[i] - (unsigned char)env[i]);
	return (0);
}