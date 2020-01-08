/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_script.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 20:10:22 by thdelmas          #+#    #+#             */
/*   Updated: 2020/01/07 02:33:56 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_entrypoint.h"
#include "libft.h"
#include "sh_tokenizer.h"
#include "sh_executer.h"
#include <fcntl.h>
#include <stdlib.h>
#define BUFF_SIZE 4096

#include <stdio.h>

int		sh_script(const char *path)
{
	t_sh	*p;
	char	*buff;
	char	*input;
	int		fd;
	t_token	*ast;

	p = sh();
	input = NULL;
	if (!(buff = ft_strnew(BUFF_SIZE)))
		return (-1);
	if ((fd = open(path, O_RDONLY)) < 0)
	{
		sh_dprintf(2, "42sh: cant open %s\n", path);
		ft_memdel((void**)&buff);
		return (fd);
	}
	if (read(fd, buff, 0) != 0)
	{
		ft_memdel((void**)&buff);
		sh_dprintf(2, "42sh: cant read %s\n", path);
		return (-1);
	}
	while (read(fd, buff, 4096) > 0)
	{
		if (input)
			input = ft_strjoin_free(input, buff, input);
		else if (!(input = ft_strdup(buff)))
			return (0);
		ft_strclr(buff);
	}
	ft_memdel((void**)&buff);
	close(fd);
	input = ft_strconv_w(input);
	sh_init_cmd(input);
	//doesnt throw good error on script "WHILE"
	if (input && *input && (ast = tokenize_input(input)))
	{
		//HANDLE SYNTAX ERROR
	//	print_all_tokens(p, ast, 0);
		p->abort_cmd = 0;
		ft_memdel((void**)&input);
		exec_script(p, ast);
	}
	else if (input && *input)
		sh_dprintf(2, "Tokenize Error-\n");
	ft_memdel((void**)&input);
	return (1);
}

int		sh_exec_file(void)
{
	t_sh	*p;
	int		i;

	p = sh();
	i = 1;
	while (i < p->ac)
		sh_script(p->av[i++]);
	return (1);
}
