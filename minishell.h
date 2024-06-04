#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PROMPT "minishell$ "
# define PROMPT_SIZE 11
# define MAX_CMD_SIZE 4096
# define MAX_CMD_ARGS 4096
# define MAX_CMD_PIPES 4096
# define MAX_CMD_FILES 4096
# define MAX_CMD_ENV 4096
# define MAX_CMD_PATH 4096


typedef struct s_cmd
{
    char	*cmd;
    char	*args[MAX_CMD_ARGS];
    char	*pipes[MAX_CMD_PIPES];
    char	*files[MAX_CMD_FILES];
    char	*env[MAX_CMD_ENV];
    char	*path[MAX_CMD_PATH];
}	t_cmd;

typedef struct s_data
{
    t_list *env;
    char *line;
    char *cmd;
    char **args;
    char **pipe;
    int *fd;
    int *fd_pipe;
    int fd_in;
    int fd_out;
    int status;
    pid_t pid;
    int exit;
} t_data;

void    ft_error(char *str);
void    ft_free(char **str);
void    ft_free_cmd(t_cmd *cmd);
void    ft_free_data(t_data *data);
void    ft_init_data(t_data *data);
void    ft_parse_cmd(t_data *data);
void    ft_parse_args(t_data *data);
void    ft_parse_pipes(t_data *data);
void    ft_parse_files(t_data *data);
void    ft_parse_env(t_data *data);
void    ft_parse_path(t_data *data);
void    ft_exec_cmd(t_data *data);
void    ft_exec_cmd_path(t_data *data);
void    ft_exec_cmd_files(t_data *data);
void    ft_exec_cmd_pipes(t_data *data);
void    ft_exec_cmd_args(t_data *data);
void    ft_exec_cmd_env(t_data *data);
void    ft_exec_cmd_builtin(t_data *data);
void    ft_exec_cmd_builtin_cd(t_data *data);
void    ft_exec_cmd_builtin_echo(t_data *data);
void    ft_exec_cmd_builtin_env(t_data *data);
void    ft_exec_cmd_builtin_exit(t_data *data);
void    ft_exec_cmd_builtin_export(t_data *data);
void    ft_exec_cmd_builtin_pwd(t_data *data);
void    ft_exec_cmd_builtin_unset(t_data *data);
void    ft_exec_cmd_builtin_export_add(t_data *data, char *str);
void    ft_exec_cmd_builtin_export_del(t_data *data, char *str);
void    ft_exec_cmd_builtin_export_print(t_data *data);
void    ft_exec_cmd_builtin_export_sort(t_data *data);
void    ft_exec_cmd_builtin_export_sort_swap(char **str1, char **str2);

#endif