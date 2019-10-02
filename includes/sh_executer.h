/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_executer.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 13:54:38 by thdelmas          #+#    #+#             */
/*   Updated: 2019/10/01 06:49:27 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_EXECUTER_H
# define SH_EXECUTER_H

typedef struct s_token t_token;
typedef struct s_sh t_sh;
typedef struct s_env t_env;
typedef struct s_pipe_lst t_pipe_lst;

int		sh_exec_stdin(void);
int		sh_exec_file(void);
int		sh_exec_arg(void);
int		exec_script(t_sh *p, t_token *token_begin, t_token *token_end);
int		exec_compound_case(t_sh *p, t_token *tok);
int		exec_compound_for(t_sh *p, t_token *tok);
int     exec_compound_while(t_sh *p, t_token *tok, t_toktype type);
int     exec_compound_if(t_sh *p, t_token *tok);
int		exec_compound_command(t_sh *p, t_token *token_compound, int type);
int		exec_command(t_sh *p, t_token *token_begin, t_token *token_end);
int		exec_command_in_background(t_sh *p, t_token *token_begin, t_token *token_end, int force_pgid);
int		exec_command_to_pipe(t_sh *p, t_token *token_begin, t_token *token_end, int pipe_in_fd);
int		exec_and_or_in_background(t_sh *p, t_token *token_begin, t_token *token_end);
int		exec_script(t_sh *p, t_token *token_begin, t_token *token_end);
int     exec_path(t_sh *p, char *path);
int		exec_prgm(t_sh *p);
int     exec_builtin(t_sh *p, int (*f)(int, char **, t_env **));
int		exec_simple_command(t_sh *p, t_token *token_begin, t_token *token_end);
int		sh_exec_arg(void);
int     exec_script(t_sh *p, t_token *token_begin, t_token *token_end);
int		sh_exec_file(void);
int		sh_exec_stdin(void);
void	exec_pipeline(t_sh *p, t_token *token_begin, t_token *token_end);
void	exec_pipeline(t_sh *p, t_token *token_begin, t_token *token_end);
void	exec_and_or(t_sh *p, t_token *token_begin, t_token *token_end);
int		stock_redirections_assignements_compound(t_sh *p, t_token *token_begin, t_token *token_end);
void	stock_redirection(t_sh *p, t_token *token, int *nb_redirections);
int		stock_redirections_assignements_argvs(t_sh *p, t_token *token_begin, t_token *token_end, int *nb_assign);
void	push_pipe_lst(t_pipe_lst **p_origin, int pipe[2]);
void	close_pipes_parent(t_sh *p);
int		fork_process(t_sh *p, int foreground, int default_sig);

#endif
