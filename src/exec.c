#include "minishell.h"

void    exec_builtin(t_data *data);
void    exec_bin(t_data *data);
int    exec_bin_path(t_data *data, char **paths);
void    exec_pipe(t_data *data);
void    exec_redirection(t_data *data);

void    exec_builtin(t_data *data)
{
    if (ft_strncmp(data->args[0], "exit", 5) == 0)
        ft_exit(data);
    else if (ft_strncmp(data->args[0], "cd", 3) == 0)
        ft_cd(data);
    else if (ft_strncmp(data->args[0], "pwd", 4) == 0)
        ft_pwd(data);
    else if (ft_strncmp(data->args[0], "echo", 5) == 0)
        ft_echo(data);
    else if (ft_strncmp(data->args[0], "export", 7) == 0)
        ft_export(data);
    else if (ft_strncmp(data->args[0], "unset", 6) == 0)
        ft_unset(data);
    else if (ft_strncmp(data->args[0], "env", 4) == 0)
        ft_env(data);
    else
        exec_bin(data);
}

void exec_bin(t_data *data)
{
    char    **paths;
    int     err;

    if (!get_env("PATH", data))
    {
        ft_error(data, data->args[0], "command not found");
        return ;
    }
    if (check_bin(data))
        return ;
    err = 0;
    paths = ft_split(get_env("PATH", data), ':');
    if (execve(data->args[0], data->args, env_to_array(data->env)) == -1)
        err = exec_bin_path(data, paths);
    if (!err)
    {
        ft_error(data, data->args[0], "command not found");
        data->status = 127;
    }
    free_array(paths);
}

int    exec_bin_path(t_data *data, char **paths)
{
    char    *cmd;
    int     pid;
    int     i;
    struct  stat path_stat;

    i = 0;
    while (paths[i])
    {
        cmd = ft_strjoin(ft_strjoin(paths[i], "/"), data->args[0]);
        pid = fork();
        if (pid == 0)
        {
            execve(cmd, data->args, env_to_array(data->env));
            exit(EXIT_FAILURE);
        }
        else
        {
            wait_and_save_exit_status(data);
            if (stat(cmd, &path_stat) == 0)
                return (1);
            i++;
        }
    }
    return (0);
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
        if (ft_strncmp(data->args[i], ">", 2) == 0)
        {
            output_redirection(data, i);
            return ;
        }
        else if (ft_strncmp(data->args[i], ">>", 3) == 0)
        {
            append_redirection(data, i);
            return ;
        }
        else if (ft_strncmp(data->args[i], "<", 2) == 0)
        {
            if(check_dir(data, data->args[i + 1]))
                return ;
            input_redirection(data, i);
            return ;
        }
        else if (ft_strncmp(data->args[i], "<<", 3) == 0)
        {
            exec_here_documents(data, i);
            return ;
        }
        i++;
    }
}