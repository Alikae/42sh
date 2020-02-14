#include "sh_tools.h"
#include "sh_builtins.h"
#include "libft.h"

static char		**init_tab(void)
{
	char **cd_path;

	cd_path = ft_strsplit(sh_getev_value("CDPATH"), ':');
	if (!cd_path)
		cd_path = tab_realloc(cd_path, sh_getev_value("CDPATH"));
	if (!cd_path)
		return (NULL);
	return (cd_path);
}

char			*sh_try_cd_path(char *arg, char flag)
{
	int 	i;
	char	*av;
	char	**cd_path;
	char	**path;
	char	*real;

	i = -1;
	real = NULL;
	cd_path = init_tab();
	av = NULL;
	while (i != -2 && cd_path && cd_path[++i])
	{
		av = ft_strjoin(cd_path[i], "/");
		av = ft_strjoin_free(av, arg, av);
		if (!(path = ft_strsplit(av, '/')))
		{
			ft_tab_strdel(&path);
			path = tab_realloc(path, av);
		}
		if ((real = path_process(av, path, flag)))
			i = -2; 
		ft_memdel((void**)&av);
		ft_tab_strdel(&path);
	}
	ft_tab_strdel(&cd_path);
	return (real);
}
