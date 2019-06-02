#include "includes/general_env/sh_general_env.h"
#include "includes/tokenizer/sh_tokens.h"
#include <sys/stat.h>
#include <unistd.h>
typedef struct	s_sh
{
	int			last_cmd_result;
	int			type;
	t_toktype	script_separators[2];
	t_toktype	and_or_separators[2];
	t_toktype	pipeline_separators[2];
}				t_sh;

int		exec_script(t_sh *p, t_token *token_begin, t_token *token_end, t_general_env *gen_env);

/*int		is_in_iarray(int i, const int *array)
{
	int	n;

	n = -1;
	while (array[++n])
		if (i == array[n])
			return (1);
	return (0);
}*/

t_general_env	*extract_child_env(t_general_env *parent_env, t_token *token_begin, t_token *token_end)
{

}

t_token	*find_token_by_key_until(t_token *lst, t_token *lst_end, int *type, t_toktype (*types)[2])
{
	if (type)
		*type = 0;
	while (lst)
	{
		if (lst == lst_end)
		{
			if (type)
				*type = lst->type;
			return (lst);
		}
		if (lst->type == (*types)[0] || lst->type == (*types)[1])
		{
			if (type)
				*type = lst->type;
			return (lst);
		}
		lst = lst->next;
	}
	return (0);
}

int		block_wait()
{
	wait(0);
	printf("Wait finish\n");
	return (0);
}

int		exec_path(t_sh *p, char *path, t_general_env *prgm_env)
{
	int	ret;

	//fork stuff
	int child_pid = fork();
	if (child_pid)
		ret = block_wait();
	else
		execve(path, prgm_env->argv, 0/*prgm_env->env is a struct*/);
	//wait in parent
	//dup2() for handle redirections
	//execve in child
	return (ret); //<-- Return What?
}

int		can_exec(struct stat *st)
{
	if (!S_ISREG(st->st_mode))
		return (0);
	else if (st->st_uid == getuid() && st->st_mode & S_IXUSR)
		return (1);
	else if (st->st_gid == getgid() && st->st_mode & S_IXGRP)
		return (1);
	else if (st->st_mode & S_IXOTH)
		return (1);
	return (0);
}

int		tablen(char **tab)
{
	int i = -1;
	if (!tab)
		return (0);
	while (tab[++i])
		;
	return (i);
}

void	push_str_to_tab(char ***ptab, char *s)
{
	int len = tablen(*ptab);
	char **old = *ptab;
	*ptab = realloc(*ptab, len + 2);
	(*ptab)[len] = strdup(s);
	(*ptab)[len + 1] = 0;
}

t_general_env	*construct_child_env(t_sh *p, t_token *token_begin, t_token *token_end, t_general_env *gen_env, t_general_env *torefactor)
{
	gen_env->argv = 0;
	gen_env->env = 0;
	while (token_begin && token_begin != token_end)
	{
		//stock redirection / assignement is done before
		if (token_begin->type == SH_WORD)
		{
			printf("argv += %s\n", token_begin->content);
			push_str_to_tab(&gen_env->argv, token_begin->content);
		}
		token_begin = token_begin->next;
	}
	return (0);
}

int		exec_prgm(t_sh *p, t_token *token_begin, t_token *token_end, t_general_env *gen_env)
{
	//foreach $PATH + "/"
	//	construct path
	//
		//for now
		char *path = token_begin->content;
	//
	int ret;
	struct stat	st;
	t_general_env child_env;

	if (lstat(path, &st))
		printf("--%s not found\n", path);
	else
	{
		if (can_exec(&st))
		{
			construct_child_env(p, token_begin, token_end, &child_env, gen_env); //<--OOPS
			ret = exec_path(p, path, &child_env);
		}
		else
		{
			printf("cant exec %s\n", path);
			return (127);
		}
	}
	//	free_path
	return (ret);
}

int		exec_built_in(t_sh *p, t_token *token_begin, t_token *token_end, t_general_env *gen_env)
{
	//TODO
	printf("exec builtin -%s-\n", token_begin->content);
	if (!strcmp(token_begin->content, "true"))
		return (0);
	return (1);
}

int		is_built_in(const char *name)
{
	//TODO
	if (!(strcmp(name, "false") && strcmp(name, "true")))
		return (1);
	return (0);
}

int		exec_simple_command(t_sh *p, t_token *token_begin, t_token *token_end, t_general_env *gen_env)
{
//CREATE ENVIRONNEMENTAL STRUCTURE

	//simple_cmd:
	//				*io_redirect-*assignements ?cmd name *io_redirect-*argvs
	//find_stock_redirections/assignements
	//while (token_begin == redirect | assign)
	//	token_begin = token_begin->next;
	//handle no_cmd_name (<auteur)
	if (is_built_in(token_begin->content))
		return (p->last_cmd_result = exec_built_in(p, token_begin, token_end, gen_env));
	p->last_cmd_result = exec_prgm(p, token_begin, token_end, gen_env);
	return (p->last_cmd_result);
}

int		exec_compound_while(t_sh *p, t_token *token_while, t_general_env *gen_env, int type)
{
	int ret;
	int	tmp;

	printf("treating WHILE\n");
	ret = 0;
	while (((tmp = exec_script(p, token_while->sub->sub, 0, gen_env)) && type == SH_UNTIL) || (!tmp && type == SH_WHILE))
		ret = exec_script(p, token_while->sub->next->sub, 0, gen_env);
	return (ret);
}

int		exec_compound_if(t_sh *p, t_token *token_if, t_general_env *gen_env)
{
	printf("treating IF\n");
	if (!exec_script(p, token_if->sub->sub, 0, gen_env))
		return (p->last_cmd_result = exec_script(p, token_if->sub->next->sub, 0, gen_env));
	else if (token_if->sub->next->next)
		return (p->last_cmd_result = exec_script(p, token_if->sub->next->next->sub, 0, gen_env));
	return (0);
}//PROTECC NO ELSE

int exec_compound_for(t_sh *p, t_token *token_for, t_general_env *gen_env)
{
	//for name in yo lala ; do echo $name ; done
	t_token *ins;
	int		ret;

	printf("treating FOR\n");
	ins = token_for->sub->sub;
	ret = 0;
	while (ins)
	{
		//set $name to ins in child_env
		ret = exec_script(p, token_for->sub->next->sub, 0, 0/*child_env*/);
		ins = ins->next;
	}
	return (p->last_cmd_result = ret);
}

int		exec_compound_command(t_sh *p, t_token *token_compound, int type, t_general_env *gen_env) //<--More Child_env
{
	if (type == SH_WHILE || type == SH_UNTIL)
		return (exec_compound_while(p, token_compound, gen_env, type));
	else if (type == SH_IF)
		return (exec_compound_if(p, token_compound, gen_env));
	else if (type == SH_CASE)
	{}	//return (exec_compound_case(p, token_compound));
	else if (type == SH_FOR)
		return (exec_compound_for(p, token_compound, gen_env));
	return(exec_script(p, token_compound->sub, 0, 0/*child_env*/));
}

int		exec_command(t_sh *p, t_token *token_begin, t_token *token_end, t_general_env *gen_env)
{
	//if (token_begin->type == SH_FUNCTOKEN)
	//	store_func;
	//else
	if (token_begin->type == SH_WHILE || token_begin->type == SH_UNTIL || token_begin->type == SH_IF || token_begin->type == SH_CASE || token_begin->type == SH_FOR || token_begin->type == SH_BRACES) //<-- next token who have sens (no redirections...)
	{
	//	store potential redirectlst
		exec_compound_command(p, token_begin, token_begin->type, gen_env);
	}
	else
		p->last_cmd_result = exec_simple_command(p, token_begin, token_end, gen_env);
	return (p->last_cmd_result);
}

int		exec_pipeline(t_sh *p, t_token *token_begin, t_token *token_end, t_general_env *gen_env) //TOWORK
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
		next_separator = find_token_by_key_until(token_begin, token_end, &p->type, &p->pipeline_separators);
		printf("pipeline cut at '%i'\n", p->type);
		//OPEN PIPE AND SET IT IN GEN_ENV
		p->last_cmd_result = exec_command(p, token_begin, next_separator, gen_env); // <---- exec_command NON BLOQUANT ICI (new param?)
		//ONLY THE LAST PIPELINE CMD HAS RETURN ("false | echo $?")
		token_begin = (next_separator && next_separator != token_end) ? next_separator->next : 0;
	}
	if (bang)
		p->last_cmd_result = (p->last_cmd_result) ? 0 : 1;
	return (p->last_cmd_result);
}

int		exec_and_or(t_sh *p, t_token *token_begin, t_token *token_end, t_general_env *gen_env)
{
	t_token	*next_separator;
	int		previous_separator;
	int		tmp;

	previous_separator = 0;
	while (token_begin)
	{
		next_separator = find_token_by_key_until(token_begin, token_end, &p->type, &p->and_or_separators);
		printf("and_or cut at '%i'\n", p->type);
		tmp = p->type;
		if (!previous_separator || (previous_separator == SH_AND_IF && !p->last_cmd_result) || (previous_separator == SH_OR_IF && p->last_cmd_result))
			p->last_cmd_result = exec_pipeline(p, token_begin, next_separator, gen_env);
		previous_separator = tmp;
		token_begin = (next_separator && next_separator != token_end) ? next_separator->next : 0;
	}
	return (p->last_cmd_result);
}

void	exec_and_or_in_background(t_sh *p, t_token *token_begin, t_token *token_end, t_general_env *gen_env)
{
	int	child_pid;
	//fork stuff
	
	//if ((child_pid = (int)fork()) < 0)
	//{
		//exit properly;
	//}
	//if (!child_pid)
	//	return ;
	exec_and_or(p, token_begin, token_end, gen_env);
	//exit properly
}

int		exec_script(t_sh *p, t_token *token_begin, t_token *token_end, t_general_env *gen_env)
{
	t_token	*next_separator;

	while (token_begin)
	{
		next_separator = find_token_by_key_until(token_begin, token_end, &p->type, &p->script_separators); //<-- + newline (echo yo \n echo lala)
		printf("script cut at '%i'\n", p->type);
		if (p->type == SH_AND)
			exec_and_or_in_background(p, token_begin, next_separator, gen_env);
		else
			p->last_cmd_result = exec_and_or(p, token_begin, next_separator, gen_env);
		token_begin = (next_separator && next_separator != token_end) ? next_separator->next : 0;
	}
	return (p->last_cmd_result);
}


//INIT P->LAST_CMD_RESULT

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
t_token *create_token(int type, const char *content)
{
	t_token *tok = malloc(sizeof(t_token));
	tok->type = type;
	tok->content = strdup(content);
	tok->sub = 0;
	tok->next = 0;
	return (tok);
}

t_token	*gen_tokens()
{
	t_token *begin;
	t_token *actual;
	actual = create_token(SH_WORD, "/bin/echo");
	begin = actual;
	actual->next = create_token(SH_WORD, "yo");
	actual = actual->next;
	actual->next = create_token(SH_SEMI, "-;-");
	actual = actual->next;
	actual->next = create_token(SH_WORD, "/bin/ls");
	actual = actual->next;
	actual->next = create_token(SH_WORD, "/");
	return (begin);
}

t_token	*gen_tokens2()
{
	t_token *begin;
	t_token *actual;
	actual = create_token(SH_IF, "-if-");
	begin = actual;
	actual->sub = create_token(SH_GROUP_TOKEN, "-group-");
	actual->sub->sub = create_token(SH_WORD, "true");
	actual->sub->next = create_token(SH_GROUP_TOKEN, "-group-");
	actual->sub->next->sub = create_token(SH_WORD, "/bin/ls");
	actual->sub->next->sub->next = create_token(SH_WORD, "..");
	actual->sub->next->sub->next->next = create_token(SH_OR, "-|-");
	actual->sub->next->sub->next->next->next = create_token(SH_WORD, "/bin/cat");
	actual->sub->next->sub->next->next->next->next = create_token(SH_WORD, "yo");
	actual->next = create_token(SH_SEMI, "-;-");
	actual = actual->next;
	actual->next = create_token(SH_WORD, "/bin/ls");
	actual = actual->next;
	actual->next = create_token(SH_WORD, "/");
	return (begin);
}

void	print_all_tokens(t_token *t, int lvl)
{
	int lvcpy;
	while (t)
	{
		//printf("-%*s", lvl, (lvl) ? " " : "");
		lvcpy = lvl;
		while (lvcpy--)
			printf("%c      ", (lvcpy == 0) ? '|' : ' ');
		printf("%-10s (%i)\n", t->content, t->type);
		if (t->sub)
		{
			print_all_tokens(t->sub, lvl + 1);
		}
		t = t->next;
	}
}

void	init_params(t_sh *p)
{
	p->last_cmd_result = 0;
	p->script_separators[0] = SH_SEMI;
	p->script_separators[1] = SH_AND;
	p->and_or_separators[0] = SH_AND_IF;
	p->and_or_separators[1] = SH_OR_IF;
	p->pipeline_separators[0] = SH_OR;
	p->pipeline_separators[1] = 0;
}

int main()
{
	t_sh p;
	t_general_env gen_env;
	init_params(&p);
	printf("NEXT SCRIPT: echo yo ; ls /\n");
	t_token *tok = gen_tokens();
	print_all_tokens(tok, 0);
	exec_script(&p, tok, 0, &gen_env);
	printf("NEXT SCRIPT: if true; do ls .. | cat done ; ls /\n");
	tok = gen_tokens2();
	print_all_tokens(tok, 0);
	exec_script(&p, tok, 0, &gen_env);
}
