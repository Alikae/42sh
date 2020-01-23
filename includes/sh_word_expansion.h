/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_word_expansion.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 06:44:44 by tcillard          #+#    #+#             */
/*   Updated: 2020/01/23 10:42:28 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_WORD_EXPANSION_H
# define SH_WORD_EXPANSION_H

# include <pwd.h>
# include <stdlib.h>
# include <unistd.h>
# include "sh_types.h"
# include "sh.h"

# define COLON	1
# define ERROR	2
# define LEN	4

void		sh_subsh_quote(t_exp *exp, short *quote);
void		sh_special_quote(char **content);
int			sh_word_expansion(t_exp *exp);
void		sh_parameter_expansion(t_exp *exp);
int			sh_tilde_expansion(char **content, t_env *env);
t_token		*sh_quote_removal(t_token *tok, const char *split, short ifs);
void		sh_find_quote(t_split *splt, short quote);
int			sh_expansion_size(char *content, int i);
t_token		*sh_expansion(char *content, t_env **env, short ifs);
void		sh_print_exp(t_exp *exp, char *where);
void		sh_record_name(t_exp *exp);
void		sh_simple_expansion(t_exp *exp);
void		sh_subsh_expansion(t_exp *exp);
void		sh_arithmetic_expansion(t_exp *exp);
void		sh_str_start_end(char **dest, char *src, int i, int n);
void		sh_sub_arith_var(char **str);
int			sh_all_char_operator(char c);
int			sh_valide_arith(char *str);
char		**sh_strsplit_arth(const char *s);
char		*sh_long_itoa(long int n);
void		bst_print_dot(t_arith *a, char *str, char *arth);
int			sh_is_next_word(t_split *splt);
int			sh_check_split(t_split *splt);
void		sh_remove_char(char **str, int *i);
int			sh_check_quote(t_split *splt, short quote);
int			sh_check_split(t_split *splt);
void		sh_token_spliting(t_split *splt, int reset);
void		sh_next_token(t_token **new);
void		sh_word_opt(t_exp *exp);
void		sh_sub_word(t_exp *exp);
void		sh_next_word(t_exp *exp);
void		sh_assign_word(t_exp *exp);
void		sh_record_less_option(t_exp *exp);
void		sh_pattern_matching(t_exp *exp);
char		*subtitute_prefix_pattern(const char *str
			, const char *pattern, short short_or_long);
char		*subtitute_suffix_pattern(const char *str
			, const char *pattern, short short_or_long);
void		sh_special_parameters(t_exp *exp, int where);
int			sh_skip_white_space(char *str, int i);
int			sh_skip_number(char *str, int i);
int			sh_arth_syntax_error(char *str, int i);
void		sh_str_start_end(char **dest, char *src, int i, int n);
void		sh_subsh_quote(t_exp *exp, short *quote);
int			sh_commande_string_size(t_exp *exp, char c);
void		sh_record_commande_string(t_exp *exp);
int			sh_error_expression_name(char *str);
int			sh_check_value(char *str);
char		*sh_find_arth_var_value(char **str);
void		sh_sub_var(char **value, char **str, int beg, int ed);
int			sh_tab_len(char **tab);
void		sh_init_exp(t_env **env, t_exp *exp, char *tok_content);
void		sh_free_exp(t_exp *exp, char **tok_content);
int			sh_word_error(t_exp *exp);
void		sh_sub_token(t_exp *exp);
long int	sh_exec_arith(t_arith *arith);
void		sh_init_arith(t_arith **arith);
long int	sh_atoi_index(char *str, int *i);
char		*sh_long_itoa(long int n);
void		sh_write_less_op(char *str, int i, t_arith **arith);
int			sh_all_char_operator(char c);
void		sh_count_priority(char *c, int i, int count, int *less_count);
int			sh_special_char_operator(char *str, int i);
int			sh_arth_error_parenthesis(char *str);
void		sh_free_arith_ast(t_arith *arith);
int			sh_check_arth(char *name);
void		sh_init_ast(long int number, t_arith **arith);
int			sh_is_number(char *str, int i, int end);
int			sh_next_less_operator(char *str, int begin
			, int end, t_arith **arith);
int			sh_valid_operator(char *str, int begin);
void		sh_record_arithmetic_string(t_exp *exp);
int			sh_arithmetic_string_size(t_exp *exp);
int			sh_error_not_valide_arth_name(char *str, int i);
long int	sh_long_atoi(char *str);
long int	sh_long_power(int pw);
int			sh_error_div_by_0(void);
int			sh_skip_number_par(char *str, int i);
int			sh_is_valid_operator(char *str, int i);
int			sh_parenthesis_counter(char *str, int *i, int s1);
#endif
