#include "minishell.h"

void exec_cmd(t_data *data)
{
    if (ft_strchr(data->cmd, '>') || ft_strchr(data->cmd, '<'))
        exec_redirection(data);
    else if (ft_strchr(data->cmd, '|'))
        exec_pipe(data);
    exec_builtin(data);
}

void exec_pipe(t_data *data)
{
    int i;
    int fd[2];

    i = 0;
    data->pipe = ft_split(data->cmd, '|');
    while (data->pipe[i])
    {
        pipe(fd);
        data->pid = fork();
        ft_putnbr_fd(data->pid, 1);
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
    exec_bin(data);
}

void exec_bin(t_data *data)
{
    char **env;
    data->pid = fork();
    if (data->pid == 0)
    {
        env = env_to_array(data->env);
        if (execve(data->args[0], data->args, env) == -1)
        {
            ft_putstr_fd("minishell: ", 2);
            ft_putstr_fd(data->args[0], 2);
            ft_putstr_fd(": No such file or directory\n", 2);
            exit(127);
        }
    }
    else
        wait_and_save_exit_status(data);
}

void wait_and_save_exit_status(t_data *data)
{
    waitpid(data->pid, &data->status, 0);
    if (WIFEXITED(data->status))
        data->status = WEXITSTATUS(data->status);
}