#include "minishell.h"

void    init_data(t_data *data, char **env);
void    free_data(t_data *data);
void    parse_line(t_data *data);
void    wait_and_save_exit_status(t_data *data);

void    init_data(t_data *data, char **env)
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

void    free_data(t_data *data)
{
    if (data->cmd)
        free(data->cmd);
    if (data->args)
        free_array(data->args);
    if (data->env)
    {
        ft_lstiter(data->env, &free_env_node);
        free(data->env);
    }
    if (data->pipe)
        free_array(data->pipe);
    if (data->fd)
        free(data->fd);
    if (data->fd_pipe)
        free(data->fd_pipe);
}

void    parse_line(t_data *data)
{
    //int i;

    data->cmd = ft_strtrim(data->line, " ");
    if (data->cmd && data->cmd[0])
        data->args = split_args(data->cmd);
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
        //data_env_format(data);
        exec_cmd(data);
    }
}

void    wait_and_save_exit_status(t_data *data)
{
    waitpid(data->pid, &data->status, 0);
    if (WIFEXITED(data->status))
        data->status = WEXITSTATUS(data->status);
}