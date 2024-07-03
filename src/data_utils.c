#include "minishell.h"

void init_data(t_data *data, char **env)
{
    while(env && *env)
    {
        set_env(data, *env);
        env++;
    }
    if (!data->env)
        data->env = NULL;
    data->line = NULL;
    data->cmd = NULL;
    data->args = NULL;
    data->pipe = NULL;
    data->fd = NULL;
    data->fd_pipe = NULL;
    data->fd_in = 0;
    data->fd_out = 1;
    data->status = 0;
    data->pid = 0;
    data->exit = 0;
}

void free_data(t_data *data)
{
    if (data->cmd)
        free(data->cmd);
    if (data->args)
    {
        while(*data->args)
            free(*data->args++);
        free(data->args);
    }
    if (data->env)
    {
        ft_lstiter(data->env, free_env_node);
        free(data->env);
    }
    if (data->pipe)
    {
        while(*data->pipe)
            free(*data->pipe++);
        free(data->pipe);
    }
    if (data->fd)
        free(data->fd);
    if (data->fd_pipe)
        free(data->fd_pipe);
}

void free_env_node(t_list *env)
{
    free_env_content(env);
    free(env);
}

void parse_line(t_data *data)
{
    int i;

    data->cmd = ft_strtrim(data->line, " ");
    data->args = split_cmd(data->cmd);
    if (ft_strchr(data->cmd, '>') || ft_strchr(data->cmd, '<'))
        exec_redirection(data);
    else
        exec_cmd(data);
    if (data->args)
    {
        i = 0;
        while(data->args[i])
        {
            if (ft_strncmp(data->args[i], "<<", 2) == 0 || ft_strncmp(data->args[i], ">>", 2) == 0 
                || ft_strncmp(data->args[i], ">", 1) == 0 || ft_strncmp(data->args[i], "<", 1) == 0)
            {
                if(data->args[i + 1] == NULL)
                {
                    ft_putendl_fd("minishell: syntax error near unexpected token `newline'", 2);
                    return ;
                }
                else
                    exec_redirection(data);
            }
            i++;
        }
        if (ft_strncmp(data->args[0], "exit", 4) == 0)
            data->exit = 1;
        else if (ft_strncmp(data->args[0], "cd", 2) == 0)
            ft_cd(data);
        else if (ft_strncmp(data->args[0], "pwd", 3) == 0)
            ft_pwd(data);
        else if (ft_strncmp(data->args[0], "echo", 4) == 0)
            ft_echo(data);
        else if (ft_strncmp(data->args[0], "export", 5) == 0)
            ft_export(data);
        else if (ft_strncmp(data->args[0], "unset", 5) == 0)
            ft_unset(data);
        else if (ft_strncmp(data->args[0], "env", 3) == 0)
            ft_env(data);
        else
            exec_cmd(data);
    }
}

