#include "minishell.h"

void    init_data(t_data *data, char **env);
void    parse_line(t_data *data);
void    exec_cmd(t_data *data);
void    wait_and_save_exit_status(t_data *data);
void    free_data(t_data *data);

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

void    parse_line(t_data *data)
{
    data->cmd = ft_strtrim(data->line, " ");
    data->cmd = token_format(data->cmd);
    if (data->cmd && data->cmd[0])
        data->args = split_args(data->cmd);
    if (check_token_error(data))
        return ;
    data_env_format(data);
    if (data->args && data->args[0])
        exec_cmd(data);
}

void exec_cmd(t_data *data)
{
    int i;
    int redir;
    int pipe;

    i = 0;
    redir = 0;
    pipe = 0;
    while (data->args[i])
    {
        if (data->args[i][0] == '<' || data->args[i][0] == '>')
            redir = 1;
        if (data->args[i][0] == '|')
            pipe = 1;
        i++;
    }
    if (redir)
        exec_redirection(data);
    else if (pipe)
        exec_pipe(data);
    else
        exec_builtin(data);
}

void    wait_and_save_exit_status(t_data *data)
{
    waitpid(data->pid, &(data->status), 0);
    if (WIFEXITED(data->status))
        data->status = WEXITSTATUS(data->status);
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
