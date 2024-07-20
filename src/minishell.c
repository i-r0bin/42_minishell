#include "minishell.h"

int main(int ac, char **av, char **env)
{
    t_data data;

    (void)ac;
    (void)av;
    init_data(&data, env);
    signal(SIGINT, signal_handler);
    signal(SIGQUIT, SIG_IGN);
    while (data.exit == 0)
    {
        data.line = readline("minishell$ ");
        if (!data.line)
            break;
        if (data.line[0] != '\0')
        {
            parse_line(&data);
            if (data.cmd && data.cmd[0])
                add_history(data.line);
        }
        free(data.line);
    }
    free_data(&data);
    ft_putendl_fd("exit", 1);
    exit(data.status);
    return (0);
}

void signal_handler(int signum)
{
    if (signum == SIGINT)
    {
        write(1, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}