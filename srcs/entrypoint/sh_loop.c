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

#include "sh.h"
#include "sh_tokenizer.h"
#include "sh_tokens.h"
#include "tmp.h"
#include "libft.h"
#include "sh_executer.h"
#include "sh_entrypoint.h"
#include "sh_command_line.h"
#include "sh_history.h"
#include "sh_env.h"
#include "sh_job_control.h"
#include "sh_builtins.h"
#include "sh_command_edition.h"

static t_hist		*init_history(void)
{
	t_hist	*hist;
	t_env	*tmp;
	int		size;

	hist = malloc(sizeof(t_hist));
	hist->topush = 0;
	hist->index = -1;
	hist->prev = NULL;
	hist->current = NULL;
	hist->path = find_path_dir();
	tmp = sh_getev("HISTSIZE");
	size = tmp ? ft_atoi(tmp->value) : 200;
	hist->size_l = (size > 0 ? size : 0);
	hist = command_history(hist);
	tmp = NULL;
	return (hist);
}

static int			sh_in_loop(char **input, t_sh *p, char **ln_buff)
{
	fflush(0);
	if (!(*ln_buff = sh_arguments(p->hist)))
		return (1);
	if (*input)
		*input = ft_strjoin_free(*input, "\n", *input);
	*input = ft_strjoin_free(*input, *ln_buff, *input);
	*input = ft_strjoin_free(*input, "\n", *input);
	ft_memdel((void**)ln_buff);
	sh_init_cmd(*input);
	if ((p->ast = tokenize_input(*input)))
	{
		p->abort_cmd = 0;
		if (!p->unfinished_cmd)
			exec_script(p, p->ast);
	}
	(*input)[ft_strlen(*input) - 1] = 0;
	free_ast(p->ast);
	p->ast = 0;
	if (p->invalid_cmd)
		return (1);
	return (0);
}

static void			sh_loop_init_cmd(char **ln_buff, char **input,
		int *complete)
{
	sh_prompt();
	*ln_buff = NULL;
	*complete = 0;
	*input = 0;
	sh()->print_syntax_errors = 1;
}

int					sh_loop(void)
{
	char	*ln_buff;
	t_sh	*p;
	char	*input;
	int		complete;

	p = sh();
	sh_parse_rc();
	p->hist = init_history();
	while (!p->exit)
	{
		sh_loop_init_cmd(&ln_buff, &input, &complete);
		sh()->unfinished_cmd = 0;
		while (!complete)
		{
			if (sh_in_loop(&input, p, &ln_buff))
				break ;
			if (!p->unfinished_cmd)
				complete = 1;
			else
				ft_putstr("$->");
		}
		ft_memdel((void**)&input);
		check_jobs_status(p);
	}
	return (1);
}
