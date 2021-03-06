/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/02/07 21:45:52 by tmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_entrypoint.h"
#include "libft.h"
#include "sh_tokenizer.h"
#include "sh_executer.h"
#include <fcntl.h>
#include <stdlib.h>

static void		clean_input(char **str)
{
	int i;

	i = 0;
	if (!str || !*str)
		return ;
	while (str[0][i])
	{
		if ((str[0][i] < 32 || str[0][i] == 127) && str[0][i] != '\n')
			str[0][i] = 32;
		i++;
	}
}

int				read_script(char **buff, int *fd, const char *path)
{
	if (!(*buff = ft_strnew(4096)))
		return (-1);
	if ((*fd = open(path, O_RDONLY)) < 0)
	{
		sh_dprintf(2, "42sh: cant open %s\n", path);
		ft_memdel((void**)buff);
		return (-1);
	}
	if (read(*fd, *buff, 0) != 0)
	{
		ft_memdel((void**)buff);
		sh_dprintf(2, "42sh: cant read %s\n", path);
		return (-1);
	}
	return (*fd);
}

int				read_script_2(int fd, char **input, char **buff)
{
	while (read(fd, *buff, 4096) > 0)
	{
		if (*input)
			*input = ft_strjoin_free(*input, *buff, *input);
		else if (!(*input = ft_strdup(*buff)))
			return (0);
		ft_strclr(*buff);
	}
	ft_memdel((void**)buff);
	close(fd);
	return (1);
}

int				sh_script(const char *path)
{
	t_sh	*p;
	char	*buff;
	char	*input;
	int		fd;
	t_token	*ast;

	p = sh();
	input = NULL;
	if ((fd = read_script(&buff, &fd, path)) < 0)
		return (-1);
	if ((fd = read_script_2(fd, &input, &buff)) < 1)
		return (fd);
	input = ft_strconv_w(input);
	clean_input(&input);
	sh_init_cmd(input);
	if (p->input && *p->input && (ast = tokenize_input(p->input)))
	{
		ft_memdel((void**)&p->input);
		exec_script(p, ast);
		free_ast(ast);
	}
	else if (p->input && *p->input)
		sh_dprintf(2, "Tokenize Error-\n");
	ft_memdel((void**)&p->input);
	return (1);
}

int				sh_exec_file(void)
{
	t_sh	*p;
	int		i;

	p = sh();
	i = 1;
	while (i < p->ac)
		sh_script(p->av[i++]);
	return (1);
}
