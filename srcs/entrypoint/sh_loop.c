/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 17:32:52 by thdelmas          #+#    #+#             */
/*   Updated: 2019/10/01 06:09:02 by ede-ram          ###   ########.fr       */
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

#include <stdio.h>

void			print_all_tokens(t_sh *p, t_token *t, int lvl)
{
	int lvcpy;

	while (t)
	{
		lvcpy = lvl;
		while (lvcpy--)
		{
			if (!lvcpy && lvl > 1)
				if (!ft_strcmp(p->dbg, __func__) || !ft_strcmp(p->dbg, "all"))
					dprintf(p->dbg_fd, "‾‾‾‾‾‾");
			if (!ft_strcmp(p->dbg, __func__) || !ft_strcmp(p->dbg, "all"))
				dprintf(p->dbg_fd, "%c", (lvcpy == 0) ? '|' : ' ');
			if (lvcpy < lvl - 1 || lvl == 1)
				dprintf(p->dbg_fd, "      ");
		}
		if (!ft_strcmp(p->dbg, __func__) || !ft_strcmp(p->dbg, "all"))
			dprintf(p->dbg_fd, "[%15s] (%i)-%i\n", (t->content) ? t->content : "o", t->type, t->index);
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

	hist = malloc(sizeof(t_hist));
	hist->path = find_path();
	hist->size_l = 200;
	hist = command_history(hist);
	return (hist);
}

int		sh_loop(void)
{
	char	*ln_tab;//RENAME
	t_hist	*hist;
	t_sh	*p;
	char	*input;
	int	complete;

	p = sh();
	hist = init_history();
	sh_parse_rc();
	while (!p->exit)
	{
		sh_prompt();
		ln_tab = NULL;
		int dbug = sh()->dbg != NULL;
		complete = 0;
		input = 0;
		p->print_syntax_errors = 1;
		while (!complete)
		{
			//swap_signals_to_prompter
			if (1 || /**/!dbug)
			{
				fflush(0);
				if (!(ln_tab = sh_arguments(hist)))
					break ;
			}
			else
			{
				//		ln_tab = malloc(2 * sizeof(char*));
				//	ln_tab[0] = ft_strdup("/bin/echo lala && /bin/ls -la && CTA 3");
				//	ln_tab[0] = ft_strdup("yolo () { echo lala ; }");
				//	ln_tab[0] = ft_strdup("/bin/cat tet");
				//	ln_tab[0] = ft_strdup("for lala in po la ka nu ; do /bin/echo $lala ; done");
				//	ln_tab[0] = ft_strdup("case yolo in yola ) echo ;; yali | yolo ) loul;;(po )tu ;esac");
				//	ln_tab[0] = ft_strdup("case yoz in ( lap | yoz ) /bin/echo yes ;esac");
				//	ln_tab[0] = ft_strdup("  echo ; done");
				//		ln_tab[0] = ft_strdup("case yolo in yola ) echo ;; yali | yolo ) loul;;(po )tu ; esac");
				//	ln_tab = ft_strdup("case yolo in yola ) echo ;; yali | yolo ) loul;;(po )tu ;esac");
				ln_tab = ft_strdup("LSCOLORS=lala ls -g");
				ln_tab = ft_strdup("cat |");
				ln_tab = ft_strdup("echo (PUSH SUR TA PUTAIN DE BRANCHE)");
				ln_tab = ft_strdup("if ( ls ) ; then echo yo ; fi");
				ln_tab = ft_strdup("!");
				ln_tab = ft_strdup("ls");
				ln_tab = ft_strdup("echo yo lala");
				ln_tab = ft_strdup("\"BONJOURS TOUT LE\"");
				ln_tab = ft_strdup("echo yo");
				ln_tab = ft_strdup("readonly PWD ; cd .. ; pwd");
				ln_tab = ft_strdup("readonly PWD ; pwd");
				ln_tab = ft_strdup("fg");
				ln_tab = ft_strdup("a=b;  a=c;  a=d; a=e");
				ln_tab = ft_strdup("a=b;  e=c;  w=d; q=e");
				ln_tab = ft_strdup("exit");
				ln_tab = ft_strdup(";");
				ln_tab = ft_strdup("echo \\;; ; ls");
				ln_tab = ft_strdup("echo $?");
				ln_tab = ft_strdup("$(ls)");
				ln_tab = ft_strdup("$()");
				ln_tab = ft_strdup("echo $(echo yolglej)");
				//ET UTILISE L'OPTION DEBUG
			}
			//	int z = 0;
			//	while (ln_tab[z])
			//		fprintf(stderr, "[%s]\n", ln_tab[z++]);
			//	if (!*ln_tab || !ft_strncmp("exit", *ln_tab, 4))
			//		break ;
			//	else
			if (input)
				input = ft_strjoin_free(input, "\n", input);
			input = ft_strjoin_free(input, ln_tab, input);
			//printf("%i - %s -\n", strlen(input), input);
			//ft_tab_strdel(&ln_tab); //BECAME STRDEL
			free(ln_tab);
			sh_init_cmd(input);
			if ((p->ast = tokenize_input(input)))//line
			{
				print_all_tokens(p, p->ast, 0);
				p->abort_cmd = 0;
				if (!p->unfinished_cmd)
					exec_script(p, p->ast, 0);
				//printf("Script executed\n");
			}
			//	else
			//		printf("Tokenizer Error\n");
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
		check_jobs_status(p);
	}
	push_history(hist);
	return (1);
}
