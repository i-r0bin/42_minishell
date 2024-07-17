#include "minishell.h"

void    ft_error(t_data *data, char *arg, char *error);
int     ft_isnumber(char *str);

void    ft_error(t_data *data, char *arg, char *error)
{
    ft_putstr_fd("minishell: ", 2);
    if (arg)
    {
        if (ft_strncmp(data->args[0], "export", 6) == 0)
            ft_putchar_fd('`', 2);
        ft_putstr_fd(arg, 2);
        if (ft_strncmp(data->args[0], "export", 6) == 0)
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