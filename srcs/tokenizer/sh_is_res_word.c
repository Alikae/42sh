/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_is_res_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 14:54:57 by thdelmas          #+#    #+#             */
/*   Updated: 2019/05/20 16:49:54 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_tokens.h"
#include "libft.h"

t_toktype	sh_is_res_word(const char *str, size_t index)
{
	char *word;
	t_toktype type;

	type = SH_EOS;
	word = ft_strndup(str, index + 1);
	word = ft_strjoin_free(word, "*", word);
	type = sh_get_res(word);
	ft_strdel(&word);
	return (type);
}
