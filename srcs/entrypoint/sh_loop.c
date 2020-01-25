/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 17:32:52 by thdelmas          #+#    #+#             */
/*   Updated: 2020/01/25 03:02:23 by ede-ram          ###   ########.fr       */
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
#include "sh_command_edition.h"

static t_hist	*init_history(void)
{
	t_hist	*hist;
	t_env	*tmp;

	hist = malloc(sizeof(t_hist));
	hist->current = NULL;
	hist->path = find_path_dir();
	tmp = sh_getev("HISTSIZE");
	hist->size_l = (!tmp ? 200 : ft_atoi(tmp->value));
	hist = command_history(hist);
	tmp = NULL;
	return (hist);
}

int				sh_in_loop(char **input, t_sh *p, char **ln_buff)
{
	sh_tty_cbreak(1, sh()->orig_termios);
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

void			sh_loop_init_cmd(char **ln_buff, char **input, int *complete)
{
	sh_prompt();
	*ln_buff = NULL;
	*complete = 0;
	*input = 0;
	sh()->print_syntax_errors = 1;
}

int				sh_loop(void)
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
