/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_word_expansion.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 06:44:44 by tcillard          #+#    #+#             */
/*   Updated: 2019/12/17 00:05:30 by tcillard         ###   ########.fr       */
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


typedef enum	e_arthtype
{
	INIT = 0,
	NUMBER,
	PLUS,
	MINUS,
	MULTI,
	DIV,
	MODULO,
	MORE,
	LESS,
	MORE_EQUAL,
	LESS_EQUAL,
	AND,
	OR,
	AND_AND,
	OR_OR,
	DIFFERENT,
	EQUAL,
	NOP
}				t_arthtype;

typedef struct	s_arith
{
	t_arthtype		next_op;
	long int		nb;
	struct s_arith	*next;
	struct s_arith	*sub;
}				t_arith;

void		sh_subsh_quote(t_exp *exp, short *quote);
void		sh_spetial_quote(char **content);
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
int 		sh_all_char_operator(char c);
int			sh_valide_arith(char *str);
char		**sh_strsplit_arth(const char *s);
long int	sh_long_atoi(const char *s1);
char 	  *sh_long_itoa(long int n);
void		bst_print_dot(t_arith *a, char *str, char *arth);
int			sh_is_next_word(t_split *splt);
int			sh_check_split(t_split *splt);
void		sh_remove_char(char **str, int i);
int			sh_check_quote(t_split *splt, short quote);
int			sh_check_split(t_split *splt);
void		sh_token_spliting(t_split *splt, int reset);
void		sh_next_token(t_token **new);
void		sh_word_opt(t_exp *exp);
void		sh_spetial_quote(char **content);
void		sh_sub_word(t_exp *exp);
void		sh_next_word(t_exp *exp);
void		sh_add_var(t_exp *exp);
void		sh_assign_word(t_exp *exp);
void		sh_record_less_option(t_exp *exp);

#endif
