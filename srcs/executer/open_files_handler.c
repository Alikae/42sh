/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/02/19 04:13:14 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_executer.h"
#include <fcntl.h>

void	push_to_opened_files(t_sh *p, char *name, int fd)
{
	t_open_file	**prev_next;

	prev_next = &p->opened_files;
	while (*prev_next)
		prev_next = &((*prev_next)->next);
	if (!(*prev_next = (t_open_file*)malloc(sizeof(t_open_file))))
		destructor(127);
	(*prev_next)->name = ft_strdup(name);
	(*prev_next)->fd = fd;
	(*prev_next)->next = 0;
}

void	remove_opened_files(t_sh *p)
{
	t_open_file	*tmp;

	while (p->opened_files)
	{
		ft_memdel((void**)&(p->opened_files->name));
		tmp = p->opened_files;
		p->opened_files = p->opened_files->next;
		close(tmp->fd);
		ft_memdel((void**)&tmp);
	}
}

int		file_is_already_open(t_sh *p, char *name)
{
	t_open_file	*f;

	f = p->opened_files;
	while (f)
	{
		if (name && f->name && !ft_strcmp(f->name, name))
			return (f->fd);
		f = f->next;
	}
	return (-1);
}

int		open_with_redirection_flags(char *path, t_toktype type)
{
	struct stat st;

	if (stat(path, &st) == -1)
		return (-1);
	if ((st.st_mode & S_IFIFO) && sh()->pid_main_process == getpid())
	{
		sh_dprintf(2, "42sh: can't redirect fifo file in main process\n");
		return (-1);
	}
	if (type == SH_GREAT)
		return (open(path, O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR));
	else if (type == SH_LESS)
		return (open(path, O_CREAT | O_RDONLY, S_IRUSR | S_IWUSR));
	else if (type == SH_DGREAT)
		return (open(path, O_CREAT | O_APPEND | O_WRONLY, S_IRUSR | S_IWUSR));
	else if (type == SH_LESSGREAT || type == SH_LESSAND || type == SH_GREATAND)
		return (open(path, O_CREAT | O_APPEND | O_RDWR,
					S_IRUSR | S_IWUSR));
		return (-1);
}

int		create_open_file(t_sh *p, char *path, t_toktype type)
{
	int		fd;
	int		was_malloc;
	char	*real_path;
	char	*tmp;

	if (!(was_malloc = 0) && path[0] == '/')
		real_path = path;
	else
	{
		real_path = getcwd(0, 0);
		tmp = ft_strjoin(real_path, "/");
		ft_memdel((void**)&real_path);
		real_path = ft_strjoin(tmp, path);
		(was_malloc = 1) ? ft_memdel((void**)&tmp) : 0;
	}
	if ((fd = open_with_redirection_flags(real_path, type)) < 0)
	{
		sh_dprintf(2, "42sh: OPEN ERROR - '%s'\n", real_path);
		p->abort_cmd = 1;
		(was_malloc) ? ft_memdel((void**)&real_path) : 0;
		return (-1);
	}
	push_to_opened_files(p, real_path, fd);
	(was_malloc) ? ft_memdel((void**)&real_path) : 0;
	return (fd);
}
