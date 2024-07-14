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

void    init_data(t_data *data, char **env);
void    parse_line(t_data *data);
void    free_data(t_data *data);
void    free_array(char **array);
void    free_env_node(void *env);
void    free_env_content(void *env);
char	**split_cmd(char const *line);
void    signal_handler(int signum);
void    ft_echo(t_data *data);
void    ft_cd(t_data *data);
void    ft_pwd();
void    ft_export(t_data *data);
void    ft_unset(t_data *data);
void    ft_env(t_data *data);
void    exec_cmd(t_data *data);
void    exec_pipe(t_data *data);
void    exec_redirection(t_data *data);
void    exec_bin(t_data *data);
void    wait_and_save_exit_status(t_data *data);
void    exec_builtin(t_data *data);
void    data_env_format(t_data *data);
void    replace_env(t_data *data, int arg_index, char *key_pos);
void    replace_double_quote(t_data *data, int arg_index, char *key_pos, char *env);
void    replace_quote(t_data *data, int arg_index, char quote);
int     key_len(char *key_pos);
char    *formatted_arg_allocation(char *arg, int env_len, int key_len);
char    *get_env(char *key, t_data *data);
void    set_env(char *arg, t_data *data, char *is_global);
t_list  *update_env(char *key, char *value, t_data *data);
void    add_env(char *key, char *value, t_data *data, char *is_global);
void    unset_env(char *key, t_data *data);
char    **env_to_array(t_list *env);
void    print_export(t_data *data);
void    write_exp_var(t_list *var);
t_list  *get_next_sorted_var(t_list *env, char *last);
void    set_env_exp(char *key, t_data *data);
void    set_input_output(t_data *data, int i, int fd[2]);
void    set_fd_pipe(t_data *data, int fd[2], int i);
void    exec_pipe_cmd(t_data *data, char *cmd);
void    input_redirection(t_data *data, int index);
void    output_redirection(t_data *data, int index);
void    append_redirection(t_data *data, int index);
void    exec_here_documents(t_data *data, int index);
void    remove_redir_args(t_data *data, int index);

#endif