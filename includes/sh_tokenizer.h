/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_tokenizer.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 16:31:21 by thdelmas          #+#    #+#             */
/*   Updated: 2019/11/16 02:16:49 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_TOKENIZER
# define SH_TOKENIZER

# include "sh.h"

int			sh_alias_substitution(t_tokenize_tool *t, int word_begin);
t_token		*create_token(t_toktype type, int index, const char *content);
t_token		*create_token_n(t_toktype type, int index, const char *content, int n);
void		delete_token(t_token *token);
t_token		*tokenize_input(const char *input);
t_token		*recursive_tokenizer(t_tokenize_tool *t, t_toktype actual_compound, t_toktype *terminator);
t_toktype	word_is_reserved(const char *word, int len);
t_toktype	word_is_actual_terminator(const char *word, int len, t_toktype actual_compound);
t_toktype	treat_operator(t_tokenize_tool *t, t_token **p_actual, t_toktype actual_compound);
int			is_compound(t_toktype type);
t_token		*tokenize_compound(t_tokenize_tool *t, t_toktype type, int word_begin);
t_toktype	read_skip_opening_char(t_tokenize_tool *t);
t_toktype	skip_ending_char(t_tokenize_tool *t, t_toktype type, int max_exp);
t_token		*find_token_by_key_until(t_token *tok_begin, t_token *tok_end, t_toktype *type, t_toktype (*types)[2]);
t_token		*tokenize_for(t_tokenize_tool *t, int word_begin);
t_token		*tokenize_if(t_tokenize_tool *t, int word_begin);
t_token		*tokenize_case(t_tokenize_tool *t, int word_begin);
t_token		*tokenize_while(t_tokenize_tool *t, t_toktype type, int word_begin);
t_toktype	read_here_doc(t_tokenize_tool *t, t_token **p_actual, t_toktype type);
void		forward_blanks_newline(t_tokenize_tool *t);
void		forward_blanks(t_tokenize_tool *t);
t_toktype	read_n_skip_operator(t_tokenize_tool *t);
int			read_n_skip_word(t_tokenize_tool *t);
t_token	*handle_syntax_error(t_tokenize_tool *t, const char *s, t_token *to_free);

int			is_redirection_operator(t_toktype type);
t_toktype		fill_redirection(t_tokenize_tool *t, t_token **p_actual, t_toktype type);
t_toktype		treat_redirection(t_tokenize_tool *t, t_token **p_actual, int len);
void		free_ast(t_token *origin);
t_token		*dup_token_with_sub(t_token *origin);
int			exec_compound_subsh(t_sh *p, t_token *tok);
int     	block_wait(t_sh *p, int child_pid, int from_fg);
void	sh_print_onetok(t_token *tok);
void	sh_print_alltok(t_token *tok);
char	*sh_get_tok_content(const char *input);
int		sh_isquoted(const char *str, int index);

#endif
