#ifndef T_TOKEN_H
# define T_TOKEN_H

//# include "sh.h"

typedef enum	e_toktype
{
	SH_NULL = 0,
	SH_WORD,
	SH_ASSIGN,
	SH_LESS,
	SH_GREAT,
	SH_AND,
	SH_OR,
	SH_SEMI,
	SH_AND_IF,
	SH_OR_IF,
	SH_DSEMI,
	SH_DLESS,
	SH_DGREAT,
	SH_LESSAND,
	SH_GREATAND,
	SH_LESSGREAT,
	SH_DLESSDASH,
	SH_CLOBBER,
	SH_IF,
	SH_THEN,
	SH_ELSE,
	SH_ELIF,
	SH_FI,
	SH_DO,
	SH_DONE,
	SH_CASE,
	SH_ESAC,
	SH_WHILE,
	SH_UNTIL,
	SH_FOR,
	SH_BRACES,
	SH_BANG,
	SH_IN,
	SH_FUNC,
	SH_SUBSH, 		// ( )
	SH_SUBSH_EXP,	// $( )
	SH_PARAM_EXP,	// ${ }
	SH_ARITH_EXP,	// $(( ))
	SH_NEWLINE,
	SH_GROUP,
	
	SH_QUOTE,
	SH_DQUOTE,
	SH_BQUOTE,

	SH_SYNTAX_ERROR
}				t_toktype;

typedef struct	s_token
{
	t_toktype		type;
	char			*content;
	struct s_token	*sub;
	struct s_token	*next;
}				t_token;

typedef struct s_tokenize_tool
{
	const char  *input;
	int         i;
	int         word_nb;
}               t_tokenize_tool;

//FOR DEBUG
typedef struct s_sh t_sh;
void		print_all_tokens(t_sh *p, t_token *t, int lvl);
//FOR DEBUG
t_token		*create_token(t_toktype type, const char *content);
t_token		*create_token_n(t_toktype type, const char *content, int n);
void		delete_token(t_token *token);
t_token		*tokenize_input(const char *input);
t_token		*recursive_tokenizer(t_tokenize_tool *t, t_toktype actual_compound, t_toktype *terminator);
t_toktype	word_is_reserved(const char *word, int len);
t_toktype	word_is_actual_terminator(const char *word, int len, t_toktype actual_compound);
t_toktype	treat_operator(t_tokenize_tool *t, t_token **p_actual, t_toktype actual_compound);
int			is_compound(t_toktype type);
t_token		*tokenize_compound(t_tokenize_tool *t, t_toktype type);
t_toktype	read_skip_opening_char(t_tokenize_tool *t);
void		skip_ending_char(t_tokenize_tool *t, t_toktype type);
t_token		*find_token_by_key_until(t_token *tok_begin, t_token *tok_end, t_toktype *type, t_toktype (*types)[2]);
t_token		*tokenize_for(t_tokenize_tool *t);
t_token		*tokenize_if(t_tokenize_tool *t);
t_token		*tokenize_case(t_tokenize_tool *t);
t_token		*tokenize_while(t_tokenize_tool *t, t_toktype type);
t_toktype	read_here_doc(t_tokenize_tool *t, t_token **p_actual, t_toktype type);
void		forward_blanks_newline(t_tokenize_tool *t);
void		forward_blanks(t_tokenize_tool *t);
t_toktype	read_n_skip_operator(t_tokenize_tool *t);
int			read_n_skip_word(t_tokenize_tool *t);
t_token	*handle_syntax_error(t_tokenize_tool *t, const char *s, t_token *to_free);

int			is_redirection_operator(t_toktype type);
t_toktype		fill_redirection(t_tokenize_tool *t, t_token **p_actual, t_toktype type);
#endif
