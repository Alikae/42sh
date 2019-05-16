int		is_in_iarray(int i, const int *array)
{
	int	n;

	n = -1;
	while (array[++n])
		if (array[n] == type)
			return (1);
	return (0);
}

t_token	*find_token_by_key_until(t_token *lst, t_token *lst_end, int *type, int *types)
{
	if (type)
		*type = 0;
	while (lst)
	{
		if (lst == lst_end)
			return (lst);
		if (is_in_iarray(lst->type, types))
		{
			if (type)
				*type = lst->type;
			return (lst);
		}
		lst = lst->next;
	}
	return (0);
}

int		exec_pipeline(t_sh *p, t_token *token_begin, t_token *token_end)
{
	int		bang;
	t_token	*next_separator;

	bang = 0;
	if (token_begin->type == SH_BANG)
	{
		bang = 1;
		token_begin = token_begin->next;
	}
	while (token_begin)
	{
		next_separator = find_token_by_key(token_begin, next_separator, 0, [SH_OR, 0]);
		//OPEN PIPE AND USE IT HERE
		p->last_cmd_result = exec_command(p, token_begin, token_end);
	}
}

int		exec_and_or(t_sh *p, t_token *token_begin, t_token *token_end)
{
	t_token	*next_separator;
	int		previous_separator;

	previous_separator = 0;
	while (token_begin)
	{
		next_separator = find_token_by_key_until(token_begin, token_end, &p->type, [SH_AND_IF, SH_OR_IF, 0]);
		if (!previous_separator || (previous_separator == SH_AND_IF && !p->last_cmd_result) || (previous_separator == SH_OR_IF && p->last_cmd_result))
			p->last_cmd_result = exec_pipeline(p, token_begin, next_separator);
		previous_separator = p->type;
		token_begin = (next_separator) ? next_separator->next : 0;
	}
	return (p->last_cmd_result);
}

void	exec_in_background(t_token *token_begin, t_token *token_end)
{
	int	child_pid;
	//fork stuff
	
	if ((child_pid = (int)fork()) < 0)
	{
		//exit properly;
	}
	if (!child_pid)
		return ;
	exec_and_or(p, token_begin, token_end);
	//exit properly
}

int		exec_script(t_sh *p, t_token *token_lst)
{
	t_token	*next_separator;

	while (token_lst) //Will not conflict if token encapsulation is good
	{
		next_separator = find_token_by_key_until(token_lst, 0, &p->type, [SH_AND, SH_SEMI, 0]);
		if (p->type == SH_AND)
			exec_in_background(token_lst, next_separator);
		else
			p->last_cmd_result = exec_and_or(p, token_lst, next_separator);
		token_lst = (next_separator) ? next_separator->next : 0;
	}
	return (p->last_cmd_result);
}



/*
script:
	  |------------------------------------
	  v						   	      	  |
		*\n - and_or 	-o "&;" *\n 	>-|
and_or:
	  |------------------------------------
	  v							 		  |
		pipeline 		-o "&&||" *\n 	>-|
pipeline:
	  |------------------------------------
	  v								 	  |
   *!		 command  	-o "|" *\n 		>-|
command:
	simple:
	function:
	compound:
*/
