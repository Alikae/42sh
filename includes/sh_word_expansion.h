#ifndef SH_WORD_EXPANSION_H
# define SH_WORD_EXPANSION_H

# include <pwd.h>
# include <stdlib.h>
# include <unistd.h>
# include "t_token.h"
# include "sh_env.h"
# include "sh.h"
# include "libft.h"

# define COLON	1
# define ERROR	2
# define LEN	4

typedef struct	s_exp
{
	t_token	*tok;
	int		i;
	int		first_i;
	t_env	**env;
	t_env	*find;
	char	*value;
	char	*name;
	char	*content;
	short	opt;
	short	quote;
}				t_exp;

typedef struct	s_split
{
	int			i;
	t_token		*tok;
	t_token		*sub;
	const char	*split;
}				t_split;

typedef enum	e_arthtype
{
	PLUS = 0,
	MINUS,
	PARENTHESIS,
	MULTI,
	DIV,
	MODULO,
	INCREMENT,
	DECREMENT,
	MORE,
	LESS,
	MORE_EQUAL,
	LESS_EQUAL,
	AND,
	OR,
	EQUAL,
	DIFFERENT
}				t_arthtype;

typedef struct	s_arith
{
	t_arthtype		next_op;
	long int		nb;
	struct s_arith	*next;
	struct s_arith	*sub;
}				t_arith;

void	sh_spetial_quote(char **content);
int		sh_word_expansion(t_exp *exp);
void	sh_parameter_expansion(t_exp *exp);
int		sh_tilde_expansion(char **content, t_env *env);
t_token	*sh_quote_removal(t_token *tok, const char *split);
void	sh_find_quote(t_split *splt, short quote);
int		sh_expansion_size(char *content, int i);
void	sh_print_exp(t_exp *exp, char *where);
void	sh_record_name(t_exp *exp);
void	sh_simple_expansion(t_exp *exp);
void	sh_subsh_expansion(t_exp *exp);

#endif
