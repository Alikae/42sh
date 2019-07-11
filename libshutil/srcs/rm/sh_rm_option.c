void	sh_opt(char c, int *opt)
{
	if ((c == 'r' || c == 'R') && ((*opt) & 1 != 0))
		*opt = (*opt) + 1;
	else if (c == 'f' && ((*opt) & 2 != 0))
		*opt = (*opt) + 2;
	else if (c == 'i' && ((*opt) & 3 != 0) && ((*opt) & 2 != 0)
		*opt = (*opt) + 3;
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
				return (sh_error_rm_opt(av[*i][j]));
			sh_opt(av[*i][j], &opt);
			j++;
		}
		(*i)++;
	}
	return (opt);
}
