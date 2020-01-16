/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exec_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 14:06:25 by thdelmas          #+#    #+#             */
/*   Updated: 2020/01/14 20:31:37 by jerry            ###   ########.fr       */
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
