#include "libshutil.h"

int		sh_recursive_rm(char *path)
{
	int				ret;
	DIR				*dirp;
	struct dirent	*dp;
	char			*new_path;

	ret = 0;
	if (sh_check_last_path(path))
		dirp = opendir(path);
	else
		return (-1);
	while ((dp = readdir(dirp)) != NULL)
	{
		new_path = ft_add_to_path(path, dp->d_name);
		if ((dp->d_type & DT_DIR) == DT_DIR)
		{
			if ((ret = sh_recursive_rm(new_path)) == 0)
				rmdir(new_path);
		}
		else if (sh_check_file(new_path))
			unlink(new_file);
		free(new_path);
		else
			return (-1);
	}
	return (ret);
}

int		sh_remove(int opt, char *path)
{
	if (!(opt & 1))
		return (ft_recursive_rm(path));
	else if (!(opt & 2))
		unlink(path);
	else
		rmdir(path);
	return (0);
}

int		sh_rm(int ac, char **av)
{
	int		opt;
	int		i;
	int		error;
	int		ret;
	int		rm_ret;

	i = 1;
	error = 0;
	ret = 0;
	rm_ret = 0;
	if ((opt = sh_find_opt(av, &i)) == -1)
		return (-1);
	while (av[i])
	{
		if (sh_rm_path(opt, av[i], &error)
			ret = sh_remove(opt, av[i]);
		else
			ret = -1;
		i++;
		if (ret = -1)
			rm_ret = -1;
	}
	return (rm_ret);
}
