int		sh_error_path(char *cmd, char *path, int error);
{
	ft_putstr_fd(cmd, 2);
	ft_pustr_fd(path, 2);
	if (error & NOT_FOUND)
		write(2, ": No such file or directory\n", 28);
	if (error & NOT_DIR)
		write(2, ": Not a director\n", 17);
	if (error & NOT_ACCESS)
		write(2, ": Permission denied\n",  20);
	return (-1);
}

