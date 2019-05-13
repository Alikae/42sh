/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_tokenizer.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 16:31:21 by thdelmas          #+#    #+#             */
/*   Updated: 2019/05/13 22:20:39 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_TOKENIZER
# define SH_TOKENIZER

# include "sh_tokens.h"
# include <stdlib.h>

void	sh_print_onetok(t_token *tok);
void	sh_print_alltok(t_token *tok);
char	*sh_get_tok_content(const char *input);
size_t		sh_set_toktype(const char *input, t_toktype *type);
t_toktype	sh_match_tok_op(const char *tok_content, int i);
t_token	*sh_get_tok_sub(const char *tok_content);
t_token	*sh_tokenizer(const char *input);
t_token	*sh_init_tok(const char *input, t_token *parent);

#endif
