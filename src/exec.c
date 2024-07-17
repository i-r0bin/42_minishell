#include "minishell.h"

void    exec_cmd(t_data *data);
void    exec_pipe(t_data *data);
void    exec_redirection(t_data *data);
void    exec_bin(t_data *data);
void    exec_builtin(t_data *data);

void exec_cmd(t_data *data)
{
    char **args;
    int i;
    int redir;
    int pipe;

    args = data->args;
    i = 0;
    redir = 0;
    pipe = 0;
    while (args[i])
    {
        if (args[i][0] == '<' || args[i][0] == '>')
            redir = 1;
        if (args[i][0] == '|')
            pipe = 1;
        i++;
    }
    data_env_format(data);
    remove_null_args(data);
    if (redir)
        exec_redirection(data);
    else if (pipe)
        exec_pipe(data);
    else
        exec_builtin(data);
}

void exec_pipe(t_data *data)
{
    int i;
    int fd[2];

    i = 0;
    //data->pipe deve essere splittato dagli args
    data->pipe = ft_split(data->cmd, '|');
    while (data->pipe[i])
    {
        pipe(fd);
        data->pid = fork();
        if (data->pid == 0)
        {
            set_input_output(data, i, fd);
            exec_pipe_cmd(data, data->pipe[i]);
        }
        else
        {
            wait_and_save_exit_status(data);
            set_fd_pipe(data, fd, i);
            i++;
        }
    }
    free(data->pipe);
}

void exec_redirection(t_data *data)
{
    int i;

    i = 0;
    while (data->args[i])
    {
        if (ft_strncmp(data->args[i], ">", 1) == 0)
            output_redirection(data, i);
        else if (ft_strncmp(data->args[i], ">>", 2) == 0)
            append_redirection(data, i);
        else if (ft_strncmp(data->args[i], "<", 1) == 0)
            input_redirection(data, i);
        else if (ft_strncmp(data->args[i], "<<", 2) == 0)
            exec_here_documents(data, i);
        i++;
    }
    // perché bin? non mi ricordo, probabilmente errore o forse ci vuole exec_cmd o al massimo exec_builtin
    exec_bin(data);
}

void exec_bin(t_data *data)
{
    char *path;
    char *cmd;
    char **env;

    cmd = data->args[0];
    path = get_env("PATH", data);
    env = env_to_array(data->env);
    if (path)
    {
        data->pid = fork();
        if (data->pid == 0)
        {
            execve(cmd, data->args, env);
            ft_error(data, cmd, "command not found");
            exit(127);
        }
        else
            wait_and_save_exit_status(data);
    }
    else
    {
        ft_error(data, cmd, "command not found");
        data->status = 127;
    }
    free_array(env);
}

void    exec_builtin(t_data *data)
{
    if (ft_strncmp(data->args[0], "exit", 4) == 0)
        ft_exit(data);
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