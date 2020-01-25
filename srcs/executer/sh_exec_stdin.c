/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exec_stdin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 13:56:39 by thdelmas          #+#    #+#             */
/*   Updated: 2020/01/25 17:03:45 by thdelmas         ###   ########.fr       */
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
	ret = ft_strconv_w(ret);
	sh_init_cmd(ret);
	if (ret && *ret && (sh()->ast = tokenize_input(ret)))
	{
		ft_memdel((void**)&ret);
		exec_script(sh(), sh()->ast);
		free_ast(sh()->ast);
	}
	else
		sh_dprintf(2, "Tokenize Error\n");
	ft_memdel((void**)&ret);
	return (0);
}
