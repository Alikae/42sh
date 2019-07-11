int		sh_rm_last_arg(int opt, char *path)
{
	struct stat s;
	DIR			*dirp;

	lstat(path, &s);
	if ((s.st_mod & IF_DIR) == IF_DIR && !(opt & 1))
	{
		if (opt & 1)
			return (sh_rm_directory(path));
		else
		{
			drp = opendir(path);
			if (readdir(dirp) == NULL)
			{
				closedir(dirp);
				return (1);
			}
			closedir(dirp);
			return (sh_rm_not_empty(path));
		}
	}
	return (1);
}

int		sh_rm_path(int opt, char *path, int *error)
{
	if (sh_check_path(path, error) == -1)
	{
		if (!(opt & 2) || (!(error & NOT_FOUND))
			return (1);
		else
			return (sh_error_path("rm: ", path, error));
	}
	if (opt & 2)
		return (ft_rm_last_arg(opt, path));
	return (1);
}
