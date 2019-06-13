/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_tokenizer.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 16:31:21 by thdelmas          #+#    #+#             */
/*   Updated: 2019/05/24 15:28:53 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_TOKENIZER
# define SH_TOKENIZER

# include "sh_tokens.h"
# include <stdlib.h>

void	sh_print_onetok(t_token *tok);
void	sh_print_alltok(t_token *tok);
char	*sh_get_tok_content(const char *input);
int		sh_isquoted(const char *str, int index);

#endif
