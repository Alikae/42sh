/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_tokens.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 15:13:46 by thdelmas          #+#    #+#             */
/*   Updated: 2019/06/03 22:41:37 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_TOKENS
# define SH_TOKENS

# include <unistd.h>

typedef enum	e_toktype
{
	SH_NULL = 0,
	SH_EOS,
	SH_EOF,
	SH_WORD,
	SH_ASSIGN_WORD,
	SH_NAME,
	SH_NEWLINE,
	SH_IO_NUMBER,
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
	SH_LBRACE,
	SH_RBRACE,
	SH_BANG,
	SH_IN,
	SH_FUNC,
	SH_LSUBSH,
	SH_RSUBSH,
	SH_LSUBSH_EXP,
	SH_RSUBSH_EXP,
	SH_LPARAM_EXP,
	SH_RPARAM_EXP,
	SH_LARITH_EXP,
	SH_RARITH_EXP,
	SH_GROUP_TOKEN,
	SH_BRACES
}				t_toktype;

typedef struct      s_token
{
	int				type;
	struct s_token	*sub;
	char			*content;
	struct s_token  *next;
}                   t_token;

void		print_all_tokens(t_token *t, int lvl);
t_toktype	sh_match_tok_op(const char *tok_content, size_t i);
t_toktype	sh_get_res(const char *tok_content);
t_toktype	sh_is_res_word(const char *tok_content, size_t i);
t_token		*sh_get_tok_sub(const char *tok_content);
t_token		*sh_tokenizer(const char *input);
t_token		*sh_init_tok(const char *input, size_t i);


#endif
