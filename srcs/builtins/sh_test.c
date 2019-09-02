/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 18:13:44 by thdelmas          #+#    #+#             */
/*   Updated: 2019/09/01 19:43:21 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_env.h"
#include "libft.h"
#include "sh_builtins.h"
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

int		sh_test_and_or(int ac, char **av, t_env **ev)
{
	int		j;
	int		brace;

	j = 0;
	brace = 0;
	while (++j < ac)
	{
		if (!ft_strcmp("(", av[j]))
			brace++;
		else if (!ft_strcmp(")", av[j]))
			brace--;
		else if (!brace && !ft_strcmp("-a", av[j]))
			return (sh_test(j, av, ev) || sh_test(ac - j, av + j, ev));
	}
	j = 0;
	brace = 0;
	while (++j < ac)
	{
		if (!ft_strcmp("(", av[j]))
			brace++;
		else if (!ft_strcmp(")", av[j]))
			brace--;
		else if (!brace && !ft_strcmp("-o", av[j]))
			return (sh_test(j, av, ev) && sh_test(ac - j, av + j, ev));
	}
	return (-1);
}

int		sh_test_braces(int ac, char **av, int i, int ret)
{
	int j;

	j = i;
	while (++i < ac && ft_strcmp(av[i], ")"))
		;
	if (i >= ac)
	{
		ft_putendl("Missing )");
		return (1);
	}
	else if (i == ac - 1)
		ret = sh_test(i - j, av + j, NULL);
	if (i < ac - 2 && !ft_strcmp(av[i + 1], "-a"))
		return (ret == 0 && sh_test(ac - 1, av + 1, NULL) == 0 ? 0 : 1);
	else if (i < ac - 2 && !ft_strcmp(av[i + 1], "-o"))
		return (ret == 0 || sh_test(ac - 1, av + 1, NULL) == 0 ? 0 : 1);
	else
		return (ret);
}

int		sh_test(int ac, char **av, t_env **ev)
{
	int		ret;
	int		i;
	char	un_op[] = "-b -c -d -e -f -n -p -S -s -z";
	char	bi_op[] = "= != -eq -ne -gt -ge -lt -le";

	(void)ev;
	i = 1;
	ret = 1;
	if ((ret = sh_test_and_or(ac, av, ev)) != -1)
		return (ret);
	else if (ac >= 2 && !ft_strcmp(av[i], "!"))
		ret = !(sh_test(ac - 1, av + 1, ev));
	else if (ac == 2)
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
		ret = sh_test_braces(ac, av, i, ret);
	else
		ret = 1;
	return (ret);
}
