/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 16:06:19 by ede-ram           #+#    #+#             */
/*   Updated: 2019/12/14 00:57:20 by ede-ram          ###   ########.fr       */
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
		exit(127);
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

int		open_with_redirection_flags(char *real_path, t_toktype type)
{
	if (type == SH_GREAT)
		return (open(real_path, O_CREAT | O_TRUNC | O_WRONLY,
					S_IRUSR | S_IWUSR));
	else if (type == SH_LESS)
		return (open(real_path, O_CREAT | O_RDONLY,
					S_IRUSR | S_IWUSR));
	else if (type == SH_DGREAT)
		return (open(real_path, O_CREAT | O_APPEND | O_WRONLY,
					S_IRUSR | S_IWUSR));
	else if (type == SH_LESSGREAT)
		return (open(real_path, O_CREAT | O_APPEND | O_RDWR,
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
		ft_memdel((void**)&tmp);
		was_malloc = 1;
	}
	if ((fd = open_with_redirection_flags(real_path, type)) < 0)
	{
		dprintf(2, "OPEN ERROR -> '%s'\n", real_path);
		(was_malloc) ? ft_memdel((void**)&real_path) : 0;
		return (-1);
	}
	push_to_opened_files(p, real_path, fd);
	(was_malloc) ? ft_memdel((void**)&real_path) : 0;
	return (fd);
}
