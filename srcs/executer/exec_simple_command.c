/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 07:03:55 by ede-ram           #+#    #+#             */
/*   Updated: 2020/01/18 03:42:01 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_exitpoint.h"
#include "sh_entrypoint.h"
#include "sh_builtins.h"
#include "sh_executer.h"
#include <fcntl.h>
#include <stdio.h>
#include "sh_tokenizer.h"
#include "sh_redirections.h"
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include "sh_env.h"
#include "sh_error.h"
#include "sh_word_expansion.h"
#include "sh_tools.h"
#include "sh_tokens.h"
#include "sh_job_control.h"

void	free_simple_cmd_ressources(t_sh *p, int nb_redirections, int nb_assign,
		char **child_argv)
{
	ft_free_tabstr(child_argv);
	del_n_redirect_lst(&p->redirect_lst, nb_redirections);
	restore_std_fds(p);
	remove_opened_files(p);
	restore_before_assigns(p);
	del_n_assign_lst(p, nb_assign);
}

int		exec_simple_command_2(t_sh *p, char **child_argv, t_token *tmp,
		int (*f)(int ac, char **av, t_env **ev))
{
	handle_assigns(p);
	save_std_fds(p);
	generate_redirections(p);
	if ((tmp = is_defined_function(child_argv[0])))
		return (exec_function(p, tmp, child_argv));
	else if ((f = sh_is_builtin(child_argv[0])))
		return (exec_builtin(p, f, child_argv));
	else
		return (exec_prgm(p, child_argv));
}

int		exec_simple_command(t_sh *p, t_token *token_begin, t_token *token_end)
{
	int		nb_redirections;
	int		nb_assign;
	int		(*f)(int ac, char **av, t_env **ev);
	t_token	*tmp;
	char	**child_argv;

	f = 0;
	if ((tmp = is_function_definition(token_begin, token_end)))
		return (store_func(p, tmp));
	nb_redirections = stock_redirections_assignements_argvs(token_begin,
			token_end, &nb_assign, &child_argv);
	if (p->abort_cmd)
	{
		free_simple_cmd_ressources(p, nb_redirections, nb_assign, child_argv);
		return (-125);
	}
	if (!child_argv[0])
		return (handle_no_cmd_name(p, child_argv, nb_redirections));
	tmp = (t_token*)(uint64_t)exec_simple_command_2(p, child_argv, tmp, f);
	free_simple_cmd_ressources(p, nb_redirections, nb_assign, child_argv);
	return ((int)tmp);
}
