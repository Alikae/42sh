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
char	*sh_tab_fusion(char **t);
t_token	*sh_expansion(char *tok_content, t_env **env);

#endif
