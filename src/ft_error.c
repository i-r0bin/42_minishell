#include "minishell.h"

void    ft_error(t_data *data, char *arg, char *error);
int     ft_isnumber(char *str);

void    ft_error(t_data *data, char *arg, char *error)
{
    ft_putstr_fd("minishell: ", 2);
    if (arg)
    {
        if (ft_strncmp(data->args[0], "export", 7) == 0)
            ft_putchar_fd('`', 2);
        ft_putstr_fd(arg, 2);
        if (ft_strncmp(data->args[0], "export", 7) == 0)
            ft_putchar_fd('\'', 2);
        ft_putstr_fd(": ", 2);
    }
    ft_putendl_fd(error, 2);
    if (data->status == 0)
        data->status = 1;
}

int ft_isnumber(char *str)
{
    int i;

    i = 0;
    if (str[i] == '-' || str[i] == '+')
        i++;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

int     check_dir(t_data *data, char *dir)
{
    struct stat path_stat;
    
    if ((dir[0] == '.' && dir[1] == '/') || dir[0] == '/' || ft_isalpha(dir[0]))
    {
        if (stat(dir, &path_stat) != 0)
        {
            ft_error(data, dir, "No such file or directory");
            data->status = 1;
            return (data->status);
        }
    }
    else if (ft_isdigit(dir[0]))
    {
        ft_error(data, dir, "No such file or directory");
        data->status = 1;
        return (data->status);
    }
    else if (!ft_isalpha(dir[0]) && dir[0] != '$')
    {
        ft_error(data, dir, "No such file or directory");
        data->status = 2;
        return (data->status);
    }
    return (0);
}

int     check_bin(t_data *data)
{
    struct stat path_stat;
    
    if ((data->args[0][0] == '.' && data->args[0][1] == '/') || data->args[0][0] == '/')
    {
        if (stat(data->args[0], &path_stat) == 0)
        {
            if (S_ISDIR(path_stat.st_mode)) {
                ft_error(data, data->args[0], "Is a directory");
                data->status = 126;
                return (data->status);
            }
        }
        else 
        {
            ft_error(data, data->args[0], "No such file or directory");
            data->status = 127;
            return (data->status);
        }
    }
    return (0);
}

int     check_token_error(t_data *data)
{
    int     i;
    char    *token;
    char    *error;

    i = 0;
    while (data->args[i])
    {
        token = NULL;
        if (data->args[i][0] == '<' || data->args[i][0] == '>' || data->args[i][0] == '|')
        {
            if (ft_strlen(data->args[i]) > 2 && data->args[i][0] != '|')
            {
                token = ft_calloc(3, sizeof(char));
                ft_strlcpy(token, data->args[i], 3);
            }
            else if (data->args[i][1] && data->args[i][0] != data->args[i][1])
            {
                token = ft_calloc(2, sizeof(char));
                token[0] = data->args[i][0];
            }
        }
        if (token)
        {
            error = ft_strjoin("syntax error near unexpected token `", token);
            error = ft_append_str(error, "\'");
            ft_error(data, NULL, error);
            free(token);
            free(error);
            return (1);
        }
        i++;
    }
    return (0);
}