#include "minishell.h"

void    ft_pwd();
void    ft_cd(t_data *data);
void    ft_env(t_data *data);
void    ft_unset(t_data *data);
void    ft_exit(t_data *data);

void ft_pwd()
{
    char *cwd;

    cwd = getcwd(NULL, 0);
    ft_putendl_fd(cwd, 1);
    free(cwd);
}

//controllare se chdir gestisce sia relative che absolute path
void ft_cd(t_data *data)
{
    if (data->args[1])
    {
        if (data->args[2])
            ft_error(data, NULL, "too many arguments");
        else if (chdir(data->args[1]) == -1)
            ft_error(data, data->args[1], "No such file or directory");
    }
    else
        chdir(get_env("$HOME", data));
}

void ft_env(t_data *data)
{
    t_list *tmp;

    tmp = data->env;
    while (tmp)
    {
        if (((char *)tmp->content)[1] != '\0' && *((char **)tmp->content)[2] == '0')
        {
            ft_putstr_fd(((char **)tmp->content)[0], 1);
            ft_putchar_fd('=', 1);
            ft_putendl_fd(((char **)tmp->content)[1], 1);
        }
        tmp = tmp->next;
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
        unset_env(key, data);
        i++;
    }
}

void ft_exit(t_data *data)
{
    if (data->args[1])
    {
        if (data->args[2])
            ft_error(data, NULL, "too many arguments");
        else if (!ft_isnumber(data->args[1]))
            ft_error(data, data->args[1], "numeric argument required");
        else
        {
            data->status = ft_atoi(data->args[1]);
            exit(data->status);
        }
    }
    data->exit = 1;
}