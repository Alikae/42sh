/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_set_toktype.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 19:26:57 by thdelmas          #+#    #+#             */
/*   Updated: 2019/05/11 20:47:58 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_tokenizer.h"

size_t		sh_set_toktype(const char *in, t_toktype *type)
{
	if ((!in || !*in) && (*type = SH_EOS) == SH_EOS)
		return (0);
return (SH_EOS);	
}
