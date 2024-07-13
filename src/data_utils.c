#include "minishell.h"

void init_data(t_data *data, char **env)
{
    data->env = NULL;
    while(env && *env)
    {
        set_env(*env, data, "0");
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
        ft_lstiter(data->env, &free_env_node);
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

void free_env_node(void *env)
{
    free_env_content(env);
    free(env);
}

void parse_line(t_data *data)
{
    //int i;

    data->cmd = ft_strtrim(data->line, " ");
    if (data->cmd && data->cmd[0])
        data->args = split_cmd(data->cmd);
    if (data->args)
    {
        // ancora da capire cosa gestire prima e dopo (pipe, redir, comando)
        /*i = 0;
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
        }*/
        data_env_format(data);
        exec_cmd(data);
    }
}

void    exec_builtin(t_data *data)
{
    if (ft_strncmp(data->args[0], "exit", 4) == 0)
        data->exit = 1;
    else if (ft_strncmp(data->args[0], "cd", 2) == 0)
        ft_cd(data);
    else if (ft_strncmp(data->args[0], "pwd", 3) == 0)
        ft_pwd(data);
    else if (ft_strncmp(data->args[0], "echo", 4) == 0)
        ft_echo(data);
    else if (ft_strncmp(data->args[0], "export", 6) == 0)
        ft_export(data);
    else if (ft_strncmp(data->args[0], "unset", 5) == 0)
        ft_unset(data);
    else if (ft_strncmp(data->args[0], "env", 3) == 0)
        ft_env(data);
    else
        exec_bin(data);
}