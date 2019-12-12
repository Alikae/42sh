/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prgm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 16:03:48 by ede-ram           #+#    #+#             */
/*   Updated: 2019/12/08 17:35:15 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_executer.h"

int	exec_path(t_sh *p, char *path, char **child_argv)
{
	int ret;
	int child_pid;

	child_pid = fork_process(p, 1);
	ret = 0;
	if (child_pid)
		ret = block_wait(p, child_pid, 0);
	else
	{
		execve(path, child_argv, transform_env_for_child(p->params)/*protec?FREE?*/);
		dprintf(2, "Execve ErrorR\n");
		sh()->exit = 1;
		exit(1);
	}
	return (ret);
}

int	can_exec(struct stat *st)
{
	if (st->st_uid == getuid() && st->st_mode & S_IXUSR)
		return (1);
	else if (st->st_gid == getgid() && st->st_mode & S_IXGRP)
		return (1);
	else if (st->st_mode & S_IXOTH)
		return (1);
	return (0);
}

int	exec_prgm(t_sh *p, char **child_argv)
{
	int			ret;
	struct stat	st;
	char		*real_path;

	ret = 0;
	if (!(real_path = get_real_path(child_argv[0], &st)))
		return (127);
	if (!can_exec(&st))
	{
		printf("cant exec '%s'\n", child_argv[0]);
		return (127);
	}
	ret = exec_path(p, real_path, child_argv);
	free(real_path);
	return (ret);
}
