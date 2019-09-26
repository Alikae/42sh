/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exec_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 14:06:25 by thdelmas          #+#    #+#             */
/*   Updated: 2019/09/22 00:06:37 by thdelmas         ###   ########.fr       */
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
	if (opt && opt->arg)
		ret = opt->arg;
	sh_init_cmd(ret);
	if (ret && *ret && (sh()->ast = tokenize_input(ret)))//line
	{
		print_all_tokens(sh(), sh()->ast, 0);
		exec_script(sh(), sh()->ast, 0);
	}
	return (0);
}
