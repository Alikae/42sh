/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_tokens.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 15:13:46 by thdelmas          #+#    #+#             */
/*   Updated: 2019/09/22 00:05:14 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_TOKENS
# define SH_TOKENS

# include <unistd.h>
# include "sh.h"

void		print_all_tokens(t_sh *p, t_token *t, int lvl);
t_toktype	sh_match_tok_op(const char *tok_content, size_t i);
t_toktype	sh_get_res(const char *tok_content);
t_toktype	sh_is_res_word(const char *tok_content, size_t i);
t_toktype	sh_get_tok_type(const char *in, size_t i);
t_token		*sh_get_tok_sub(const char *tok_content);
t_token		*sh_tokenizer(const char *input);
t_token		*sh_init_tok(t_toktype type, const char *content);


#endif
