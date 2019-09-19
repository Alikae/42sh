/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_subsh_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 04:11:29 by tcillard          #+#    #+#             */
/*   Updated: 2019/09/19 12:09:05 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_word_expansion.h"
#include <stdio.h>

#define P(x) (printf(x))


void	sh_str_start_end(char **dest, char *src, int i, int n)
{
	int		j;

	j = 0;
	printf("i == %i\nn == %i\n", i, n);
	while (i < n)
	{
		if (src[i])
			(*dest)[j++] = src[i++];
	}
	(*dest)[j] = '\0';
}

void	sh_subsh_quote(t_exp *exp, short *quote)
{
	if (exp->content[exp->i] == '\'' && *quote != SH_DQUOTE)
	{
		if (!*quote)
			*quote = SH_QUOTE;
		else
			*quote = 0;
	}
	else if (exp->content[exp->i] == '"' && *quote != SH_QUOTE)
	{
		if (!*quote)
			*quote = SH_DQUOTE;
		else
			*quote = 0;
	}
}

int		sh_commande_string_size(t_exp *exp, char c)
{
	int		size;
	short	quote;

	size = exp->i;
	quote = 0;
	exp->i++;
	while ((exp->content[exp->i] != c || quote) && exp->content[exp->i])
	{
		printf("%c\n", exp->content[exp->i]);
		sh_subsh_quote(exp, &quote);
		if (!quote && exp->content[exp->i] == '(')
			sh_commande_string_size(exp,')');
		exp->i++;
	}
	return (exp->i - size);
}

void	sh_record_commande_string(t_exp *exp)
{
	int		size;

	if (exp->content[exp->i] == '(')
		size = sh_commande_string_size(exp, ')');
	else
		size = sh_commande_string_size(exp, '`');
	printf("%i\n", size);
	exp->i = exp->i - size + 1;
	if (!(exp->name = (char*)malloc(size + 1)))
		exit (-1);
	sh_str_start_end(&(exp->name), exp->content, exp->i, exp->i + size - 1);
	printf("name == %s\n", exp->name);
}

void	sh_read_pipe(t_exp *exp, int fd)
{
	int ret;
	char buff[500];
	(void)exp;
	ret = 0;

	printf("oui\n");
	while ((ret = read(fd, &buff, 499)) > 0)
	{
		buff[ret] = '\0';
		printf("reading from pipe: %s\n", buff);
	}
}
void	sh_subsh_expansion(t_exp *exp)
{
	t_token	*tok;
	int		pipe_fd[2];

	tok = NULL;
	if (pipe(pipe_fd) == -1)
		exit(-1);
	sh_record_commande_string(exp);
	tok = create_token(SH_SUBSH, 0, NULL);
	if ((tok->sub = tokenize_input(exp->name)))
	{
		printf("fijwlfl\n");
		push_redirect_lst(&(sh()->redirect_lst), 1, pipe_fd[1]);
		exec_compound_subsh(sh(), tok);
		del_n_redirect_lst(&(sh()->redirect_lst), 1);
		sh_read_pipe(exp, pipe_fd[0]);
	}
	else//error
	{}
	close(pipe_fd[1]);
}
