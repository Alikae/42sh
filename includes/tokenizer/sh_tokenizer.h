/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_tokenizer.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 16:31:21 by thdelmas          #+#    #+#             */
/*   Updated: 2019/05/19 15:28:05 by thdelmas         ###   ########.fr       */
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
int		sh_isquoted(const char *str, int index);

#endif
