/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 18:13:44 by thdelmas          #+#    #+#             */
/*   Updated: 2019/08/31 16:59:15 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_env.h"
#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int sh_test_unary(char *s1, char *s2)
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
	else if (!ft_strcmp(s1, "-b") && !lstat(s2, &pstat) && (pstat.st_mode & S_IFMT) == S_IFBLK)
		return (0);
	else if (!ft_strcmp(s1, "-c") && !lstat(s2, &pstat) && (pstat.st_mode & S_IFMT) == S_IFCHR)
		return (0);
	else if (!ft_strcmp(s1, "-d") && !lstat(s2, &pstat) && (pstat.st_mode & S_IFMT) == S_IFDIR)
		return (0);
	else if (!ft_strcmp(s1, "-e") && !lstat(s2, &pstat))
		return (0);
	else if (!ft_strcmp(s1, "-f") && !lstat(s2, &pstat) && (pstat.st_mode & S_IFMT) == S_IFREG)
		return (0);
	else if (!ft_strcmp(s1, "-n") && ft_strlen(s2) > 0)
		return (0);
	else if (!ft_strcmp(s1, "-p") && !lstat(s2, &pstat) && (pstat.st_mode & S_IFMT) == S_IFIFO)
		return (0);
	else if (!ft_strcmp(s1, "-S") && !lstat(s2, &pstat) && (pstat.st_mode & S_IFMT) == S_IFSOCK)
		return (0);
	else if (!ft_strcmp(s1, "-s") && !lstat(s2, &pstat) && pstat.st_size > 0)
		return (0);
	else
		return (1);
}

int sh_test_binary(char *s1, char *s2, char *s3)
{
	if (!s1)
		return (1);
	else if (!ft_strcmp(s1, "!"))
		return (!sh_test_unary(s2, s3));
	else if (!ft_strcmp(s1, "(") && !ft_strcmp(s3, ")"))
		return (sh_test_unary(NULL, s2));
	else if (!ft_strcmp(s2, "=") && !ft_strcmp(s1, s3))
		return (0);
	else if (!ft_strcmp(s2, "!=") && ft_strcmp(s1, s3))
		return (0);
	else if (!ft_strcmp(s2, "-eq") && ft_atoi(s1) == ft_atoi(s3))
		return (0);
	else if (!ft_strcmp(s2, "-ne") && ft_atoi(s1) != ft_atoi(s3))
		return (0);
	else if (!ft_strcmp(s2, "-gt") && ft_atoi(s1) > ft_atoi(s3))
		return (0);
	else if (!ft_strcmp(s2, "-ge") && ft_atoi(s1) >= ft_atoi(s3))
		return (0);
	else if (!ft_strcmp(s2, "-lt") && ft_atoi(s1) < ft_atoi(s3))
		return (0);
	else if (!ft_strcmp(s2, "-le") && ft_atoi(s1) <= ft_atoi(s3))
		return (0);
	else
		return (1);
}
int		sh_test(int ac, char **av, t_env **ev)
{
	int		ret;
	int		i;
	int		j;
	char	un_op[] = "-b -c -d -e -f -n -p -S -s -z";
	char	bi_op[] = "= != -eq -ne -gt -ge -lt -le";

	(void)ev;
	i = 1;
	j = 0;
	while (++j < ac)
		if (!ft_strcmp("-a", av[i]))
			return (sh_test(i - 1, av, ev) || sh_test(ac - i - 1, av + i + 1, ev));
	j = 0;
	while (++j < ac)
		if (!ft_strcmp("-o", av[i]))
			return (sh_test(i - 1, av, ev) && sh_test(ac - i - 1, av + i + 1, ev));
	if (ac == 2)
		ret = (sh_test_unary(NULL, av[i]));
	else if (i < ac - 1  && ft_strstr(un_op, av[i]))
		ret =  (sh_test_unary(av[i], av[i + 1]));
	else if (i < ac - 2 && ft_strstr(bi_op, av[i + 1]))
		ret = (sh_test_binary(av[i], av[i + 1], av[i + 2]));
	else if (i < ac - 3 && !ft_strcmp(av[i], "!") && ft_strstr(bi_op, av[i + 2]))
		ret = (sh_test_binary(av[i + 1], av[i + 2], av[i + 3]) ? 1 : 0);
	else if (i < ac - 3 && !ft_strcmp(av[i], "(") && !ft_strcmp(av[i + 3], ")") && ft_strstr(bi_op, av[i + 1]))
		ret = sh_test_unary(av[i + 1], av[i + 2]);
	else if (i < ac - 4 && !ft_strcmp(av[i], "(") && !ft_strcmp(av[i + 4], ")") && ft_strstr(bi_op, av[i + 2]))
		ret = (sh_test_binary(av[i + 1], av[i + 2], av[i + 3]));
	else if (i < ac - 1 && !ft_strcmp(av[i], "("))
	{
		j = i;
		while (++i < ac && ft_strcmp(av[i], ")"))
			;
		if (i >= ac)
		{
			ft_putendl("Missing )");
			ret = (1);
		}
		else if (i == ac - 1)
			ret = (sh_test(i - j, av + j, ev));
	}
	else
		ret = 1;
	return (ret);
}
