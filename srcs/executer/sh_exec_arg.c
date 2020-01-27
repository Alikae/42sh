/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/01/27 13:17:09 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_entrypoint.h"
#include "sh_executer.h"
#include "sh_tokens.h"
#include "sh_tokenizer.h"
#include "stdlib.h"
#include <fcntl.h>

int	sh_exec_arg(void)
{
	t_opt	*opt;
	char	*ret;

	ret = NULL;
	opt = ft_fetch_opt("c", 1, sh()->opt);
	if (opt && opt->value)
		ret = opt->value;
	sh_init_cmd(ret);
	if (ret && *ret && (sh()->ast = tokenize_input(ret)))
		exec_script(sh(), sh()->ast);
	return (0);
}
