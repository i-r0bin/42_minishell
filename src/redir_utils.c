#include "minishell.h"

void    input_redirection(t_data *data, int index);
void    output_redirection(t_data *data, int index);
void    append_redirection(t_data *data, int index);
void    exec_here_documents(t_data *data, int index);
void    remove_redir_args(t_data *data, int index);

void    input_redirection(t_data *data, int index)
{
    int fd;
    int prev_fd;

    prev_fd = dup(0);
    fd = open(data->args[index + 1], O_RDONLY);
    dup2(fd, 0);
    close(fd);
    free(data->args[index]);
    data->args[index] = ft_calloc(1, 1);
    free(data->args[index + 1]);
    data->args[index + 1] = ft_calloc(1, 1);
    remove_null_args(data);
    exec_cmd(data);
    dup2(prev_fd, 0);
    close(prev_fd);
}

void    output_redirection(t_data *data, int index)
{
    int fd;
    int prev_fd;

    prev_fd = dup(1);
    fd = open(data->args[index + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    dup2(fd, 1);
    close(fd);
    free(data->args[index]);
    data->args[index] = ft_calloc(1, 1);
    free(data->args[index + 1]);
    data->args[index + 1] = ft_calloc(1, 1);
    remove_null_args(data);
    exec_cmd(data);
    dup2(prev_fd, 1);
    close(prev_fd);
}

void    append_redirection(t_data *data, int index)
{
    int fd;
    int prev_fd;

    prev_fd = dup(1);
    fd = open(data->args[index + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
    dup2(fd, 1);
    close(fd);
    free(data->args[index]);
    data->args[index] = ft_calloc(1, 1);
    free(data->args[index + 1]);
    data->args[index + 1] = ft_calloc(1, 1);
    remove_null_args(data);
    exec_cmd(data);
    dup2(prev_fd, 1);
    close(prev_fd);
}

void    exec_here_documents(t_data *data, int index)
{
    int fd[2];
    char *line;
    int prev_fd;

    if(data->args[index + 1] == NULL)
    {
        ft_putendl_fd("minishell: syntax error near unexpected token `newline'", 2);
        return ;
    }
    prev_fd = dup(1);
    pipe(fd);
    dup2(0, fd[0]);
    while (1)
    {
        line = readline("> ");
        data->line = ft_append_str(data->line, "\n");
        data->line = ft_append_str(data->line, line);
        if (ft_strncmp(line, data->args[index + 1], 
            ft_strlen(data->args[index + 1]) + 1) == 0)
        {
            data->line = ft_append_str(data->line, "\n");
            free(line);
            break;
        }
        free(line);
    }
    close(fd[1]);
    dup2(fd[0], 0);
    close(fd[0]);
    free(data->args[index]);
    data->args[index] = ft_calloc(1, 1);
    free(data->args[index + 1]);
    data->args[index + 1] = ft_calloc(1, 1);
    remove_null_args(data);
    exec_cmd(data);
    dup2(prev_fd, 1);
    close(prev_fd);
}

void    remove_redir_args(t_data *data, int index)
{
    while (data->args[index + 2])
    {
        data->args[index] = data->args[2 + index];
        index++;
    }
    data->args[index++] = NULL;
    data->args[index] = NULL;
}