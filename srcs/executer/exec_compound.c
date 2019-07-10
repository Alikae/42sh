#include "t_token.h"
#include "sh.h"

int		exec_compound_for(t_sh *p, t_token *tok)
{
	t_token	*ins;

	dprintf(p->debug_fd, "treating FOR\n");
	ins = tok->sub->sub;
	while (ins)
	{
		if (ins->type == SH_WORD)
		{
			//assign var $tok->sub->content to ins->content
			p->last_cmd_result = exec_script(p, tok->sub->sub->sub, 0);
			//unassign
		}
		ins = ins->next;
	}
	return (p->last_cmd_result);
}

int     exec_compound_while(t_sh *p, t_token *tok, t_toktype type)
{
	int ret;
	int tmp;

	dprintf(p->debug_fd, "treating WHILE\n");
	ret = 0;
	while (((tmp = exec_script(p, tok->sub->sub, 0)) && type == SH_UNTIL) || (!tmp && type == SH_WHILE))
	{
		dprintf(p->debug_fd, "WHILE condition true\n");
		ret = exec_script(p, tok->sub->next, 0);
	}
	dprintf(p->debug_fd, "WHILE condition false\n");
	return (ret);
}

int     exec_compound_if(t_sh *p, t_token *tok)
{
	dprintf(p->debug_fd, "treating IF\n");
	if (!exec_script(p, tok->sub->sub, 0))
	{
		dprintf(p->debug_fd, "IF true\n");
		return (p->last_cmd_result = exec_script(p, tok->sub->next->sub, 0));
	}
	dprintf(p->debug_fd, "IF false\n");
	if (tok->sub->next->next)
		return (p->last_cmd_result = exec_script(p, tok->sub->next->next, 0));
	return (0);
}
