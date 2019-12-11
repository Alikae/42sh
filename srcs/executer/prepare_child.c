/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 16:11:36 by ede-ram           #+#    #+#             */
/*   Updated: 2019/12/08 17:59:20 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_executer.h"
#include "sh_tokenizer.h"
#include "sh_builtins.h"
#include "sh_tools.h"

char	**transform_env_for_child(t_env *env)
{
	char	**tab;
	int		len;
	t_env	*tmp;

	len = 0;
	tmp = env;
	while (tmp)
	{
		if (tmp->exported && tmp->value)
			len++;
		tmp = tmp->next;
	}
	if (!(tab = (char**)malloc((len + 1) * sizeof(char*))))
		exit(127);
	len = 0;
	while (env)
	{
		if (env->exported && env->value)
			tab[len++] = ft_join_with_char(env->key, env->value, '=');//protecc?
		env = env->next;
	}
	tab[len] = 0;
	return (tab);
}

int		count_argv(t_token *token_begin, t_token *token_end)
{
	int	cmd_begin;
	int	nb;

	cmd_begin = 0;
	nb = 0;
	while (token_begin)
	{
		if (token_begin->type == SH_WORD &&
				!(ft_strchr(token_begin->content, '=') > token_begin->content))
			cmd_begin = 1;
		if (token_begin->type == SH_WORD && cmd_begin)
			nb++;
		token_begin = (token_begin->next == token_end) ? 0 : token_begin->next;
	}
	return (nb);
}

char	**build_child_argvs(t_token *ast)
{
	int		len;
	t_token	*tmp;
	char	**argvs;

	len = 0;
	tmp = ast;
	while (tmp)
	{
		tmp = tmp->next;
		len++;
	}
	sh()->child_ac = len;
	if (!(argvs = (char **)malloc((len + 1) * sizeof(char*))))
		exit(127);
	argvs[len] = 0;
	len = 0;
	while (ast)
	{
		argvs[len++] = dupfilsdup(ast->content);
		ast = ast->next;
	}
	return (argvs);
}

int		(*sh_is_builtin2(const char *cmd))(int ac, char **av, t_env **ev)
{
	if (!ft_strcmp(cmd, "test"))
		return (&sh_test);
	else if (!ft_strcmp(cmd, "jobs"))
		return (&sh_jobs);
	else if (!ft_strcmp(cmd, "type"))
		return (&sh_type);
	else if (!ft_strcmp(cmd, "fg"))
		return (&sh_fg);
	else if (!ft_strcmp(cmd, "exit"))
		return (&sh_exit);
	else if (!ft_strcmp(cmd, "source") || !ft_strcmp(cmd, "."))
		return (&sh_source);
	else if (!ft_strcmp(cmd, "pwd"))
		return (&sh_pwd);
	else if (!ft_strcmp(cmd, "readonly"))
		return (&sh_readonly);
	return (NULL);
}

int		(*sh_is_builtin(const char *cmd))(int ac, char **av, t_env **ev)
{
	if (!ft_strcmp(cmd, "true"))
		return (&sh_true);
	else if (!ft_strcmp(cmd, "cd"))
		return (&sh_cd);
	else if (!ft_strcmp(cmd, "echo"))
		return (&sh_echo);
	else if (!ft_strcmp(cmd, "env"))
		return (&sh_env);
	else if (!ft_strcmp(cmd, "unsetenv"))
		return (&sh_unset);
	else if (!ft_strcmp(cmd, "setenv"))
		return (&sh_export);
	else if (!ft_strcmp(cmd, "export"))
		return (&sh_export);
	else if (!ft_strcmp(cmd, "false"))
		return (&sh_false);
	else if (!ft_strcmp(cmd, "set"))
		return (&sh_set);
	else if (!ft_strcmp(cmd, "unset"))
		return (&sh_unset);
	else if (!ft_strcmp(cmd, "alias"))
		return (&sh_alias);
	else if (!ft_strcmp(cmd, "unalias"))
		return (&sh_unalias);
	return (sh_is_builtin2(cmd));
}
