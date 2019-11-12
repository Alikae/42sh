/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 17:32:52 by thdelmas          #+#    #+#             */
/*   Updated: 2019/11/12 23:19:24 by ede-ram          ###   ########.fr       */
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

#include <stdio.h> //

void			print_all_tokens(t_sh *p, t_token *t, int lvl)
{
	int lvcpy;

	while (t)
	{
		lvcpy = lvl;
		while (lvcpy--)
		{
			if (!lvcpy && lvl > 1)
				dprintf(2, "‾‾‾‾‾‾");
			dprintf(2, "%c", (lvcpy == 0) ? '|' : ' ');
			dprintf(2, "      ");
		}
		if (t->sub)
		{
			print_all_tokens(p, t->sub, lvl + 1);
		}
		t = t->next;
	}
}

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
	return (hist);
}

int		sh_loop(void)
{
	char	*ln_tab;//RENAME
	t_sh	*p;
	char	*input;
	int	complete;

	p = sh();
	sh_parse_rc();
	sh()->hist = init_history();
	while (!p->exit)
	{
		sh_prompt();
		ln_tab = NULL;
		int dbug = sh()->dbg != NULL;
		//TMP DBG
			dbug = 1;
		//
		complete = 0;
		input = 0;
		p->print_syntax_errors = 1;
		while (!complete)//Can we ctrl-C?
		{
			//swap_signals_to_prompter
			if (1 || !dbug)
			{
				fflush(0);
				if (!(ln_tab = sh_arguments(sh()->hist)))
					break ;
			}
			else
				;
			//	int z = 0;
			//	while (ln_tab[z])
			//		fprintf(stderr, "[%s]\n", ln_tab[z++]);
			//	if (!*ln_tab || !ft_strncmp("exit", *ln_tab, 4))
			//		break ;
			//	else
			if (input)
				input = ft_strjoin_free(input, "\n", input);
			input = ft_strjoin_free(input, ln_tab, input);
			input = ft_strjoin_free(input, "\n", input);
			//printf("%i - %s -\n", strlen(input), input);
			//ft_tab_strdel(&ln_tab); //BECAME STRDEL
			printf("-%s-\n", input);
			free(ln_tab);
			sh_init_cmd(input);
			if ((p->ast = tokenize_input(input)))//line
			{
				//print_all_tokens(p, p->ast, 0);
				p->abort_cmd = 0;
				if (!p->unfinished_cmd)
					exec_script(p, p->ast);
				//printf("Script executed\n");
			}
			//	else
			//		printf("Tokenizer Error\n");
			input[ft_strlen(input) - 1] = 0;
			free_ast(p->ast);
			if (p->invalid_cmd)
				break;
			if (!p->unfinished_cmd)
				complete = 1;
			else
				ft_putstr("$->");//prompt PSX
		}
		//
		free(input);
		check_jobs_status(p);//doesnt detect pkilled
	}
	return (1);
}
