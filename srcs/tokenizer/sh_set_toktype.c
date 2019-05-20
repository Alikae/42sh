/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_set_toktype.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 19:26:57 by thdelmas          #+#    #+#             */
/*   Updated: 2019/05/20 16:49:27 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_tokenizer.h"
#include "sh_tools.h"
#include "libft.h"

size_t		sh_set_toktype(const char *in, t_toktype *type)
{
	size_t	i;

	i = 0;
	if (!in || !*in)
		return (0);
	while (sh_is_res_word(in, i) != SH_EOS)
		i++;
	if (i)
		i--;
	*type = sh_is_res_word(in, i);
	return (sh_get_toklen(in, type));
}
