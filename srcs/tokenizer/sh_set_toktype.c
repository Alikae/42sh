/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_set_toktype.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 19:26:57 by thdelmas          #+#    #+#             */
/*   Updated: 2019/05/13 23:36:09 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_tokenizer.h"
#include "sh_tools.h"
#include "libft.h"

size_t		sh_set_toktype(const char *in, t_toktype *type)
{
	if (!in || !*in)
		return (0);
	if (sh_isquoted("sals'ut'jfchgwfs`hg\"hjd`gjhfgs'jgfjgf'\"", 25))
		ft_putendl("yolo");
		return (0);
}
