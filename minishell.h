/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppezzull <ppezzull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:02:30 by ppezzull          #+#    #+#             */
/*   Updated: 2024/07/23 18:02:35 by ppezzull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_data
{
	t_list	*env;
	char	*line;
	char	*cmd;
	char	**args;
	char	**pipes_cmd;
	int		pipe_num;
	int		fd_pipe[2];
	int		status;
	pid_t	pid;
}			t_data;

/* ---------- DATA UTILS ---------- */
void		init_data(t_data *data, char **env);
void		reset_data(t_data *data);
void		free_data(t_data *data);
void		remove_null_args(t_data *data);
void		free_env_node(void *env);

/* ---------- UTILS ---------- */
int			ft_isnumber(char *str);
int			get_arr_len(char **arr);
char		*ft_append_str(char *s1, char *s2);
void		free_array(char **array);
void		free_env_content(void *env);

/* ---------- ARGS FORMAT ---------- */
void		parse_line(t_data *data);
char		**split_args(char const *line);
int			get_args_num(char const *line);
int			get_arg_size(char const *s);
int			get_null_args_num(t_data *data);

/* ---------- ENV DATA ---------- */
char		*get_env(char *key, t_data *data);
void		set_env(char *arg, t_data *data, char *is_global);
t_list		*update_env(char *key, char *value, t_data *data);
void		add_env(char *key, char *value, t_data *data, char *is_global);
void		unset_env(char *key, t_data *data);

/* ---------- ENV FORMAT ---------- */
void		data_env_format(t_data *data);
void		replace_env(t_data *data, int arg_index, char *key_pos, char *env);
char		*formatted_arg_allocation(char *arg, int env_len, int key_len);
int			envcmp(const char *s, const char *env);
char		**env_to_array(t_list *env);

/* ---------- FORMAT UTILS ---------- */
int			check_quote(const char *line, int index, int open, char quote);
char		*get_quote(char *arg);
void		remove_quotes(t_data *data, int arg_index, char quote);
int			get_key_len(char *key_pos);
char		*get_key_pos(char *arg);

/* ---------- TOKEN FORMAT ---------- */
char		*token_format(char *line);
size_t		get_line_len(char *line);
void		format_len(char *line, int *i, size_t *len);
void		format_proc(char *line, char *new_line, int *i, int *len);
int			is_token(t_data *data, int i);

/* ---------- EXEC ---------- */
void		exec_cmd(t_data *data);
void		exec_builtin(t_data *data);
void		exec_bin(t_data *data);
int			exec_bin_paths(t_data *data, char **paths, char **envp);
int			exec_bin_with_path(t_data *data, char **envp);

/* ---------- BUILTINS ---------- */
// PWD
void		ft_pwd(void);
// ENV
void		ft_env(t_data *data);
// UNSET
void		ft_unset(t_data *data);
// EXIT
void		ft_exit(t_data *data);
int			validate_exit_args(t_data *data);
// ECHO
void		ft_echo(t_data *data);
int			newline_flag(char *arg);
// CD
void		ft_cd(t_data *data);
char		*determine_cd_path(t_data *data);
void		update_pwd(t_data *data);
// EXPORT
void		ft_export(t_data *data);
void		print_export(t_data *data);
void		write_exp_var(t_list *var);
t_list		*get_next_sorted_var(t_list *env, char *last);

/* ---------- PIPE ---------- */
void		exec_pipe(t_data *data);
void		handle_pipes(t_data *data);
void		handle_fork(t_data *data, int i, int fd[2]);
void		execute_child_process(t_data *data, int i, int fd[2]);

/* ---------- PIPE & REDIR UTILS ---------- */
void		split_pipes(t_data *data);
void		get_pipe_len(t_data *data);
void		set_input_output(t_data *data, int i, int fd[2]);
void		set_fd_pipe(t_data *data, int fd[2]);
void		exec_here_input(t_data *data, int index);
void		reformat_redir_args(t_data *data, int index);

/* ---------- REDIR UTILS ---------- */
void		exec_redirection(t_data *data);
int			input_redirection(t_data *data, int index);
int			output_redirection(t_data *data, int index);
int			append_redirection(t_data *data, int index);
int			exec_here_documents(t_data *data, int index);

/* ---------- ERROR HANDLING ---------- */
void		ft_error(t_data *data, char *arg, char *error);
void		handle_pipe_error(const char *message);
int			handle_token_error(t_data *data, int i);
void		handle_cd_error(t_data *data, char *path);
int			handle_export_error(t_data *data, char *arg);

/* ---------- ERROR UTILS ---------- */
int			check_dir(t_data *data, char *dir);
int			check_file_permissions(char *file, int flags);
int			check_bin(t_data *data);
int			check_file_status(t_data *data, struct stat *path_stat);
int			check_token_error(t_data *data);

/* ---------- MINI UTILS ---------- */
void		signal_handler(int signum);
void		wait_and_save_exit_status(t_data *data);

#endif
