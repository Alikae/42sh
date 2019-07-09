int		sh_error_mv_opt(char c)
{
	write(2, "mv: illegal option -- ", 23);
	write(2, &c, 1);
	write(2,"\nusage: mv [-f | -i | -n] [-v] source targe", 43);
	write(2, "\n\tmv [-f | -i | -n] [-v] source ... directory\n", 46);
	return (-1);
}

void	sh_opt(char c, int *opt)
{
	if (c == 'b' && ((*opt) & 1 == 0))
		*opt = (*opt) + 1;
	else if (c == 'f' && ((*opt) & 2 == 0))
		*opt = (*opt) + 2;
	else if (c == 'i' && ((*opt) & 4 == 0))
		*opt = (*opt) + 4;
	else if (c == 'u' && ((*opt) & 8 == 0))
		*opt = (*opt) + 8;
}

int		sh_find_opt(char **av, int *i)
{
	int		opt;
	int		j;

	opt = 0;
	j = 0;
	while (av[*i][0] == '-')
	{
		if (ft_strcmp(av[*i], "--") == 0)
			return (opt);
		while (av[*i][j])
		{
			if (av[*i][j] != '-' && av[*i][j] != 'b' && av[*i][j] != 'f'
					&& av[*i][j] != 'i' && av[*i][j] != 'u')
				return (sh_error_mv_opt(av[*i][j]));
			sh_opt(av[*i][j], &opt);
			j++;
		}
		(*i)++;
	}
	return (opt);
}

int		sh_mv(int ac, char **av, char **env)
{
	int		opt;
	int		i;

	i = 1;
	if ((opt = sh_find_opt(av, &i)) == -1)
		return (-1);
}
