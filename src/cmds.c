#include "minishell.h"

void ft_echo(t_data *data)
{
    int i;
    int n;

    n = 0;
    i = 1;
    if (data->args[1] && data->args[1][0] == '-')
    {
        while(data->args[1][i] == 'n')
            i++;
        if (i > 1 && !data->args[1][i])
            n++;
    }
    if (!n)
        i = 1;
    else
        i = 2;
    while (data->args[i])
    {
        ft_putstr_fd(data->args[i], 1);
        if (data->args[i + 1])
            ft_putstr_fd(" ", 1);
        i++;
    }
    if (!n)
        ft_putstr_fd("\n", 1);
}

void ft_cd(t_data *data)
{
    if (data->args[1])
    {
        if (data->args[2])
            ft_putendl_fd("minishell: cd: too many arguments", 2);
        else if (chdir(data->args[1]) == -1)
        {
            ft_putstr_fd("minishell: cd: ", 2);
            ft_putstr_fd(data->args[1], 2);
            ft_putstr_fd(": No such file or directory\n", 2);
        }
    }
    else
        chdir(get_env("$HOME", data->env));
}

void ft_pwd(t_data *data)
{
    char *cwd;

    cwd = getcwd(NULL, 0);
    ft_putendl_fd(cwd, 1);
    free(cwd);
}

void ft_export(t_data *data)
{
    int i;
    char *key;
    char *value;

    i = 1;
    if (!data->args[i])
        print_export(data);
    while (data->args[i])
    {
        if (data->args[i][0] == '=')
        {
            ft_putstr_fd("minishell: export: `", 2);
            ft_putstr_fd(data->args[i], 2);
            ft_putendl_fd("': not a valid identifier", 2);
        }
        else
        {
            key = ft_strtrim(data->args[i], " ");
            value = ft_strchr(key, '=');
            if (value)
            {
                *value = '\0';
                value++;
                if (!value)
                    value = "";
                set_env(key, value, data->env);
            }
            else
                set_env_exp(key, data->env);
            i++;
        }
    }
}

void ft_unset(t_data *data)
{
    int i;
    char *key;

    i = 1;
    while (data->args[i])
    {
        key = ft_strtrim(data->args[i], " ");
        unset_env(key, data->env);
        i++;
    }
}

void ft_env(t_data *data)
{
    t_list *tmp;

    tmp = data->env;
    while (tmp)
    {
        if (&tmp->content[1] != '\0')
        {
            ft_putstr_fd(&tmp->content[0], 1);
            ft_putchar_fd('=', 1);
            ft_putendl_fd(&tmp->content[1], 1);
        }
        tmp = tmp->next;
    }
}