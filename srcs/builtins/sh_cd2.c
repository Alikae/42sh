/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 00:31:32 by tmeyer            #+#    #+#             */
/*   Updated: 2020/02/17 00:31:49 by tmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_tools.h"
#include "sh_builtins.h"
#include "libft.h"

char			*check_av(char *av)
{
	char	*tmp;

	tmp = NULL;
	if (!av && !(tmp = sh_getev_value("HOME")))
	{
		sh_dprintf(2, "NO HOME SET\n");
		return (NULL);
	}
	else if (av && !strcmp(av, "-") && !(tmp = sh_getev_value("OLDPWD")))
	{
		sh_dprintf(2, "NO OLDPWD SET\n");
		return (NULL);
	}
	else if (!tmp)
		return (av);
	return (tmp);
}

static char		**init_tab(void)
{
	char **cd_path;
	char *tmp;

	if (!(tmp = sh_getev_value("CDPATH")))
		return (NULL);
	cd_path = ft_strsplit(tmp, ':');
	if (!cd_path)
		cd_path = tab_realloc(cd_path, tmp);
	return (cd_path);
}

static char		*sh_try_cd_path(char *arg, char flag)
{
	int		i;
	char	*av;
	char	**cd_path;
	char	*real;

	i = -1;
	real = NULL;
	cd_path = init_tab();
	av = NULL;
	while (i != -2 && cd_path && cd_path[++i])
	{
		av = ft_strjoin(cd_path[i], "/");
		av = ft_strjoin_free(av, arg, av);
		sh_generate_path(av, 0);
		printf("AV: [%s]\n", sh()->potential_pwd);
		ft_memdel((void**)&real);
		real = process_cd(sh()->potential_pwd, flag);
		printf("i: %d\n:", i);
		if (!(sh()->chdir_result = chdir(real)))
			i = -2;
		ft_memdel((void**)&av);
	}
	ft_tab_strdel(&cd_path);
	return (real);
}

char			*sh_real_cd(char *arg, char flag)
{
	char *real;

	real = NULL;
	if (!arg)
		return (NULL);
	if ((arg && (arg[0] == '/' || arg[0] == '.')) || !sh_getev_value("CDPATH"))
	{
		sh_generate_path(arg, 0);
		real = process_cd(sh()->potential_pwd, flag);
		if ((sh()->chdir_result = chdir(real)))
			ft_memdel((void**)&real);
		return (real);
	}
	else
		return (sh_try_cd_path(arg, flag));	
}
