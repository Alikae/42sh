/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 17:32:52 by thdelmas          #+#    #+#             */
/*   Updated: 2019/12/16 16:33:34 by ede-ram          ###   ########.fr       */
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

void	print_all_tokens(t_sh *p, t_token *ast, int depth);

int	sh_loop_read(int *complete, char **input, t_sh *p, char **ln)
{
	fflush(0);
	if (!(*ln = sh_arguments(sh()->hist)))
		return (0);
	if (*input)
		*input = ft_strjoin_free(*input, "\n", *input);
	*input = ft_strjoin_free(*input, *ln, *input);
	//ft_tab_strdel(&ln_buff); //BECAME STRDEL
	ft_memdel((void**)ln);
	sh_init_cmd(*input);
	if ((p->ast = tokenize_input(*input)))
	{
		print_all_tokens(p, p->ast, 0);
		p->abort_cmd = 0;
		if (!p->unfinished_cmd)
			exec_script(p, p->ast);
	}
	free_ast(p->ast);
	if (p->invalid_cmd)
		return (0);
	if (!p->unfinished_cmd)
		*complete = 1;
	else
		ft_putstr("$->");
	return (1);
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
//		while (!complete && sh_loop_read(&complete, &input, p, &ln_buff))
//			;
		while (!complete)//Can we ctrl-C?
		{
			dbug = 0;
			//swap_signals_to_prompter
			if (!dbug)
			{
				fflush(0);
				if (!(ln_buff = sh_arguments(sh()->hist)))
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
				ln_buff = ft_strdup("LSCOLORS=lala ls -g");
				ln_buff = ft_strdup("cat |");
				ln_buff = ft_strdup("echo (PUSH SUR TA PUTAIN DE BRANCHE)");
				ln_buff = ft_strdup("if ( ls ) ; then echo yo ; fi");
				ln_buff = ft_strdup("!");
				ln_buff = ft_strdup("ls");
				ln_buff = ft_strdup("echo yo lala");
				ln_buff = ft_strdup("\"BONJOURS TOUT LE\"");
				ln_buff = ft_strdup("echo yo");
				ln_buff = ft_strdup("readonly PWD ; cd .. ; pwd");
				ln_buff = ft_strdup("readonly PWD ; pwd");
				ln_buff = ft_strdup("fg");
				ln_buff = ft_strdup("a=b;  a=c;  a=d; a=e");
				ln_buff = ft_strdup("a=b;  e=c;  w=d; q=e");
				ln_buff = ft_strdup("exit");
				ln_buff = ft_strdup(";");
				ln_buff = ft_strdup("echo \\;; ; ls");
				ln_buff = ft_strdup("echo $?");
				ln_buff = ft_strdup("$(ls)");
				ln_buff = ft_strdup("$()");
				ln_buff = ft_strdup("echo $(echo yolglej)");
				ln_buff = ft_strdup("a()\n{ a ; }\na\n");
				ln_buff = ft_strdup("$'\n");
				ln_buff = ft_strdup("a=\"'\"\n");
				ln_buff = ft_strdup("cat <<-lala\necho yolo\nlala\n");
				ln_buff = ft_strdup("fd < lala\n\n\n");
				ln_buff = ft_strdup("cat <lala\n");
				ln_buff = ft_strdup("a");
			}
			//	int z = 0;
			//	while (ln_buff[z])
			//		fprintf(stderr, "[%s]\n", ln_buff[z++]);
			//	if (!*ln_buff || !ft_strncmp("exit", *ln_buff, 4))
			//		break ;
			//	else
			if (input)
				input = ft_strjoin_free(input, "\n", input);
			input = ft_strjoin_free(input, ln_buff, input);
			input = ft_strjoin_free(input, "\n", input);
			//printf("%i - %s -\n", strlen(input), input);
			//ft_tab_strdel(&ln_buff); //BECAME STRDEL
			//printf("-%s-\n", input);
			ft_memdel((void**)&ln_buff);
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
		ft_memdel((void**)&input);
		check_jobs_status(p);
	}
	return (1);
}
