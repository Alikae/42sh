/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 17:32:52 by thdelmas          #+#    #+#             */
/*   Updated: 2020/01/17 00:13:12 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

#include "sh_tokenizer.h"
#include "tmp.h"
#include "libft.h"
#include "sh_executer.h"
#include "sh_entrypoint.h"
#include "sh_command_line.h"
#include "sh_history.h"
#include "sh_env.h"
#include "sh_job_control.h"
#include "sh_builtins.h"

#include <stdio.h> //

static t_hist	*init_history(void)
{
	t_hist *hist;
	t_env *tmp;

	hist = malloc(sizeof(t_hist));
	hist->current = NULL;
	hist->path = find_path_dir();
	tmp = sh_getev("HISTSIZE");
	hist->size_l = (!tmp ? 200 : ft_atoi(tmp->value));
	hist = command_history(hist);
	tmp = NULL;
	return (hist);
}

int		sh_loop(void)
{
	char	*ln_buff;
	t_sh	*p;
	char	*input;
	int		complete;
	int		dbug;

	dbug = sh()->dbg != NULL;
	p = sh();
	sh()->hist = sh_init_history();
	sh_parse_rc();
	sh()->hist = init_history();
	while (!p->exit)
	{
		sh_prompt();
		ln_buff = NULL;
		complete = 0;
		input = 0;
		p->print_syntax_errors = 1;
		while (!complete)//Can we ctrl-C?
		{
			dbug = 0;
			if (!dbug)
			{
				fflush(0);
				if (!(ln_buff = sh_arguments(sh()->hist)))
					break ;
			}
			if (input)
				input = ft_strjoin_free(input, "\n", input);
			input = ft_strjoin_free(input, ln_buff, input);
			input = ft_strjoin_free(input, "\n", input);
			ft_memdel((void**)&ln_buff);
			sh_init_cmd(input);
			if ((p->ast = tokenize_input(input)))
			{
				p->abort_cmd = 0;
				if (!p->unfinished_cmd)
					exec_script(p, p->ast);
			}
			input[ft_strlen(input) - 1] = 0;
			free_ast(p->ast);
			p->ast = 0;
			if (p->invalid_cmd)
				break;
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
