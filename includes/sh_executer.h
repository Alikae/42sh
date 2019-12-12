/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_executer.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 13:54:38 by thdelmas          #+#    #+#             */
/*   Updated: 2019/12/09 11:21:00 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_EXECUTER_H
# define SH_EXECUTER_H

# include <sys/stat.h>

typedef struct s_token t_token;
typedef struct s_sh t_sh;
typedef struct s_env t_env;
typedef struct s_pipe_lst t_pipe_lst;

int		sh_script(const char *path);
int		sh_exec_stdin(void);
int		sh_exec_file(void);
int		sh_exec_arg(void);
int		exec_script(t_sh *p, t_token *token_begin);
int		exec_compound_case(t_sh *p, t_token *tok);
int		exec_compound_for(t_sh *p, t_token *tok);
int     exec_compound_while(t_sh *p, t_token *tok, t_toktype type);
int     exec_compound_if(t_sh *p, t_token *tok);
int		exec_compound_command(t_sh *p, t_token *token_compound, int type);
int		exec_command(t_sh *p, t_token *token_begin, t_token *token_end);
int		exec_command_in_background(t_sh *p, t_token *token_begin, t_token *token_end);
int		exec_command_to_pipe(t_sh *p, t_token *token_begin, t_token *token_end, int pipe_in_fd);
int		exec_and_or_in_background(t_sh *p, t_token *token_begin, t_token *token_end);
int     exec_path(t_sh *p, char *path, char **child_argv);
int		exec_prgm(t_sh *p, char **child_argv);
int     exec_builtin(t_sh *p, int (*f)(int, char **, t_env **), char **child_argv);
int		exec_simple_command(t_sh *p, t_token *token_begin, t_token *token_end);
int		sh_exec_arg(void);
int		sh_exec_file(void);
int		sh_exec_stdin(void);
void	sh_exec_default(void);
void	exec_pipeline(t_sh *p, t_token *token_begin, t_token *token_end);
void	exec_and_or(t_sh *p, t_token *token_begin, t_token *token_end);
int		stock_redirections_assignements_compound(t_sh *p, t_token *token_begin, t_token *token_end, int *nb_assign);
void	stock_redirection(t_sh *p, t_token *token, int *nb_redirections);
int		stock_redirections_assignements_argvs(t_token *token_begin, t_token *token_end, int *nb_assign, char ***child_argv);
void	push_pipe_lst(t_pipe_lst **p_origin, int pipe[2]);
void	close_pipes_parent(t_sh *p);
int		fork_process(t_sh *p, int foreground);
void	remove_opened_files(t_sh *p);
void	del_n_assign_lst(t_sh *p, int n);
void	save_std_fds(t_sh *p);
void	restore_std_fds(t_sh *p);
void	generate_redirections(t_sh *p);
void	gen_redirections_recursively(t_sh *p, t_redirect_lst *lst);
void	close_all_redirections(t_sh *p);
void	print_redirections(t_sh *p, t_redirect_lst *origin);
void	delete_close_all_pipe_lst(t_pipe_lst *lst);
int		tablen(char **tab);
char	*get_next_path(const char *path, char **all_paths, int i);
char	*get_real_path(const char *path, struct stat *st);
t_token	*is_defined_function(char *name);
int		exec_function(t_sh *p, t_token *func, char **child_argv);
t_token	*is_function_definition(t_token *token_begin, t_token *token_end);
int		store_func(t_sh *p, t_token *function);
void	remove_old_function(const char *name);
int		exec_prgm(t_sh *p, char **child_argv);
int		can_exec(struct stat *st);
int     exec_path(t_sh *p, char *path, char **child_argv);
int     block_wait(t_sh *p, int child_pid, int from_fg);
char	**transform_env_for_child(t_env *env);
int		create_open_file(t_sh *p, char *path, t_toktype type);
int	open_with_redirection_flags(char *real_path, t_toktype type);
int		file_is_already_open(t_sh *p, char *name);
void	remove_opened_files(t_sh *p);
void	push_to_opened_files(t_sh *p, char *name, int fd);
char	**transform_env_for_child(t_env *env);
int		count_argv(t_token *token_begin, t_token *token_end);
char	**build_child_argvs(t_token *ast);
int		(*sh_is_builtin(const char *cmd))(int ac, char **av, t_env **ev);
void	stock_redirection(t_sh *p, t_token *token, int *nb_redirections);
void	stock_lessgreatand(t_sh *p, t_token *token, int *nb_redirections);
void	stock_here_document(t_sh *p, t_token *tok, int *nb_redirections);
int		push_redirections(t_sh *p, int fd_in, int fd_out, t_toktype type);
void	handle_assigns(t_sh *p);
void	restore_before_assigns(t_sh *p);
void	print_assign(t_sh *p);
int		handle_no_cmd_name(t_sh *p, char **child_argv);
void	restore_before_assigns(t_sh *p);
void	stock_assign(t_sh *p, t_token *token, int *nb_assign);
void	del_n_assign_lst(t_sh *p, int n);
int     block_wait(t_sh *p, int child_pid, int from_fg);

#endif
