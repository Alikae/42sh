/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/01/27 13:17:09 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

static int	sh_test_unary_sub(char *s1, char *s2)
{
	struct stat	pstat;

	if (!ft_strcmp(s1, "-e") && !lstat(s2, &pstat))
		return (0);
	else if (!ft_strcmp(s1, "-f") && !lstat(s2, &pstat)
			&& (pstat.st_mode & S_IFMT) == S_IFREG)
		return (0);
	else if (!ft_strcmp(s1, "-n") && ft_strlen(s2) > 0)
		return (0);
	else if (!ft_strcmp(s1, "-p") && !lstat(s2, &pstat)
			&& (pstat.st_mode & S_IFMT) == S_IFIFO)
		return (0);
	else if (!ft_strcmp(s1, "-S") && !lstat(s2, &pstat)
			&& (pstat.st_mode & S_IFMT) == S_IFSOCK)
		return (0);
	else if (!ft_strcmp(s1, "-s") && !lstat(s2, &pstat)
			&& pstat.st_size > 0)
		return (0);
	else
		return (1);
}

int			sh_test_unary(char *s1, char *s2)
{
	struct stat	pstat;

	if (!s1 && s2 && *s2)
		return (0);
	else if (!s1)
		return (1);
	else if (!ft_strcmp(s1, "!") && (!s2 || !*s2))
		return (0);
	else if (!ft_strcmp(s1, "-z") && (!s2 || !*s2))
		return (0);
	else if (!ft_strcmp(s1, "-b") && !lstat(s2, &pstat)
			&& (pstat.st_mode & S_IFMT) == S_IFBLK)
		return (0);
	else if (!ft_strcmp(s1, "-c") && !lstat(s2, &pstat)
			&& (pstat.st_mode & S_IFMT) == S_IFCHR)
		return (0);
	else if (!ft_strcmp(s1, "-d") && !lstat(s2, &pstat)
			&& (pstat.st_mode & S_IFMT) == S_IFDIR)
		return (0);
	else
		return (sh_test_unary_sub(s1, s2));
}
