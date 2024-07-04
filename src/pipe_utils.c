#include "minishell.h"

void set_input_output(t_data *data, int i, int fd[2])
{
    if (i > 0)
    {
        dup2(data->fd_pipe[0], 0);
        close(data->fd_pipe[0]);
        close(data->fd_pipe[1]);
    }
    if (data->pipe[i + 1])
        dup2(fd[1], 1);
    close(fd[0]);
}

void set_fd_pipe(t_data *data, int fd[2], int i)
{
    if (i > 0)
    {
        close(data->fd_pipe[0]);
        close(data->fd_pipe[1]);
    }
    data->fd_pipe[0] = fd[0];
    data->fd_pipe[1] = fd[1];
}

void exec_pipe_cmd(t_data *data, char *cmd)
{
    data->args = split_cmd(ft_strtrim(cmd, " "));
    if (data->args)
    {
        if (ft_strchr(cmd, '>') || ft_strchr(cmd, '<'))
            exec_redirection(data);
        else
            exec_cmd(data);
    }
}