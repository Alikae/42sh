/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_script.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 20:10:22 by thdelmas          #+#    #+#             */
/*   Updated: 2019/11/01 19:16:40 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_entrypoint.h"
#include "libft.h"
#include "sh_tokenizer.h"
#include <fcntl.h>
#include <stdlib.h>
#define BUFF_SIZE 4096

#include <stdio.h>

int     exec_script(t_sh *p, t_token *token_begin, t_token *token_end);

int		sh_script(const char *path)
{
	t_sh *p;
	char	*buff;
	char	*input;
	int		fd;

	p = sh();
	input = NULL;
	if (!(buff = ft_strnew(BUFF_SIZE)))
		return (-1);
	if ((fd = open(path, O_RDONLY)) < 0)
		return (fd);
	if (read(fd, buff, 0) != 0)
		return (-1);
	while (read(fd, buff, 4096) > 0)
	{
		if (input)
			input = ft_strjoin_free(input, buff, input);
		else
			if (!(input = ft_strdup(buff)))
				return (0);
		ft_strclr(buff);
	}
	close(fd);
	sh_init_cmd(input);
	//doesnt throw error omn script "WHILE"
	if (input && *input && (p->ast = tokenize_input(input)))//line
	{
		//HANDLE SYNTAX ERROR
	//	print_all_tokens(p, p->ast, 0);
		p->abort_cmd = 0;
		exec_script(p, p->ast, 0);
	}
	return (1);
}

int		sh_exec_file()
{
	t_sh	*p;
	int		i;

	p = sh();
	i = 0;
	while (i < p->ac)
		sh_script(p->av[i++]);
	return (1);
}
