#include "minishell.h"

void input_redirection(t_data *data, int index)
{
    int fd;

    fd = open(data->args[index + 1], O_RDONLY);
    dup2(fd, 0);
    close(fd);
    data->args[index] = NULL;
    data->args[index + 1] = NULL;
}

void output_redirection(t_data *data, int index)
{
    int fd;

    fd = open(data->args[index + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    dup2(fd, 1);
    close(fd);
    data->args[index] = NULL;
    data->args[index + 1] = NULL;
}

void append_redirection(t_data *data, int index)
{
    int fd;

    fd = open(data->args[index + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
    dup2(fd, 1);
    close(fd);
    data->args[index] = NULL;
    data->args[index + 1] = NULL;
}

void exec_here_documents(t_data *data, int index)
{
    int fd[2];
    char *line;

    if(data->args[index + 1] == NULL)
    {
        ft_putendl_fd("minishell: syntax error near unexpected token `newline'", 2);
        return ;
    }
    pipe(fd);
    while (1)
    {
        line = readline("> ");
        if (!line || ft_strncmp(line, data->args[index + 1], 
            ft_strlen(data->args[index + 1])) == 0)
        {
            free(line);
            break;
        }
        ft_putendl_fd(line, fd[1]);
        free(line);
    }
    close(fd[1]);
    dup2(fd[0], 0);
    close(fd[0]);
    remove_redir_args(data, index);
}

void remove_redir_args(t_data *data, int index)
{
    while (data->args[index + 2])
    {
        data->args[index] = data->args[2 + index];
        index++;
    }
    data->args[index++] = NULL;
    data->args[index] = NULL;
}