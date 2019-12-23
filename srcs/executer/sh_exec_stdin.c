/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exec_stdin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 13:56:39 by thdelmas          #+#    #+#             */
/*   Updated: 2019/12/23 00:48:33 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_tokens.h"
#include "sh_tokenizer.h"
#include "sh_executer.h"
#include "sh_entrypoint.h"
#include <fcntl.h>

int	sh_exec_stdin(void)
{
	char *buff;
	char *ret;

	ret = NULL;
	buff = ft_strnew(1024);
	while (buff && read(0, buff, 1024) > 0)
	{
		if (!ret)
			ret = ft_strdup(buff);
		else
			ret = ft_strjoin_free(ret, buff, ret);
		ft_bzero(buff, 1024);
	}
	ft_memdel((void**)&buff);
	sh_init_cmd(ret);
	if (ret && *ret && (sh()->ast = tokenize_input(ret)))
	{
		print_all_tokens(sh(), sh()->ast, 0);
		exec_script(sh(), sh()->ast);
	}
	else
		sh_dprintf(2, "Tokenize Error\n");
	ft_memdel((void**)&ret);
	return (0);
}
