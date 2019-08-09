/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_rmdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 23:30:06 by thdelmas          #+#    #+#             */
/*   Updated: 2019/08/06 23:30:09 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	sh_rmdir_option(char **av, int *i, int *opt)
{
	int		j;

	j = 0;
	while (av[*i][0] == '-')
	{
		if (ft_strcmp(av[*i], "--") == 0)
			return ;
		while (av[*i][j])
		{
			if (av[*i][j] != '-' && av[*i][j] != 'b' && av[*i][j] != 'f'
					&& av[*i][j] != 'i' && av[*i][j] != 'u')
				return (sh_error_rm_opt(av[*i][j]));
			if (av[*i][j] == 'p' || (!(*opt)))
				*opt = 1
			j++;
		}
		(*i)++;
	}
}

int		sh_rm_last_arg(int opt, char *path)
{
	struct stat s;
	DIR			*dirp;

	stat(path, &s);
	if ((s.st_mod & IF_DIR) == IF_DIR && !(opt & 1))
	{
		if ((opt & 1) && (opt & 2))
			return (sh_rm_directory(path));
		if (!(opt & 2))
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
		if (!(opt & 4) && (!(error & NOT_FOUND))
			return (1);
		else
			return (sh_error_path("rm: ", path, error));
	}
	if (opt & 4)
		return (ft_rm_last_arg(opt, path));
	return (1);
}

int		sh_removedir(char *path, int opt)
{

}

int		sh_rmdir(int ac, char **av, t_env **env)
{
	int		opt;
	int		i;
	int		error;
	int 	ret;

	ret = 0;
	i = 0;
	opt = 0
	error = 0;
	sh_rmdir_option(av, &i, &opt);
	while (av[i])
	{
		if (sh_check_path(av[i], &error))
			sh_removedir(av[i], opt);
		else
		{
			sh_print_error("rmdir: ", av[i], error);
			ret++;
		}
		(*i)++;
	}
	return (ret);
}
