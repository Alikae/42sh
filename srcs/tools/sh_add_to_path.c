char	ft_creat_path(char *path, const char *name)
{
	int		i;
	int		j;
	char	*new;

	j = 0;
	i = 0;
	if (!((new = malloc((ft_strlen(path) + ft_strlen(name)) + 2)))
		exit (0);
	while (path[i])
		new[j++] = path[i++];
	if (path[j - 1] != '/')
		path[j++] = '/';
	i = 0;
	while (name[i])
		new[j++] = name[i++];
	new[j] = '\0';
	return (new);
}
