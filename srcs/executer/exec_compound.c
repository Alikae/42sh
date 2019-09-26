/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_compound.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 23:16:12 by thdelmas          #+#    #+#             */
/*   Updated: 2019/09/21 01:51:26 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_tokenizer.h"
#include "sh.h"
#include "sh_env.h"
#include "sh_executer.h"
#include <stdio.h>

//FOR
//NAME
//WORDLIST?
//DO

int		exec_compound_subsh(t_sh *p, t_token *tok)
{
	int	pid;
	//Not more?
	printf("[%i]exec_compound_subsh\n", getpid());
	if ((pid = fork_process(p, 0)) < 0)
	{
		printf("fork error\n");
		return (1/*fork_error*/);
	}
	if (!pid)
		exit(exec_script(p, tok->sub, 0));
	return (block_wait(p, pid));
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
			if (!ft_strcmp(tok->content, word->content))
				return (exec_script(p, tok->sub->sub->sub, 0));
			word = word->next;
		}
		case_elem = case_elem->next;
	}
	return (0);
}

int		exec_compound_for(t_sh *p, t_token *tok)
{
	t_token		*ins;
	char	*tmp;
	const char	*value;

	dprintf(p->dbg_fd, "treating FOR\n");
	ins = tok->sub->sub;
	tmp = 0;
	if ((value = sh_getev_value(tok->sub->content)))
		tmp = ft_strdup(value);
	while (ins && !p->abort_cmd)
	{
		if (ins->type == SH_WORD)
		{
			sh_setev(tok->sub->content, ins->content);
			printf("%s\n", tok->sub->sub->sub->content);
			p->last_cmd_result = exec_script(p, tok->sub->sub->sub, 0);
		}
		ins = ins->next;
	}
	sh_unsetev(tok->sub->content, &(sh()->params));
	if (tmp)
		sh_setev(tok->sub->content, tmp);
	free(tmp);
	return (p->last_cmd_result);
}

int     exec_compound_while(t_sh *p, t_token *tok, t_toktype type)
{
	int ret;
	int tmp;

	dprintf(p->dbg_fd, "treating WHILE\n");
	ret = 0;
	while (!p->abort_cmd && (((tmp = exec_script(p, tok->sub->sub, 0)) && type == SH_UNTIL) || (!tmp && type == SH_WHILE)) && !p->abort_cmd)
	{
		dprintf(p->dbg_fd, "WHILE condition true\n");
		ret = exec_script(p, tok->sub->next, 0);
	}
	dprintf(p->dbg_fd, "WHILE condition false\n");
	return (ret);
}

int     exec_compound_if(t_sh *p, t_token *tok)
{
	dprintf(p->dbg_fd, "treating IF\n");
	if (!exec_script(p, tok->sub->sub, 0) && !p->abort_cmd)
	{
		dprintf(p->dbg_fd, "IF true\n");
		return (p->last_cmd_result = exec_script(p, tok->sub->next->sub, 0));
	}
	dprintf(p->dbg_fd, "IF false\n");
	if (tok->sub->next->next && !p->abort_cmd)
		return (p->last_cmd_result = exec_script(p, tok->sub->next->next, 0));
	return (0);
}
