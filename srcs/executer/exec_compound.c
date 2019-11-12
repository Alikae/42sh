/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_compound.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 05:02:36 by ede-ram           #+#    #+#             */
/*   Updated: 2019/11/13 00:16:17 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_tokenizer.h"
#include "sh.h"
#include "sh_env.h"
#include "sh_executer.h"
#include "sh_word_expansion.h"
#include "sh_exitpoint.h"
#include <stdio.h>

//FOR
//NAME
//WORDLIST?
//DO

int		exec_compound_subsh(t_sh *p, t_token *tok)
{
	int	pid;
	//Not more?
	//printf("[%i]exec_compound_subsh\n", getpid());
	if ((pid = fork_process(p, 1)) < 0)
	{
		printf("fork error\n");
		return (1/*fork_error*/);
	}
	if (!pid)
	{
		exec_script(p, tok->sub);
		exit(1);
	}
	//close all pipes?
	sh_pipe_lst_del(&p->pipe_lst);
	//
	return (block_wait(p, pid, 0));
}

int		exec_compound_case(t_sh *p, t_token *tok)
{
	t_token	*case_elem;
	t_token	*word;

	dprintf(p->dbg_fd, "treating CASE\n");
	case_elem = tok->sub;
	while (case_elem && !p->abort_cmd)
	{
		word = case_elem->sub;
		while (word)
		{
			//not strcmp : matchnmatch
			if (!ft_strcmp(tok->content, word->content))
				return (exec_script(p, tok->sub->sub->sub));
			word = word->next;
		}
		case_elem = case_elem->next;
	}
	return (0);
}

int		exec_compound_for(t_sh *p, t_token *tok)
{
	t_token		*ins;
	t_token *tmp_tok;

	dprintf(p->dbg_fd, "treating FOR\n");
	//printf("%s\n", tok->sub->content);
	tmp_tok = sh_expansion(tok->sub->content, &p->params, 1);
	if (!tmp_tok)//Does thotho can retrn null?
	{
		//
		printf("exp error\n");
		exit(1);
	}
	ins = tok->sub->sub;
	while (ins && !p->abort_cmd)
	{
		if (ins->type == SH_WORD)
		{
			sh_setev(tok->sub->content, ins->content);
			//printf("%s\n", tok->sub->sub->sub->content);
			p->last_cmd_result = exec_script(p, tok->sub->sub->sub);
		}
		ins = ins->next;
	}
	return (p->last_cmd_result);
}

int     exec_compound_while(t_sh *p, t_token *tok, t_toktype type)
{
	int ret;
	int tmp;

	dprintf(p->dbg_fd, "treating WHILE\n");
	ret = 0;
	while (!p->abort_cmd && (((tmp = exec_script(p, tok->sub->sub)) && type == SH_UNTIL) || (!tmp && type == SH_WHILE)) && !p->abort_cmd)
	{
		dprintf(p->dbg_fd, "WHILE condition true\n");
		ret = exec_script(p, tok->sub->next);
	}
	dprintf(p->dbg_fd, "WHILE condition false\n");
	return (ret);
}

int     exec_compound_if(t_sh *p, t_token *tok)
{
	dprintf(p->dbg_fd, "treating IF\n");
	if (!exec_script(p, tok->sub->sub) && !p->abort_cmd)
	{
		dprintf(p->dbg_fd, "IF true\n");
		return (p->last_cmd_result = exec_script(p, tok->sub->next->sub));
	}
	dprintf(p->dbg_fd, "IF false\n");
	if (tok->sub->next->next && !p->abort_cmd)
		return (p->last_cmd_result = exec_script(p, tok->sub->next->next));
	//return what?
	return (0);
}
