/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_tokenizer.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 16:31:21 by thdelmas          #+#    #+#             */
/*   Updated: 2020/01/13 03:14:40 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_TOKENIZER_H
# define SH_TOKENIZER_H

# include "sh.h"

const char	*assign_patend(t_toktype type);
t_toktype	is_opening_char(t_toktool *t);
int			sh_alias_substitution(t_toktool *t, int word_begin);
t_token		*create_token(t_toktype type, int index, const char *content);
t_token		*create_token_n(t_toktype type, int index,
			const char *content, int n);
void		delete_token(t_token *token);
t_token		*tokenize_input(const char *input);
t_token		*recursive_tokenizer(t_toktool *t,
			t_toktype actual_compound, t_toktype *terminator);
t_toktype	word_is_reserved(const char *word, int len);
t_toktype	word_is_actual_term(const char *word, int len,
			t_toktype actual_compound);
t_toktype	treat_operator(t_toktool *t, t_token **p_actual,
			t_toktype actual_compound);
int			is_compound(t_toktype type);
t_token		*tokenize_compound(t_toktool *t, t_toktype type, int word_begin);
t_toktype	read_skip_opening_char(t_toktool *t);
t_toktype	skip_ending_char(t_toktool *t, t_toktype type, int max_exp);
t_token		*find_token_by_key_until(t_token *tok_begin, t_token *tok_end,
			t_toktype *type, t_toktype (*types)[2]);
t_token		*tokenize_for(t_toktool *t, int word_begin);
t_token		*tokenize_if(t_toktool *t, int word_begin);
t_token		*tokenize_case(t_toktool *t, int word_begin);
t_token		*tokenize_while(t_toktool *t, t_toktype type, int word_begin);
t_toktype	read_here_doc(t_toktool *t, t_token **p_actual);
void		forward_blanks_newline(t_toktool *t);
void		forward_blanks(t_toktool *t);
t_toktype	read_n_skip_operator(t_toktool *t);
int			read_n_skip_word(t_toktool *t);
t_token		*handle_syntax_error(t_toktool *t, const char *s, t_token *to_free);
int			is_redirection_operator(t_toktype type);
t_toktype	fill_redirection(t_toktool *t, t_token **p_actual, t_toktype type);
t_toktype	treat_redirection(t_toktool *t, t_token **p_actual, int len);
void		free_ast(t_token *origin);
t_token		*dup_token_with_sub(t_token *origin);
int			exec_compound_subsh(t_sh *p, t_token *tok);
int			block_wait(t_sh *p, int child_pid, int from_fg);
void		sh_print_onetok(t_token *tok);
void		sh_print_alltok(t_token *tok);
char		*sh_get_tok_content(const char *input);
int			sh_isquoted(const char *str, int index);
t_toktype	handle_reserved_and_normals_word(t_toktool *t,
			int	word_begin, t_token **p_actual);
t_toktype	treat_word(t_toktool *t, t_token **p_actual,
			t_toktype actual_compound);
int			word_out_of_context(t_toktype type);
t_toktype	handle_functions_n_terminator(t_toktool *t,
			t_token **p_actual, t_toktype actual_compound, int word_begin);
t_toktype	tokenize_function(t_toktool *t, t_token **p_actual,
			int name_begin);
t_toktype	handle_function_error(t_toktool *t, t_toktype *type);
int			next_is_parenthesis(t_toktool *t);
int			count_token_words_in_str(const char *str);
int			read_n_skip_word(t_toktool *t);
int			process_read_n_skip_word(int *escaped, t_toktool *t, int *n);
int			is_word_char(char c);
int			is_io_nb(t_toktool *t);
t_toktype	fill_redirection(t_toktool *t, t_token **p_actual,
			t_toktype type);
t_toktype	treat_redirection(t_toktool *t, t_token **p_actual,
			int len);
t_toktype	tokenize_reserved_word(t_toktool *t, t_token **p_actual,
			t_toktype type, int word_begin);
t_token		*dup_ast(t_token *origin);
t_toktype	read_n_skip_operator(t_toktool *t);
char		*dupfilsdup(const char *content);
t_toktype	read_here_doc(t_toktool *t, t_token **p_actual);
t_token		*handle_compound_tokenizer_error(t_toktool *t,
			t_token *compound_token, const char *str);
t_token		*set_unfinished_cmd(t_token *token);
t_token		*handle_syntax_error(t_toktool *t, const char *s,
			t_token *to_free);
void		forward_blanks(t_toktool *t);
int			tokenize_case_pattern_2(t_toktool *t, int word_begin,
			t_token *actual);
int			tok_case_pattern_3(t_toktool *t, t_token *actual,
			int forbidden_esac, t_toktype *next_separator);
int			tokenize_case_pattern(t_toktool *t, t_toktype *next_separator,
			t_token *actual);
int			tokenize_case_elem_2(t_toktool *t, t_toktype *next_separator,
			t_token **actual, t_token **origin);
int			tokenize_case_elem_3(t_toktool *t, int word_begin,
			t_toktype *next_separator, t_token *origin);
t_token		*tokenize_case_elem(t_toktool *t, t_toktype *next_separator,
			int *esac_finded);
int			tokenize_case_name(t_toktool *t, t_token **compound_token,
			int case_index);
int			read_n_skip_in(t_toktool *t);
int			tokenize_case_lists_2(t_toktool *t, t_toktype next_separator);
int			tokenize_case_lists(t_toktool *t, t_token **previous_next);
t_token		*tokenize_if(t_toktool *t, int word_begin);
int			tokenize_if_begin(t_toktool *t, t_token *compound_token,
			t_toktype *next_separator, int word_begin);
t_token		*handle_tokenize_if_errors(t_toktool *t, const char *message,
			t_token *compound_token);
int			limit_compound_is_reached(void);
t_token		*tokenize_for(t_toktool *t, int word_begin);
t_token		*tokenize_for_errors(t_toktool *t, const char *message,
			t_token *compound_token);
int			tokenize_for_do(t_toktool *t, t_token *compound);
int			tokenize_for_in(t_toktool *t, t_token *compound_token);
int			tokenize_for_name(t_toktool *t, t_token *compound_token);
t_token		*tokenize_for_do_group(t_toktool *t, t_token *compound);
t_token		*tokenize_for_wordlist(t_toktool *t);
#endif
