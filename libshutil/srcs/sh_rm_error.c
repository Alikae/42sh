int		sh_error_rm_opt(char c)
{
	write(2, "rm: illegal option -- ", 23);
	write(2, &c, 1);
	write(2,"\nusage: rm [-f | -i] [-dPRrvW] file ...", 39);
	write(2, "\nunlink file\n", 13);
	return (-1);
}

int		sh_rm_directory(char *path)
{
	write(2, "rm: ", 4);
	ft_putstr_fd(path, 2);
	write(2, ": is a directory\n", 17);
	return (-1);
}

int		sh_rm_no_empty(char *path)
{
	write(2, "rm: ", 4);
	ft_putstr_fd(path, 2);
	write(2, ": Directory not empty\n", 22);
	return (-1);
}
