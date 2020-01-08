/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_subsh_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 04:11:29 by tcillard          #+#    #+#             */
/*   Updated: 2020/01/06 20:22:54 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_word_expansion.h"
#include "sh_tokenizer.h"
#include "sh_redirections.h"
#include <stdio.h>
#include "sh_tokens.h"

void	sh_str_start_end(char **dest, char *src, int i, int n)
{
	int		j;

	j = 0;
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
		sh_subsh_quote(exp, &quote);
		if (!quote && exp->content[exp->i] == '(')
			sh_commande_string_size(exp, ')');
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
	exp->i = exp->i - size + 1;
	if (!(exp->name = (char*)malloc(size + 1)))
		exit(-1);
	sh_str_start_end(&(exp->name), exp->content, exp->i, exp->i + size - 1);
}

void	ft_subshcpy(char *buff, char **str, int i)
{
	int		j;

	j = 0;
	while (buff[j])
		(*str)[i++] = buff[j++];
	(*str)[i] = '\0';
}

void	sh_subshdup(char *buff, t_exp *exp)
{
	char	*cpy;
	int		i;

	i = 0;
	cpy = exp->value;
	if (!(exp->value))
	{
		if (!(exp->value = malloc(ft_strlen(buff) + 1)))
			exit(-1);
	}
	else
	{
		if (!(exp->value = malloc(ft_strlen(cpy) + ft_strlen(buff) + 1)))
			exit(-1);
		while (cpy[i])
		{
			exp->value[i] = cpy[i];
			i++;
		}
		ft_memdel((void**)&cpy);
	}
	ft_subshcpy(buff, &(exp->value), i);
}

void	sh_read_pipe(t_exp *exp, int fd)
{
	int		ret;
	char	buff[500];

	ret = 0;
	while ((ret = read(fd, &buff, 499)) > 0)
	{
		buff[ret] = '\0';
		sh_subshdup(buff, exp);
	}
}

void	sh_subsh_expansion(t_exp *exp)
{
	t_token	*tok;
	int		pipe_fd[2];

	sh_record_commande_string(exp);
	tok = create_token(SH_SUBSH, 0, NULL);
	if ((tok->sub = tokenize_input(exp->name)))
	{
		print_all_tokens(sh(), tok, 0);
		if (pipe(pipe_fd) == -1)
			exit(-1);
		push_redirect_lst(&(sh()->redirect_lst), 1, pipe_fd[1]);
		exec_compound_subsh(sh(), tok);
		del_n_redirect_lst(&(sh()->redirect_lst), 1);
		sh_read_pipe(exp, pipe_fd[0]);
		close(pipe_fd[0]);
	}
	else
		sh()->abort_cmd = 1;
}
