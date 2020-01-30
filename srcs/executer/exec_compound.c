/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/01/29 01:25:46 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_tokenizer.h"
#include "sh.h"
#include "sh_env.h"
#include "sh_executer.h"
#include "sh_word_expansion.h"
#include "sh_exitpoint.h"

int		exec_compound_subsh(t_sh *p, t_token *tok)
{
	int	pid;

	if ((pid = fork_process(p, 1)) < 0)
	{
		sh_dprintf(1, "fork error\n");
		destructor(43);
	}
	if (!pid)
	{
		exec_script(p, tok->sub);
		destructor(p->last_cmd_result);
	}
	delete_close_all_pipe_lst(p->pipe_lst);
	p->pipe_lst = 0;
	return (block_wait(p, pid, 0));
}

int		exec_compound_case(t_sh *p, t_token *tok)
{
	t_token	*case_elem;
	t_token	*word;

	case_elem = tok->sub;
	while (case_elem && !p->abort_cmd)
	{
		word = case_elem->sub;
		while (word)
		{
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
	t_token	*ins;
	t_token *tmp_tok;

	tmp_tok = sh_expansion(tok->sub->content, &p->params, 1);
	if (!tmp_tok)
	{
		sh_dprintf(1, "expansion error\n");
		destructor(1);
	}
	ins = tok->sub->sub;
	while (ins && !p->abort_cmd)
	{
		if (ins->type == SH_WORD)
		{
			sh_setev(tok->sub->content, ins->content);
			p->last_cmd_result = exec_script(p, tok->sub->sub->sub);
		}
		ins = ins->next;
	}
	return (p->last_cmd_result);
}

int		exec_compound_while(t_sh *p, t_token *tok, t_toktype type)
{
	int ret;
	int tmp;

	ret = 0;
	while (!p->abort_cmd && (((tmp = exec_script(p, tok->sub->sub))
					&& type == SH_UNTIL) || (!tmp && type == SH_WHILE))
			&& !p->abort_cmd)
	{
		ret = exec_script(p, tok->sub->next);
	}
	return (ret);
}

int		exec_compound_if(t_sh *p, t_token *tok)
{
	if (!exec_script(p, tok->sub->sub) && !p->abort_cmd)
		return (p->last_cmd_result = exec_script(p, tok->sub->next->sub));
	if (tok->sub->next->next && !p->abort_cmd)
		return (p->last_cmd_result = exec_script(p, tok->sub->next->next));
	return (0);
}
