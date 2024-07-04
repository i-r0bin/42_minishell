#include "minishell.h"

void print_export(t_data *data)
{
    t_list *tmp;
    char *last;
    int c;

    tmp = NULL;
    last = NULL;
    c = 0;
    while (c < ft_lstsize(data->env))
    {
        tmp = get_next_sorted_var(data->env, last);
        last = ((char **)tmp->content)[0];
        if (*((char **)tmp->content)[1] != '\0')
            write_exp_var(tmp);
        c++;
    }
    tmp = NULL;
    c = 0;
    while (c < ft_lstsize(data->env))
    {
        tmp = get_next_sorted_var(data->env, last);
        last = ((char **)tmp->content)[0];
        if (*((char **)tmp->content)[1] == '\0')
            write_exp_var(tmp);
        c++;
    }
}

void write_exp_var(t_list *var)
{
    ft_putstr_fd("declare -x ", 1);
    ft_putstr_fd(((char **)var->content)[0], 1);
    if (*((char **)var->content)[1] != '\0')
    {
        ft_putstr_fd("=\"", 1);
        ft_putstr_fd(((char **)var->content)[1], 1);
        ft_putendl_fd("\"", 1);
    }
    else
        ft_putchar_fd('\n', 1);
}

t_list *get_next_sorted_var(t_list *env, char *last)
{
    t_list *tmp;
    t_list *min;

    min = NULL;
    tmp = env;
    while (tmp)
    {
        if (!last || ft_strncmp(((char **)tmp->content)[0], last, ft_strlen(last)) > 0)
        {
            if (!min || ft_strncmp(((char **)tmp->content)[0], ((char **)min->content)[0], 
                ft_strlen(((char **)min->content)[0])) < 0)
                min = tmp;
        }
        tmp = tmp->next;
    }
    return (min);
}

//serve davvero questa funzione?
void set_env_exp(char *key, t_list *env)
{
    t_list *tmp;
    int len;
 
    tmp = env;
    len = ft_strlen(key);
    while (tmp && ft_strncmp(key, ((char **)tmp->content)[0], len) != 0)
        tmp = tmp->next;
    if (!tmp)
        add_env(key, NULL, env, "1");
}